mpicc main.c parsing_waypoints.c variables.c permutations.c geometry_functions.c -o TSP -lm

#example to run with 1 CPU (can be any)
#systemd-inhibit time mpirun -np 1 --hostfile hostfile ./TSP waypoints.txt
