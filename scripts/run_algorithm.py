#!/usr/bin/env python3
import subprocess
from pathlib import Path
import argparse

def parse_args():
    p = argparse.ArgumentParser(description="Run algorithm on selected inputs and store outputs")
    p.add_argument(
        "--binary",
        required=True,
        help="Path to compiled algorithm",
    )
    p.add_argument(
        "--input",
        required=True,
        help="Path to inputs",
    )
    p.add_argument(
        "--output",
        required=True,
        help="Path to directory where output files will be saved.",
    )
    p.add_argument(
        "--params",
        nargs='+',
        help="List of parameters for algorithm",
    )
    p.add_argument(
        "--seed",
        required=True,
        help="Seed",
    )
    return p.parse_args()

def main():
    args = parse_args()
    input_path = Path(args.input)
    output_path = Path(args.output)
    output_path.mkdir(parents=True, exist_ok=True)
    for p in input_path.iterdir():
        if p.is_file() and p.suffix.lower() != ".json":
            output_file_path = (output_path / p.stem).with_suffix(".out")
            subprocess.run([args.binary, str(p), str(output_file_path), str(args.seed), *args.params])
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
