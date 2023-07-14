num=100000000
for exe in taylor_future taylor_future_coroutine_hpx taylor_future_hpx taylor_par_hpx taylor_sender_receiver_hpx
do
    echo "RUNNING: $exe"
    for n in 1 2 4 8 16 20
    do
        for iter in $(seq 1 9)
        do
            f=data/${exe}_${num}_${n}_${iter}.csv
            if [ ! -r $f ]
            then
                mkdir -p $(dirname $f)
                echo $f | grep hpx > /dev/null
                if [ $? = 0 ]
                then
                    echo "  ./build/src/$exe --hpx:t=$n $num 0.5 $n"
                    ./build/src/$exe --hpx:t=$n $num 0.5 $n > $f
                else
                    echo "  ./build/src/$exe $num 0.5 $n"
                    ./build/src/$exe $num 0.5 $n > $f
                fi
            fi
        done
    done
done
