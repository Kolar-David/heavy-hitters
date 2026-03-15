# Config

configfile: "config.yaml"

# Functions

def cli_params_for_instance(wc):
    params = config["instances"][wc.instance]["params"]
    params = [str(val) for val in params]
    return " ".join(params)

def all_evaluation_targets():
    targets = []
    for exp_name, exp_cfg in config["experiments"].items():
        targets.extend(
            expand(
                "evaluations/{instance}/{datasetname}/seed_{seed}",
                instance=exp_cfg["instances"],
                datasetname=exp_cfg["datasets"],
                seed=exp_cfg["seeds"],
            )
        )

    return sorted(set(targets))

# Lists

DATASET_NAMES = list(config["datasets"].keys())
ALGORITHMS = ["misra-gries"]

# Rules

rule all:
    input:
        all_evaluation_targets(),
        #expand("datasets/{datasetname}", datasetname=DATASET_NAMES),
        #expand("build/{alg}", alg=ALGORITHMS),

rule build_algorithms:
    input:
        src="src/{alg}.cpp"
    output:
        exe="build/{alg}"
    shell:
        r"""
        mkdir -p build
        g++-13 -O3 -std=c++20 {input.src} src/sketch.cpp -o {output.exe}
        """

rule run_algorithm:
    input:
        run_script="scripts/run_algorithm.py",
        exe=lambda wc: f"build/{config['instances'][wc.instance]['binary']}",
        dataset="datasets/{datasetname}"
    output:
        outdir=directory("evaluations/{instance}/{datasetname}/seed_{seed}")
    params:
        cli_args=cli_params_for_instance,
    shell:
        r"""scripts/run_algorithm.py --binary {input.exe:q} --input {input.dataset:q} --output {output.outdir} --params {params.cli_args} --seed {wildcards.seed}"""

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


