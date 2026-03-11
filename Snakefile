configfile: "config.yaml"

DATASET_NAMES = list(config["datasets"].keys())
ALGORITHMS = ["misra-gries"]


rule all:
    input:
        expand("datasets/{datasetname}", datasetname=DATASET_NAMES),
        expand("build/{alg}", alg=ALGORITHMS)

rule build_algorithms:
    input:
        src="src/{alg}.cpp"
    output:
        exe="build/{alg}"
    shell:
        r"""
        mkdir -p build
        g++ -O3 -std=c++20 {input.src} src/sketch.cpp -o {output.exe}
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
        {generator} \
            --distribution {params.distribution} \
            -n {params.n} \
            --param {params.param} \
            --seed {params.seed} \
            --file-number {params.file_number} \
            --out {output.outdir}
        """
