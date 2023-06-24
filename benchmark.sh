#!/bin/bash

len=100000000
path=$(pwd)

itr = 25

if [ $1 = "hifiveu" ]; then
itr = 4
elif [ $1 = "star64" ]; then
itr = 4
fi

for i in {itr..1}
do
    data=""
    for j in {1..10}
    do
    if [ $1 = "star64" ]; then
       result=$(${path}/build/src/taylor_future ${len} 0.5 $i)
    elif [ $1 = "hifiveu" ]; then
       result=$(srun --cpus-per-task=4 --ntasks-per-node=1 --ntasks-per-core=1 ${path}/build/src/taylor_future ${len} 0.5 $i)  
    else
       result=$(srun ${path}/build/src/taylor_future ${len} 0.5 $i)
    fi
    array=($result)
    IFS=',' read -ra my_array <<< "${array[0]}"
    data="$data ${my_array[1]}"
    done
    list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`)
    echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}" >> $1_taylor_future_median.csv
done

for i in {itr..1}
do
    data=""
    for j in {1..10}
    do
    if [ $1 = "star64" ]; then
       result=$(${path}/build/src/taylor_future_hpx ${len} 0.5 $i --hpx:threads=$i)
    elif [ $1 = "hifiveu" ]; then
       result=$(srun --cpus-per-task=4 --ntasks-per-node=1 --ntasks-per-core=1 ${path}/build/src/taylor_future ${len} 0.5 $i)  
    else
       result=$(srun ${path}/build/src/taylor_future ${len} 0.5 $i)
    fi
    array=($result)
    IFS=',' read -ra my_array <<< "${array[0]}"
    data="$data ${my_array[1]}"
    done
    list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`);
    echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}" >> $1_taylor_future_hpx_median.csv
done

for i in {itr..1}
do
    data=""
    for j in {1..10}
    do	    
    if [ $1 = "star64" ]; then
       result=$(${path}/build/src/taylor_par_hpx ${len} 0.5 --hpx:threads=$i)
    elif [ $1 = "hifiveu" ]; then
       result=$(srun --cpus-per-task=4 --ntasks-per-node=1 --ntasks-per-core=1 ${path}/build/src/taylor_future ${len} 0.5 $i)  
    else
       result=$(srun ${path}/build/src/taylor_future ${len} 0.5 $i)
    fi
    array=($result)
    IFS=',' read -ra my_array <<< "${array[0]}"
    data="$data ${my_array[1]}"
    done
    list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`);
    echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}" >>  $1_taylor_par_hpx_median.csv
done

for i in {itr..1}
do
    data=""
    for j in {1..10}
    do
    if [ $1 = "star64" ]; then
       result=$(${path}/build/src/taylor_future_coroutine_hpx ${len} 0.5 $i --hpx:threads=$i)
    elif [ $1 = "hifiveu" ]; then
       result=$(srun --cpus-per-task=4 --ntasks-per-node=1 --ntasks-per-core=1 ${path}/build/src/taylor_future ${len} 0.5 $i)  
    else
       result=$(srun ${path}/build/src/taylor_future ${len} 0.5 $i)
    fi
    array=($result)
    IFS=',' read -ra my_array <<< "${array[0]}"
    data="$data ${my_array[1]}"
    done
    list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`);
    echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}" >> $1_taylor_coroutine_hpx_median.csv
done


for i in {itr..1}
do
    data=""
    for j in {1..10}
    do
    if [ $1 = "star64" ]; then
       result=$(${path}/build/src/taylor_sender_receiver_hpx ${len} 0.5 $i --hpx:threads=$i)
    elif [ $1 = "hifiveu" ]; then
       result=$(srun --cpus-per-task=4 --ntasks-per-node=1 --ntasks-per-core=1 ${path}/build/src/taylor_future ${len} 0.5 $i)  
    else
       result=$(srun ${path}/build/src/taylor_future ${len} 0.5 $i)
    fi
    array=($result)
    IFS=',' read -ra my_array <<< "${array[0]}"
    data="$data ${my_array[1]}"
    done
    list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`);
    echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}" >> $1_taylor_sender_receiver_hpx_median.csv
done
