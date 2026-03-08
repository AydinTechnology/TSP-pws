//please make sure your system has OpenMPI installed
//if building from source, you'll also need the necessary OpenMPI libraries
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include "parsing_waypoints.h"
#include "variables.h"
#include "permutations.h"
#include "geometry_functions.h"

int main(int argc, char *argv[]) {
//===================== initialising (parsing waypoints, getting OpenMPI ready etc.)
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(argc != 2) {                                                 //if the user executes the program but gives wrong/no arguments, make a problem of it
        printf("Please provide a text file with waypoints.\n");
        printf("Example input: %s waypoints.txt\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    int waypoints_parsed_count = parse_waypoints(argv[1]); //read waypoints and show to the user what they look like in memory (makes debugging the input file for the user a lot lot easier)
    int size_array = waypoints_parsed_count - 1;
    printf("Amount of waypoints parsed: %i\n\n", waypoints_parsed_count);
    for(int i = 0; i < waypoints_parsed_count; i++) {
        printf("%lf, %lf\n", waypoint_x[i], waypoint_y[i]);
    }

//===================== actual calculating (creating arrays, permuting, running algorithm etc.)
    printf("Calculating...\n\n");

    temporary_route = malloc(sizeof(int) * (size_array));
    optimal_route = malloc(sizeof(int) * (waypoints_parsed_count));

    long long total_permutations = 1;             //simple factorial so that we know our maximum of permutations to perform (n-1)!/2 (size_array is equal to (n-1))
    for(int i = 1; i <= size_array; i++) {
        total_permutations *= i;
    }

    for(long long i = rank; i < total_permutations; i += size) {
        permute(size_array, i);
    }

//===================== check all "optimal_routes" for the best one
    int *gathered = NULL;
    if(rank == 0) {
        gathered = malloc(waypoints_parsed_count * size * sizeof(int));
    }

    MPI_Gather(
        optimal_route,                      // send buffer
        waypoints_parsed_count,             // elements sent
        MPI_INT,
        gathered,                           // receive buffer (root only)
        waypoints_parsed_count,
        MPI_INT,
        0,                                  //send everything to the 0-th node
        MPI_COMM_WORLD);

    if(rank == 0) {
        for(int i = 0; i < size; i++) {
            double test_distance = find_total_distance_route(gathered+waypoints_parsed_count*i+1, size_array); //maybe this route is shorter than the one we currently have

            if(test_distance < optimal_distance) {  //we have found a route which is more optimal than the one currently held by node 0 so replace it
                    optimal_distance = test_distance;
                    optimal_route[0] = 1;   //we start from our first waypoint
                    memcpy(&optimal_route+sizeof(int), &gathered+waypoints_parsed_count*i, sizeof(int)*size_array);

                    printf("The optimal route is ");
                    array_printing(optimal_route, waypoints_parsed_count);
                    printf("with a distance of %lf units.\n", optimal_distance);
            }
        }
        free(gathered);
    }

    free(waypoint_x);   //these dynamic arrays have been initialised in the parse_waypoints() call, but these must also be freed again
    free(waypoint_y);
    free(temporary_route);
    free(optimal_route);
    MPI_Finalize();
    return 0;
}
