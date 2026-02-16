import json
from pathlib import Path
from dataclasses import dataclass, asdict
from utils import normalize_object_path, to_expected_path

import splat.scripts.split as split
import splat.util.options as splat_options
from splat.segtypes.linker_entry import write_file_if_different, clean_up_path

SECTION_ALIGNMENT_PAIRS: list[tuple[str, int]] = [
    (".text", 0x8),
    (".data", 0x8),
    (".rodata", 0x8),
    (".lit4", 0x4),
    (".sdata", 0x4),
    (".sbss", 0x4),
    (".bss", 0x10),
]

@dataclass
class GenerationArgs:
    template_path: Path
    output_path: Path
    build_path: Path
    expected_path: Path
    verbose: bool
    no_lcf: bool
    no_objdiff: bool
    use_cache: bool
    yamls: list[str]
    make_full_disasm_for_code: bool

@dataclass
class UnitMetadata:
    progress_categories: list[str]
    source_path: str | None

@dataclass
class Unit:
    name: str
    base_path: str
    target_path: str
    metadata: UnitMetadata

def split_yaml(request: GenerationArgs) -> None:
    '''
    Split a YAML with splat. Outputs a linker command file (.LCF) for MWLD, an
    `objdiff.json`, both, or neither.
    '''

    split.main(
        request.yamls,
        modes="all",
        verbose=request.verbose,
        use_cache=request.use_cache,
        make_full_disasm_for_code=request.make_full_disasm_for_code
    )

    generate_linker_dependencies(request)

    if not request.no_lcf:
        generate_lcf(request)
    
    if not request.no_objdiff:
        generate_objdiff_json(request)

def generate_linker_dependencies(request: GenerationArgs):
    linker_writer = split.linker_writer
    build_path = request.build_path
    path_strs = []

    output = f"{(build_path / clean_up_path(splat_options.opts.elf_path)).as_posix()}:"

    for entry in linker_writer.dependencies_entries:
        if entry.object_path is None:
            continue
        path_str = normalize_object_path(entry.object_path, build_path)
        path_strs.append(path_str)
        output += f" \\\n    {path_str}"

    output += "\n"
    for path_str in path_strs:
        output += f"{path_str}:\n"

    write_file_if_different(splat_options.opts.ld_script_path.with_suffix(".d"), output)

def generate_lcf(request: GenerationArgs):
    '''
    Generate a linker command file. It uses an oversimplified method of looping
    over the linker entries emitted by Splat and looking for splits that are
    parented to a `code` segment. Then it writes out the list of object files
    for each section.

    Expects a template file with the extension `.inc.lcf`.
    '''

    objects_by_section_type: dict[str, list[str]] = dict()
    for section_type, _ in SECTION_ALIGNMENT_PAIRS:
        objects_by_section_type[section_type] = []

    for entry in split.linker_writer.entries:
        segment = entry.segment
        parent = segment.parent

        if not parent or parent.type != "code":
            continue

        section_type = entry.section_link_type
        if section_type not in objects_by_section_type:
            continue

        objects_by_section_type[section_type].append(entry.object_path.name)

    lcf_blocks: list[str] = []

    for section_type, alignment in SECTION_ALIGNMENT_PAIRS:
        objects = objects_by_section_type[section_type]
        if not objects:
            continue

        block = [
            f"\t\t# {section_type}",
            f"\t\tALIGNALL(0x{alignment:X});",
        ]

        block.extend(f"\t\t{object_name} ({section_type})" for object_name in objects)
        lcf_blocks.append("\n".join(block))

    generated_lcf = "\n\n".join(lcf_blocks)

    template_path = request.template_path
    output_path = request.output_path

    template = template_path.read_text()
    output = template.replace(
        "### 🔴 code 🔴 ###",
        generated_lcf.strip(),
    )
    output_path.write_text(output)

    if request.verbose:
        print(f"✅ alessatool/generate: wrote LCF to {output_path}")

def generate_objdiff_json(request: GenerationArgs):
    units: list[dict] = []

    for entry in split.linker_writer.entries:
        segment = entry.segment
        parent = segment.parent
        segment_type = segment.type

        if segment.name == "sce":
            continue
        if segment.name.startswith("sdk/"):
            continue
        if segment.name.startswith("cri/"):
            continue
        if segment.name == "crt0":
            continue
        if segment_type != "asm" and segment_type != "c":
            continue
        if not parent or parent.type != "code":
            continue

        if len(entry.src_paths) > 1:
            raise Exception("Unhandled case: len(src_paths) > 1")

        source_path = str(entry.src_paths[0])
        object_path = str(entry.object_path)
        is_code = source_path.endswith(".c")

        metadata = UnitMetadata(
            progress_categories=[
                parent.name
            ],
            source_path=is_code and source_path or None
        )

        base_path = is_code and normalize_object_path(Path(object_path), request.build_path) or None
        target_path = normalize_object_path(to_expected_path(object_path), request.expected_path)
        unit = Unit(
            name=entry.segment.name,
            base_path=base_path,
            target_path=target_path,
            metadata=metadata
        )

        units.append(asdict(unit))
    
    result = json.dumps({
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "build_base": False,
        "build_target": False,
        "units": units,
    })

    with open("objdiff.json", "w") as f:
        f.write(result)

    if request.verbose:
        print(f"🟣 alessatool/generate: wrote objdiff.json")