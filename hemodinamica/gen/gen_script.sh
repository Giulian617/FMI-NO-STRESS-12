n_values=(10 25 33 42 47 50 73 100 150 356 500 540 750 800 970 1000)
m_values=(7 12 30 14 50 50 100 93 150 200 700 500 785 699 999 1000)

for i in `seq 0 5`; do
    echo $i
    ./generator ${n_values[$i]} ${m_values[$i]} > subtask1-${i}.in
    ./sol < subtask1-${i}.in > subtask1-${i}.out
done

for i in `seq 6 15`; do
    echo $i
    ./generator ${n_values[$i]} ${m_values[$i]} > subtask2-${i}.in
    ./sol < subtask2-${i}.in > subtask2-${i}.out
done