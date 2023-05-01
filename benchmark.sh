#!/bin/bash

len=100000000
path=$(pwd)
# Taylor HPX parallel algorithms

for i in {36..1}
do
    ${path}/build/src/taylor_future ${len} 0.5 $i >> $1_taylor_future.csv
done

for i in {36..1}
do
	srun  ${path}/build/src/taylor_future_hpx ${len} 0.5 $i --hpx:threads=$i >> $1_taylor_future_hpx.csv
done

for i in {36..1}
do
    srun  ${path}/build/src/taylor_par_hpx ${len} 0.5 --hpx:threads=$i >> $1_taylor_par_hpx.csv
done
