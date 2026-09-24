#!/usr/bin/env python3
import argparse
import json
import subprocess
from pathlib import Path


def parse_args():
    parser = argparse.ArgumentParser(
        description="Run a summary on selected inputs and store outputs"
    )

    parser.add_argument(
        "--binary",
        required=True,
        help="Path to the compiled summary runner",
    )
    parser.add_argument(
        "--summary",
        required=True,
        help="Name of the summary to run",
    )
    parser.add_argument(
        "--input",
        required=True,
        help="Path to the input directory",
    )
    parser.add_argument(
        "--output",
        required=True,
        help="Path to the directory where output files will be saved",
    )
    parser.add_argument(
        "--params",
        nargs="*",
        default=[],
        help="Summary-specific parameters",
    )
    parser.add_argument(
        "--seed",
        required=True,
        help="Seed",
    )
    parser.add_argument(
        "--top-k",
        type=int,
        help="Number of top elements to output",
    )

    return parser.parse_args()


def parse_statistics(output):
    statistics = {}
    for line in output.splitlines():
        name, value = line.split(":", maxsplit=1)
        statistics[name.strip()] = int(value.strip())
    return {
        "update_time_ns": statistics["UpdateTimeNS"],
        "query_time_ns": statistics["QueryTimeNS"],
        "memory": statistics["Memory"],
    }

def save_statistics(statistics, output_path):
    statistics_path = output_path / "statistics.json"
    with statistics_path.open("w") as file:
        json.dump(statistics, file, indent=4)

def main():
    args = parse_args()
    input_path = Path(args.input)
    output_path = Path(args.output)
    output_path.mkdir(parents=True, exist_ok=True)
    statistics = {}
    for input_file in input_path.iterdir():
        if not input_file.is_file() or input_file.suffix.lower() == ".json":
            continue
        output_file = (output_path / input_file.stem).with_suffix(".out")
        command = [
            args.binary,
            args.summary,
            str(input_file),
            str(output_file),
            str(args.seed),
            *args.params,
        ]
        if args.top_k is not None:
            command.extend(["--top-k", str(args.top_k)])

        result = subprocess.run(
            command,
            check=True,
            capture_output=True,
            text=True,
        )
        statistics[input_file.stem] = parse_statistics(result.stdout)
    save_statistics(statistics, output_path)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
