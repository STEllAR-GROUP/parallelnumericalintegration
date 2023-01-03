#!/bin/bash

len=1000000000
path=$(pwd)
# Taylor HPX parallel algorithms

for i in {1..5}
do
    start=`date +%s.%N`
    ${path}/build/src/taylor_future ${len} 0.5 $i
    end=`date +%s.%N`
    echo $i, $( echo "$end - $start" | bc -l ) >> $1_taylor_future.csv
done

for i in {1..5}
do
    start=`date +%s.%N`
    ${path}/build/src/taylor_future_hpx ${len} 0.5 $i
    end=`date +%s.%N`
    echo $i, $( echo "$end - $start" | bc -l ) >> $1_taylor_future_hpx.csv
done

for i in {1..5}
do
    start=`date +%s.%N`
    ${path}/build/src/taylor_par_hpx ${len} 0.5 --hpx:threads=$i
    end=`date +%s.%N`
    echo $i, $( echo "$end - $start" | bc -l ) >> $1_taylor_par_hpx.csv
done
