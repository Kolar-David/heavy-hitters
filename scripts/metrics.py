#!/usr/bin/env python3
import argparse
from pathlib import Path
import json

def parse_args():
    p = argparse.ArgumentParser(description="Compute precision, recall and F1 score.")
    p.add_argument(
        "--dataset",
        required=True,
        help="Original dataset.",
    )
    p.add_argument(
        "--solutions",
        required=True,
        help="Solutions to evaluate.",
    )
    p.add_argument(
        "-k",
        type=int,
        required=True,
        help="k",
    )
    p.add_argument(
        "--output",
        required=True,
        help="Output json file.",
    )
    return p.parse_args()


def get_top_k_vals_from_dict(counts, k):
    return {
        key
        for key, _ in sorted(counts.items(), key=lambda x: (-x[1], x[0]))[:k]
    }

def compute_top_k_hitters(input_path, k):
    counter = {}
    with open(input_path, "r") as file:
        for line in file:
            number = int(line)
            if number not in counter:
                counter[number] = 0
            counter[number] += 1
    return get_top_k_vals_from_dict(counter, k)

def get_top_k_from_solution(solution_path, k):
    counter = dict()
    with open(solution_path, "r") as file:
        for line in file:
            key, count = [int(val) for val in line.split()]
            counter[key] = count
    if (len(counter) > k):
        raise ValueError(f"file {solution_path} contains more than {k} heavy hitters!")
    return set(counter.keys())


def compute_metrics(input_path, solution_path, k):
    top_k_real_vals = compute_top_k_hitters(input_path, k)
    top_k_solution_vals = get_top_k_from_solution(solution_path, k)
    TP = 0
    for val in top_k_solution_vals:
        if (val in top_k_real_vals):
            TP += 1
    FP = len(top_k_solution_vals) - TP
    FN = 0
    for val in top_k_real_vals:
        if (val not in top_k_solution_vals):
            FN += 1
    if (TP + FP == 0):
        precision = 0
    else:
        precision = TP / (TP + FP)

    if (TP + FN == 0):
        recall = 0
    else:
        recall = TP / (TP + FN)

    if (precision == 0 or recall == 0):
        f1 = 0
    else:
        f1 = 2 / (1/precision + 1/recall)

    return {"precision": precision, "recall" : recall, "f1" : f1}

def store_metrics_to_json(path, data):
    with path.open("w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)
        f.write("\n")

def main():
    args = parse_args()
    dataset_path = Path(args.dataset)
    solutions_path = Path(args.solutions)
    output_path = Path(args.output)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    dict_with_metrics = {}
    for input_file_path in dataset_path.iterdir():
        solution_file_path = solutions_path / input_file_path.name
        if not solution_file_path.is_file():
            raise ValueError(f"File {solution_file_path} with a solution of {input_file_path} is missing!")
        metrics = compute_metrics(input_file_path, solution_file_path, args.k)
        dict_with_metrics[solution_file_path.name] = metrics
    store_metrics_to_json(output_path, dict_with_metrics)

if __name__ == "__main__":
    raise SystemExit(main())