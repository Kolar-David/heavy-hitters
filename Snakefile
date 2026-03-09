configfile: "config.yaml"

SET_NAMES = list(config["datasets"].keys())


rule all:
    input:
        expand("datasets/{setname}", setname=SET_NAMES)


rule generate_dataset:
    output:
        outdir=directory("datasets/{setname}")
    params:
        distribution=lambda wc: config["datasets"][wc.setname]["distribution"],
        seed=lambda wc: config["datasets"][wc.setname]["seed"],
        file_number=lambda wc: config["datasets"][wc.setname]["file_number"],
        n=lambda wc: config["datasets"][wc.setname]["n"],
        param=lambda wc: config["datasets"][wc.setname]["param"]
    shell:
        r"""
        scripts/generator.py \
            --distribution {params.distribution} \
            -n {params.n} \
            --param {params.param} \
            --seed {params.seed} \
            --file-number {params.file_number} \
            --out {output.outdir}
        """
