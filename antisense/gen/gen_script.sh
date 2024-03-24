n_values=(10 35 42 100 375 1000 2000 5799 10000 45332 100000 200000)

for i in `seq 0 3`; do
    echo $i
    ./gen ${n_values[$i]} > subtask1-${i}.in
    ./sol_vlad < subtask1-${i}.in > subtask1-${i}.out
    ./mity < subtask1-${i}.in > mity.out
    diff subtask1-${i}.out mity.out || break
done

for i in `seq 4 6`; do
    echo $i
    ./gen ${n_values[$i]} ${m_values[$i]} > subtask2-${i}.in
    ./sol_vlad < subtask2-${i}.in > subtask2-${i}.out
    ./mity < subtask2-${i}.in > mity.out
    diff subtask2-${i}.out mity.out || break
done

for i in `seq 7 11`; do
    echo $i
    ./gen ${n_values[$i]} ${m_values[$i]} > subtask3-${i}.in
    ./sol_vlad < subtask3-${i}.in > subtask3-${i}.out
    ./mity < subtask3-${i}.in > mity.out
    diff subtask3-${i}.out mity.out || break
done