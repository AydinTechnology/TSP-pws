mpicc main.c parsing_waypoints.c variables.c permutations.c geometry_functions.c -o TSP -lm

#run with 1 CPU
#mpirun -np 1 ./TSP waypoints.txt
