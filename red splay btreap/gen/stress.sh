for i in `seq 0 10000`; do
    echo $i
    ./gen_d+v 30 > data.in
    ./sol_vlad < data.in > dp.out
    ./vlad_bkt < data.in > bkt.out
    diff dp.out bkt.out || break
done