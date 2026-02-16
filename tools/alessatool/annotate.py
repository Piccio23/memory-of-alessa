from pathlib import Path
from subprocess import run
from dataclasses import dataclass

@dataclass
class AnnotationArgs:
    vram_start: int
    vram_end: int
    elf_path: Path
    asm_path: Path
    out_path: Path
    addr2line_path: Path
    encoding: str
    verbose: bool

def annotate_asm(args: AnnotationArgs):
    with open(args.asm_path, "r") as asm_file:
        asm_contents = asm_file.read()

    asm_lines = asm_contents.splitlines()
    asm_line_index = 0

    addresses = (f"0x{v:X}" for v in range(args.vram_start, args.vram_end, 0x4))
    proc = run([args.addr2line_path, "-e", args.elf_path, *addresses], capture_output=True, encoding=args.encoding)
    lines = proc.stdout.splitlines()

    prev_tu_name = ""
    prev_line_number = -1
    current_vram_addr = args.vram_start
    annotated_asm_lines = []

    for addr_index in range(0, len(lines) - 1):
        line = lines[addr_index]
        if line.startswith("?"):
            current_vram_addr += 0x4
            continue

        separator_index = line.rfind(":")
        current_line_number = int(line[separator_index+1:])

        if current_line_number == prev_line_number:
            prev_line_number = current_line_number
            current_vram_addr += 0x4
            continue

        current_tu_name = line[0:separator_index]
        if prev_tu_name:
            assert current_tu_name == prev_tu_name, f"{current_tu_name} != {prev_tu_name}"
        else:
            prev_tu_name = current_tu_name

        asm_line = asm_lines[asm_line_index]

        while asm_line_index < len(asm_lines) and f"{current_vram_addr:X}" not in asm_line:
            annotated_asm_lines.append(asm_line)
            asm_line_index += 1
            asm_line = asm_lines[asm_line_index]

        if asm_line_index >= len(asm_lines):
            raise AssertionError(f"address {current_vram_addr:X} not found in asm")

        annotated_asm_lines.append(f"\t.loc 1 {current_line_number}")    
        annotated_asm_lines.append(asm_line)
        asm_line_index += 1

        prev_line_number = current_line_number
        current_vram_addr += 0x4
    
    while asm_line_index < len(asm_lines) - 1:
        annotated_asm_lines.append(asm_lines[asm_line_index])
        asm_line_index += 1

    assert prev_tu_name, "no valid compilation unit found"
    annotated_asm_lines = [
        ".section .debug",
        ".previous",
        ".text",
        f".file 1 \"{prev_tu_name}\"",
        *annotated_asm_lines
    ]

    annotated_asm_contents = "\n".join(annotated_asm_lines)

    with open(args.out_path, "w") as out:
        out.write(annotated_asm_contents)

    if args.verbose:
        print(f"alessatool/annotate: wrote asm to {args.out_path}")