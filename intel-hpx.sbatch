#!/bin/bash
#SBATCH -N 1
#SBATCH --time=3:59:00
#SBATCH -p skylake-36core 
#SBATCH --job-name=hpx-32numa-%j
#SBATCH --output=hpx-32numa-%j.txt
#SBATCH --error=error-%j.txt

module load gcc

date
./benchmark.sh intel
date


