n_values=(354 500 899 1000 1000 45000 84321 75000 94332 100000)
m_values=(1000 4000 1243 1234 4000 84032 100000 100000 150000 194500)
r_values=(123 943 234 399 399 10000 12123 15432 12342 123)

for i in `seq 0 4`; do
    echo $i
    ./generator ${n_values[$i]} ${m_values[$i]} ${r_values[$i]} > subtask1-${i}.in
    ./sol_vlad < subtask1-${i}.in > subtask1-${i}.out
    ./daniel < subtask1-${i}.in > daniel.out
    diff subtask1-${i}.out daniel.out || break
done

for i in `seq 5 9`; do
    echo $i
    time ./generator ${n_values[$i]} ${m_values[$i]} ${r_values[$i]} > subtask2-${i}.in
    time ./sol_vlad < subtask2-${i}.in > subtask2-${i}.out
    time ./daniel < subtask2-${i}.in > daniel.out
    diff subtask2-${i}.out daniel.out || break
done