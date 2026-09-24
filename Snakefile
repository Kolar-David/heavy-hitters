# Imports

import glob

# Config

configfile: "config.yaml"

# Functions

# Convert instance parameters from config to a CLI argument string
def cli_params_for_instance(wc):
    params = config["instances"][wc.instance]["params"]
    params = [str(val) for val in params]
    return " ".join(params)

# Collect all summary evaluation targets required by experiments
def all_evaluation_targets():
    targets = []

    for exp_name, exp_cfg in config["experiments"].items():
        targets.extend(
            expand(
                "evaluations/{instance}/{datasetname}/{k}/seed_{seed}",
                instance=exp_cfg["instances"],
                datasetname=exp_cfg["datasets"],
                k=exp_cfg["k"],
                seed=exp_cfg["seeds"],
            )
        )
    return sorted(set(targets))


# Collect all unique metric files required by experiments
def all_metric_targets():
    targets = []

    for exp_name, exp_cfg in config["experiments"].items():
        targets.extend(
            expand(
                "metrics/{experiment}/{instance}/{datasetname}/{k}/seed_{seed}.json",
                experiment=[exp_name],
                instance=exp_cfg["instances"],
                datasetname=exp_cfg["datasets"],
                k=exp_cfg["k"],
                seed=exp_cfg["seeds"],
            )
        )

    return sorted(set(targets))

CPP_SOURCES = glob.glob("src/**/*.cpp", recursive=True)
CPP_HEADERS = glob.glob("src/**/*.h", recursive=True)

# Rules

rule all:
    input:
        all_metric_targets(),
        "other-experiments/unbiasedness/result.txt"


rule compute_metrics:
    input:
        evaluation=directory(
            "evaluations/{instance}/{datasetname}/{k}/seed_{seed}"
        ),
        dataset=directory("datasets/{datasetname}"),
        metrics="scripts/metrics.py"
    output:
        "metrics/{experiment}/{instance}/{datasetname}/{k}/seed_{seed}.json"
    shell:
        r"""
        {input.metrics} \
            --dataset {input.dataset:q} \
            --solutions {input.evaluation:q} \
            --output {output:q} \
            -k {wildcards.k}
        """

# Build the common summary runner using CMake
rule build_runner:
    input:
        "CMakeLists.txt",
        CPP_SOURCES,
        CPP_HEADERS
    output:
        exe="build/summary-runner"
    shell:
        r"""
        cmake -S . -B build -G Ninja
        cmake --build build --target summary-runner
        """


rule run_algorithm:
    input:
        run_script="scripts/run_algorithm.py",
        runner="build/summary-runner",
        dataset="datasets/{datasetname}"
    output:
        outdir=directory(
            "evaluations/{instance}/{datasetname}/{k}/seed_{seed}"
        )
    params:
        summary=lambda wc: config["instances"][wc.instance]["summary"],
        cli_args=cli_params_for_instance
    shell:
        r"""
        {input.run_script} \
            --binary {input.runner:q} \
            --summary {params.summary} \
            --input {input.dataset:q} \
            --output {output.outdir:q} \
            --params {params.cli_args} \
            --seed {wildcards.seed} \
            --top-k {wildcards.k}
        """

rule generate_dataset:
    input:
        generator="scripts/generator.py"
    output:
        outdir=directory("datasets/{datasetname}")
    params:
        distribution=lambda wc: config["datasets"][wc.datasetname]["distribution"],
        seed=lambda wc: config["datasets"][wc.datasetname]["seed"],
        file_number=lambda wc: config["datasets"][wc.datasetname]["file_number"],
        n=lambda wc: config["datasets"][wc.datasetname]["n"],
        param=lambda wc: config["datasets"][wc.datasetname]["param"]
    shell:
        r"""
        {input.generator} \
            --distribution {params.distribution} \
            -n {params.n} \
            --param {params.param} \
            --seed {params.seed} \
            --file-number {params.file_number} \
            --output {output.outdir}
        """


rule unbiasedness:
    input:
        script="other-experiments/unbiasedness/script.py"
    output:
        output_file="other-experiments/unbiasedness/result.txt"
    shell:
        r"""{input.script} > {output.output_file}"""
