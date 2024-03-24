n_values=(4 7 9 10 100 356 533 790 1000 1000 33350 42000 57000 87992 100000 100000)
k_values=(2 3 7 7 45 100 354 680 997 572 12799 35000 50000 56995 56443 89899)

nmax=10
for i in `seq 0 3`; do
    echo $i
    ./generator ${n_values[$i]} ${k_values[$i]} ${nmax} > subtask1-${i}.in
    ./vlad_devide < subtask1-${i}.in > subtask1-${i}.out
done

nmax=1000
for i in `seq 4 9`; do
    echo $i
    ./generator ${n_values[$i]} ${k_values[$i]} ${nmax} > subtask2-${i}.in
    ./vlad_devide < subtask2-${i}.in > subtask2-${i}.out
done

nmax=100000
for i in `seq 10 15`; do
    echo $i
    ./generator ${n_values[$i]} ${k_values[$i]} ${nmax} > subtask3-${i}.in
    ./vlad_devide < subtask3-${i}.in > subtask3-${i}.out
done