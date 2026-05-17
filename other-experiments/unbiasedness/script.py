#!/usr/bin/env python3
from itertools import product


# Universe: U = {0, 1, 2, 3}
# Hash functions h_i and g_i: Tabulation hash from U to {0, 1}

def all_tabulation_functions():
    """Generate all tabulation hash functions from U to {0, 1}"""
    return list(product([0, 1], repeat=4))


def eval_tabulation_function(func, x):
    """Evaluate a tabulation hash function on x in U."""
    t0_0, t0_1, t1_0, t1_1 = func
    x0 = x & 1
    x1 = (x >> 1) & 1
    t0_value = t0_0 if x0 == 0 else t0_1
    t1_value = t1_0 if x1 == 0 else t1_1
    return t0_value ^ t1_value


def eval_sign_function(func, x):
    bit = eval_tabulation_function(func, x)
    return 1 if bit == 0 else -1



def row_estimate(v, queried_item, h_func, g_func, bucket_count):
    counters = [0 for _ in range(bucket_count)]
    for x, frequency in enumerate(v):
        bucket = eval_tabulation_function(h_func, x)
        sign = eval_sign_function(g_func, x)
        counters[bucket] += sign * frequency
    queried_bucket = eval_tabulation_function(h_func, queried_item)
    queried_sign = eval_sign_function(g_func, queried_item)
    return queried_sign * counters[queried_bucket]


def median_of_three(a, b, c):
    return sorted([a, b, c])[1]


def exact_expectation_one_row(v, queried_item, bucket_count=2):
    functions = all_tabulation_functions()
    total = 0
    count = 0
    for h_func in functions:
        for g_func in functions:
            estimate = row_estimate(v, queried_item, h_func, g_func, bucket_count)
            total += estimate
            count += 1
    return total / count


def exact_expectation_three_rows_median(v, queried_item, bucket_count=2):
    """Enumerate all choices of three independent rows."""
    functions = all_tabulation_functions()
    row_choices = list(product(functions, functions))
    total = 0
    count = 0
    for row1 in row_choices:
        h1, g1 = row1
        e1 = row_estimate(v, queried_item, h1, g1, bucket_count)
        for row2 in row_choices:
            h2, g2 = row2
            e2 = row_estimate(v, queried_item, h2, g2, bucket_count)
            for row3 in row_choices:
                h3, g3 = row3
                e3 = row_estimate(v, queried_item, h3, g3, bucket_count)
                estimate = median_of_three(e1, e2, e3)
                total += estimate
                count += 1
    return total / count

def run_experiment():
    # Frequency vector over U = {0, 1, 2, 3}
    v = [5, 2, 1, 1]
    queried_items = [0]
    for queried_item in queried_items:
        true_frequency = v[queried_item]
        one_row_expectation = exact_expectation_one_row(v, queried_item)
        three_row_median_expectation = exact_expectation_three_rows_median(v, queried_item)
        print(f"item: {queried_item}")
        print(f"true frequency: {true_frequency}")
        print(f"one-row expectation: {one_row_expectation}")
        print(f"three-row median expectation: {three_row_median_expectation}")
        print(f"one-row bias: {one_row_expectation - true_frequency}")
        print(
            "three-row median bias: "
            f"{three_row_median_expectation - true_frequency}"
        )
        print()

if __name__ == "__main__":
    run_experiment()
