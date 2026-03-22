#!/usr/bin/env python3
import argparse
import json
from pathlib import Path
from datetime import datetime, timezone
import numpy as np

def generate_seed_if_missing(seed):
    if seed is not None:
        return int(seed)
    return int(np.random.SeedSequence().entropy)

def float_to_filename_format(param):
    s = f"{param:.3f}"
    s = s.rstrip("0").rstrip(".")
    s = s.replace(".", "p")
    return s

def sample(dist, param, n, generator):
    dist = dist.lower()
    n = int(n)
    if dist == "uniform":
        m = int(param)
        return generator.integers(low=0, high=m, size=n, dtype=np.int64)

    if dist == "zipf":
        a = float(param)
        return generator.zipf(a=a, size=n).astype(np.int64)

    raise ValueError(f"Unsupported distribution: {dist}!. Use 'uniform' or 'zipf'.")

def check_if_directory_is_empty(path):
    if (not path.is_dir()):
        return
    else:
        if any(path.iterdir()):
            raise ValueError("Directory is not empty!")


def write_numbers(out_path, data):
    out_path.parent.mkdir(parents=True, exist_ok=True)
    with out_path.open("w", encoding="utf-8") as f:
        for x in data:
            f.write(f"{int(x)}\n")


def write_log(out_path, data):
    with out_path.open("w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)
        f.write("\n")


def parse_args():
    p = argparse.ArgumentParser(description="Generate samples from uniform or zipf distribution using NumPy.")
    p.add_argument(
        "--distribution",
        required=True,
        choices=["uniform", "zipf"],
        help="Distribution to sample from.",
    )
    p.add_argument(
        "-n",
        required=True,
        help="Number of samples.",
    )
    p.add_argument(
        "--param",
        default=1.1,
        help="Distribution parameter.",
    )
    p.add_argument(
        "--output",
        default="./outputs",
        help="Output directory path where files will be saved.",
    )
    p.add_argument(
        "--file-number",
        default=1,
        help="Number of files to generate.",
    )
    p.add_argument(
        "--seed",
        default=None,
        help="Random seed. If omitted, it is generated automatically.",
    )
    return p.parse_args()


def main():
    args = parse_args()
    check_if_directory_is_empty(Path(args.output))
    seed = generate_seed_if_missing(args.seed)
    random_generator = np.random.default_rng(seed)
    if args.distribution == "uniform":
        param = int(round(args.param))
        param_file_name = param
    else:
        param = float(args.param)
        param_file_name = float_to_filename_format(param)

    for i in range(int(args.file_number)):
        data = sample(args.distribution, param, args.n, random_generator)
        out_path = Path(args.output) / f"{i}_{args.distribution}_{param_file_name}.in"
        write_numbers(out_path, data)
    log_data = {
        "timestamp": datetime.now(timezone.utc).isoformat(),
        "distribution": args.distribution,
        "param": param,
        "n": args.n,
        "out": str(out_path),
        "file_number": args.file_number,
        "seed": seed,
    }
    outpath = Path(args.output)
    log_path = outpath / f"{outpath.name}.json"
    #write_log(log_path, log_data)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
