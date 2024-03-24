# Subtask 1: N <= 15, K <= 4
# Subtask 2: K = 2
# Sutbask 3: K = 3
# Subtask 4: N, K <= 200
# Subtask 5: N, K <= 2 000
# Subtask 6: N, K <= 200 000

# generator args: N, K, T_rage, zones
# zones should be <= K
# validator args: NMAX, KMAX, NKMAX

# Subtask 1, N <= 15, K <= 4
n_values=(7 10 12 14 15 25 1000 25000 50000 196969 200000 25 1000 25000 170000 196969 200000 50 75 125 169 200 200 200 200 1000 1500 2000 2000 2000 10000 45699 75069 96969 175069 200000 200000 200000)
k_values=(2 4 3 4 4 2 2 2 2 2 2 3 3 3 3 3 3 14 16 100 57 40 15 100 175 500 300 15 75 1000 500 7500 20000 4500 25009 753 45000 173064)
t_range_values=(3 8 4 4 12 10 100 12 50000 150 10 10 10 12 40 20000 10 5 10 100 15 5 10 55 200 5 10 15 200 25 15 200 17 7 200 24 17 250)
zones=(1 3 2 2 2 1 1 1 2 1 2 1 3 1 2 1 2 4 10 30 50 3 12 45 100 20 55 7 12 200 100 57 2403 433 215 500 33333 75693)

NMAX=15
KMAX=4
NKMAX=60

for i in `seq 0 3`; do
    echo $i
    ./generator1 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask1-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask1-${i}.in
    ./vlad_sol <  subtask1-${i}.in >  subtask1-${i}.out
    ./mity_sol <  subtask1-${i}.in > mity.out
    diff  subtask1-${i}.out mity.out || break
done
for i in `seq 4 4`; do
    echo $i
    ./generator2 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} >  subtask1-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} <  subtask1-${i}.in
    ./vlad_sol <  subtask1-${i}.in >  subtask1-${i}.out
    ./mity_sol <  subtask1-${i}.in > mity.out
    diff  subtask1-${i}.out mity.out || break
done

# # Subtask 2: K = 2
# n_values=(25 1000 25000 50000 50000 196969 200000)
# k_values=(2 2 2 2 2 2)
# t_range_values=(10 100 12 50000 150 10)
# zones=(1 1 1 2 1 2 1)

NMAX=200000
KMAX=2
NKMAX=400000

for i in `seq 5 8`; do
    echo $i
    ./generator1 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask2-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask2-${i}.in
    ./vlad_sol < subtask2-${i}.in > subtask2-${i}.out
    ./mity_sol < subtask2-${i}.in > mity.out
    diff subtask2-${i}.out mity.out || break
done
for i in `seq 9 10`; do
    echo $i
    ./generator2 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask2-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask2-${i}.in
    ./vlad_sol < subtask2-${i}.in > subtask2-${i}.out
    ./mity_sol < subtask2-${i}.in > mity.out
    diff subtask2-${i}.out mity.out || break
done

# Sutbask 3: K = 3
# n_values=(25 1000 25000 50000 170000 196969 200000)
# k_values=(3 3 3 3 3 3)
# t_range_values=(10 10 12 40 20000 10)
# zones=(1 3 1 2 1 2)

NMAX=200000
KMAX=3
NKMAX=600000

for i in `seq 11 14`; do
    echo $i
    ./generator1 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask3-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask3-${i}.in
    ./vlad_sol < subtask3-${i}.in > subtask3-${i}.out
    ./mity_sol < subtask3-${i}.in > mity.out
    diff subtask3-${i}.out mity.out || break
done
for i in `seq 15 16`; do
    echo $i
    ./generator2 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask3-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask3-${i}.in
    ./vlad_sol < subtask3-${i}.in > subtask3-${i}.out
    ./mity_sol < subtask3-${i}.in > mity.out
    diff subtask3-${i}.out mity.out || break
done

# Subtask 4: N, K <= 200
# n_values=(50 75 125 169 200 200 200 200)
# k_values=(14 16 100 57 40 15 100 175)
# t_range_values=(5 10 100 15 5 10 55 200)
# zones=(4 10 30 50 3 12 45 100)

NMAX=200
KMAX=200
NKMAX=40000

for i in `seq 17 19`; do
    echo $i
    ./generator1 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask4-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask4-${i}.in
    ./vlad_sol < subtask4-${i}.in > subtask4-${i}.out
    ./mity_sol < subtask4-${i}.in > mity.out
    diff subtask4-${i}.out mity.out || break
done
for i in `seq 20 20`; do
    echo $i
    ./generator2 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask4-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask4-${i}.in
    ./vlad_sol < subtask4-${i}.in > subtask4-${i}.out
    ./mity_sol < subtask4-${i}.in > mity.out
    diff subtask4-${i}.out mity.out || break
done
for i in `seq 21 22`; do
    echo $i
    ./generator2 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask4-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask4-${i}.in
    ./vlad_sol < subtask4-${i}.in > subtask4-${i}.out
    ./mity_sol < subtask4-${i}.in > mity.out
    diff subtask4-${i}.out mity.out || break
done
for i in `seq 23 24`; do
    echo $i
    ./generator1 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask4-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask4-${i}.in
    ./vlad_sol < subtask4-${i}.in > subtask4-${i}.out
    ./mity_sol < subtask4-${i}.in > mity.out
    diff subtask4-${i}.out mity.out || break
done

# # Subtask 5: N, K <= 2000
# # n_values=(1000 1500 2000 2000 2000)
# # k_values=(500 300 15 75 1000)
# # t_range_values=(5 10 15 200 25)
# # zones=(20 55 7 12 200)

NMAX=2000
KMAX=2000
NKMAX=4000000

for i in `seq 25 27`; do
    echo $i
    ./generator1 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask5-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask5-${i}.in
    ./vlad_sol < subtask5-${i}.in > subtask5-${i}.out
    ./mity_sol < subtask5-${i}.in > mity.out
    diff subtask5-${i}.out mity.out || break
done
for i in `seq 28 29`; do
    echo $i
    ./generator2 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask5-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask5-${i}.in
    ./vlad_sol < subtask5-${i}.in > subtask5-${i}.out
    ./mity_sol < subtask5-${i}.in > mity.out
    diff subtask5-${i}.out mity.out || break
done

# # Subtask 6: N, K <= 200 000

# # n_values=(10000 45699 75069 96969 175069 200000 200000 200000)
# # k_values=(500 7500 20000 4500 25009 753 45000 173064)
# # t_range_values=(15 200 17 7 200 24 17 250)
# # zones=(100 57 2403 433 215 500 33333 75693)

NMAX=200000
KMAX=200000
NKMAX=40000000000

for i in `seq 30 35`; do
    echo $i
    ./generator1 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask6-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask6-${i}.in
    ./vlad_sol < subtask6-${i}.in > subtask6-${i}.out
    ./mity_sol < subtask6-${i}.in > mity.out
    diff subtask6-${i}.out mity.out || break
done
for i in `seq 36 37`; do
    echo $i
    ./generator2 ${n_values[$i]} ${k_values[$i]} ${t_range_values[$i]} ${zones[$i]} > subtask6-${i}.in
    ./validator ${NMAX} ${KMAX} ${NKMAX} < subtask6-${i}.in
    ./vlad_sol < subtask6-${i}.in > subtask6-${i}.out
    ./mity_sol < subtask6-${i}.in > mity.out
    diff subtask6-${i}.out mity.out || break
done