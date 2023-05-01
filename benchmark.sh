#!/bin/bash

len=100000000
path=$(pwd)
# Taylor HPX parallel algorithms


for i in {0..1}
do
    data=""
    for j in {1..10}
    do
    result=$(srun ${path}/build/src/taylor_future ${len} 0.5 $i)  
    array=($result)
    IFS=',' read -ra my_array <<< "${array[0]}"
    data="$data ${my_array[1]}"
    done
    list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`);
    echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}" >> $1_taylor_future_median.csv
done

for i in {0..1}
do
    data=""
    for j in {1..10}
    do
    result=$(srun  ${path}/build/src/taylor_future_hpx ${len} 0.5 $i --hpx:threads=$i)
    array=($result)
    IFS=',' read -ra my_array <<< "${array[0]}"
    data="$data ${my_array[1]}"
    done
    list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`);
    echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}" >> $1_taylor_future_hpx_median.csv
done

for i in {1..1}
do
    data=""
    for j in {1..10}
    do	    
    result=$(srun  ${path}/build/src/taylor_par_hpx ${len} 0.5 --hpx:threads=$i)
    array=($result)
    IFS=',' read -ra my_array <<< "${array[0]}"
    data="$data ${my_array[1]}"
    done
    list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`);
    echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}" >>  $1_taylor_par_hpx_median.csv
done

for i in {1..1}
do
    data=""
    for j in {1..10}
    do
    result=$(srun  ${path}/build/src/taylor_future_coroutine_hpx ${len} 0.5 $i --hpx:threads=$i)
    array=($result)
    IFS=',' read -ra my_array <<< "${array[0]}"
    data="$data ${my_array[1]}"
    done
    list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`);
    echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}" >> $1_taylor_coroutine_hpx_median.csv
done


for i in {64..1}
do
    data=""
    for j in {1..10}
    do
    result=$(srun  ${path}/build/src/taylor_sender_receiver_hpx ${len} 0.5 $i --hpx:threads=$i)
    array=($result)
    IFS=',' read -ra my_array <<< "${array[0]}"
    data="$data ${my_array[1]}"
    done
    list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`);
    echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}" >> $1_taylor_sender_receiver_hpx_median.csv
done
