//please make sure your system has OpenMPI installed
//if building from source, you'll also need the necessary OpenMPI libraries
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
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

    int waypoints_parsed_count = parse_waypoints(argv[1]); //read waypoints and show to the user what they look like in memory (makes debugging for the user a lot lot easier)
    int size_array = waypoints_parsed_count - 1;
    printf("Amount of waypoints parsed: %i\n\n", waypoints_parsed_count);
    for(int i = 0; i < waypoints_parsed_count; i++) {
        printf("%lf, %lf\n", waypoint_x[i], waypoint_y[i]);
    }

//===================== actual calculating (creating arrays, permuting, running algorithm etc.)
    printf("Calculating...\n\n");

    temporary_route = malloc(sizeof(int) * (size_array));
    optimal_route = malloc(sizeof(int) * (waypoints_parsed_count));

    int total_permutations = 1;
    for(int i = 1; i <= waypoints_parsed_count; i++) {
        total_permutations *= i;
    }   //simple factorial so that we know our maximum of permutations to perform

    for(int i = rank; i < total_permutations; i += size) {
        permute(size_array, i);
    }

//===================== check all "optimal_routes" for the best one
    if(rank == 0) {
        int *recvbuf = malloc(sizeof(int) * waypoints_parsed_count);

        for(int i = 1; i < size; i++) {
            MPI_Recv(recvbuf, sizeof(recvbuf), MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            int test_distance = find_total_distance_route(recvbuf, size_array);
            if(test_distance < optimal_distance) {
                optimal_route[0] = 1;
                for(int i = 1; i <= size_array; i++) {
                    optimal_route[i] = recvbuf[i];
                    optimal_distance = test_distance;
                }
            }
        }
        printf("The optimal route is ");
        array_printing(optimal_route, waypoints_parsed_count);
        printf("with a distance of %lf units.\n", optimal_distance);
        free(recvbuf);
    } else {
        MPI_Send(optimal_route, sizeof(optimal_route), MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    free(waypoint_x);   //these dynamic arrays have been initialised in the parse_waypoints() call, but these must also be freed again
    free(waypoint_y);
    free(temporary_route);
    free(optimal_route);
    MPI_Finalize();
    return 0;
}
