# Heavy Hitters

This project contains a pipeline based on Snakemake for evaluating various heavy hitter algorithms (e.g. space saving, count sketch, misra-gries).

## Requirements

1. Python modules listed in `requirements.txt` (namely Snakemake)
2. g++ with support for C++20+

## Usage

The project is far from being finished but the intended workflow is as follows:
 
1. Modify `config.yaml` as needed
2. Run snakemake
3. Collect your results
