#!/bin/bash
#SBATCH -N 1
#SBATCH --time=3:59:00
#SBATCH -p short 
#SBATCH --job-name=hpx-taylor-%j
#SBATCH --output=hpx-taylor-%j.txt
#SBATCH --error=error-hpx_taylor-%j.txt

#module load gcc/12.1.0

date
./benchmark.sh star64
date


