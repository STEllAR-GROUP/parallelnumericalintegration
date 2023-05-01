#!/bin/bash
#SBATCH -N 1
#SBATCH --time=3:59:00
#SBATCH -p skylake-36core 
#SBATCH --job-name=hpx-32numa-%j
#SBATCH --output=hpx-32numa-%j.txt
#SBATCH --error=error-%j.txt

module load gcc

#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH//lustre/software/openmpi/arm21/4.1.2/lib


date
./benchmark.sh amd
date


