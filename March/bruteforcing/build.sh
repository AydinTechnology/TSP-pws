mpicc main.c parsing_waypoints.c variables.c permutations.c geometry_functions.c -o TSP -lm

#example to run with 1 CPU (can be any)
#mpirun -np 1 --tag-output --hostfile hostfile ./TSP waypoints.txt
