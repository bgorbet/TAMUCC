#Install Bioconductor and required Bioc packages
if (!requireNamespace("BiocManager", quietly = TRUE))
    install.packages("BiocManager")
BiocManager::install(version = "3.12")

BiocManager::install("RTCGA")

library("RTCGA")
installTCGA(packages = c("RTCGA.mutations",
                            "RTCGA.clinical",
                            "RTCGA.rnaseq",
                            "RTCGA.mRNA",
                            "RTCGA.miRNASeq",
                            "RTCGA.methylation",
                            "RTCGA.CNV"))
