from pathlib import Path
from dataclasses import dataclass
from json import load, dumps
from utils import ensure_path_and_write

@dataclass
class MergeArgs:
    objdiff_fragments: list[Path]
    output_path: Path
    verbose: bool

def merge_objdiff_units(args: MergeArgs):
    units = []

    for path in args.objdiff_fragments:
        fragment = open(path, "r")
        new_units = load(fragment)
        fragment.close()

        assert isinstance(new_units, list), f"expected 'list', got '{type(new_units)}'"
        units.extend(new_units)

    units.sort(key=lambda unit: unit["name"])

    result = dumps({
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "build_base": False,
        "build_target": False,
        "units": units,
    })

    ensure_path_and_write(args.output_path, result)

    if args.verbose:
        print(f"🟣 alessatool/merge: wrote objdiff.json")
