n_values=(1 2 3 5 7 9 12 14 17 20 25 100 2500 5000 10000 20000 35000 54322 64000 85000 87202)

# n <= 11
# n <= 31
# n <= 99615

for i in `seq 0 5`; do
    echo ${n_values[$i]}
    ./gen_d+v ${n_values[$i]} > subtask1-${i}.in
    ./sol_vlad < subtask1-${i}.in > subtask1-${i}.out
    ./vlad_bkt < subtask1-${i}.in > bkt.out
    diff subtask1-${i}.out bkt.out || break
done

for i in `seq 6 10`; do
    echo ${n_values[$i]}
    ./gen_d+v ${n_values[$i]} > subtask1-${i}.in
    ./sol_vlad < subtask1-${i}.in > subtask1-${i}.out
    ./vlad_bkt < subtask1-${i}.in > bkt.out
    diff subtask1-${i}.out bkt.out || break
done

for i in `seq 18 20`; do
    echo $i
    ./gen_d+v ${n_values[$i]} > subtask1-${i}.in
    ./sol_vlad < subtask1-${i}.in > subtask1-${i}.out
    time ./sol_vlad_v2 < subtask1-${i}.in > v2.out
    # ./vlad_bkt < subtask1-${i}.in > bkt.out
    diff subtask1-${i}.out v2.out || break
done