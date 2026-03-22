//general architecture idea: generate all top-level branches ie. A->B... A->C... you get the idea
//then have all workers work out all possible branches
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include "two-smallest-edges.h"
#include "parsing_waypoints.h"
#include "geometry_functions.h"
#include "variables.h"
#include "branching.h"

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

//we do some pre calculating once instead of millions of time

    local_best_route = malloc(sizeof(int) * waypoints_parsed_count + 1);

    initialize_smallest_edges(waypoints_parsed_count);        //precompute smallest edges so it only has to be done once instead of possibly millions of times

    double bound = 0;   //find the initial lower bound or recursive branching function can work with
    for(int i = 0; i < waypoints_parsed_count; i++) {
        bound += first_smallest_edge[i] + second_smallest_edge[i];
        bound = bound / 2.0;
    }

//actual branching very cool!
    int total_top_level_branches = waypoints_parsed_count - 1;  //we do not go from A->A so we skip this one (similar idea to how we had all (n-1)! permutations in the bruteforcing)
    int branches_per_process = (total_top_level_branches + size - 1) / size;

    under_construction_route = calloc(waypoints_parsed_count, sizeof(int));
    visited_list = calloc(waypoints_parsed_count, sizeof(int));
    visited_list[0] = 1;

    for(int i = 1 + rank * branches_per_process; i < 1 + (rank + 1) * branches_per_process && i < waypoints_parsed_count; i++) {    // 1 + rank instead of just rank because we skip 0 (no A->A)
        under_construction_route[1] = i;
        visited_list[i] = 1;

        double d = calculate_distance(waypoint_x[0], waypoint_y[0], waypoint_x[i], waypoint_y[i]);


        recursive_branching(2, under_construction_route, visited_list, d, bound, &local_best_route_size, local_best_route, waypoints_parsed_count);

        visited_list[i] = 0;
    }


//===================== check all "optimal_routes" for the best one
    int *gathered = NULL;
    if(rank == 0) {
        gathered = malloc((waypoints_parsed_count+1) * size * sizeof(int));
    }

    MPI_Gather(
        local_best_route,                      // send buffer
        waypoints_parsed_count + 1,             // elements sent
        MPI_INT,
        gathered,                           // receive buffer (root only)
        waypoints_parsed_count + 1,
        MPI_INT,
        0,                                  //send everything to the 0-th node
        MPI_COMM_WORLD);

    if(rank == 0) {
        for(int i = 0; i < size; i++) {
            double test_distance = find_total_distance_route(gathered+((waypoints_parsed_count+1)*i), waypoints_parsed_count+1); //maybe this route is shorter than the one we currently have

            if(test_distance < local_best_route_size) {  //we have found a route which is more optimal than the one currently held by node 0 so replace it
                    local_best_route_size = test_distance;
                    for(int j = 0; j <= waypoints_parsed_count; j++) {
                        local_best_route[j] = gathered[j+((waypoints_parsed_count+1)*i)];
                    }

                    printf("The optimal route is ");
                    array_printing(local_best_route, waypoints_parsed_count+1);
                    printf("with a distance of %lf units.\n", local_best_route_size);
            }
        }
        free(gathered);
    }

    free(waypoint_x);
    free(waypoint_y);
    free(first_smallest_edge);
    free(second_smallest_edge);
    free(under_construction_route);
    free(visited_list);
    free(local_best_route);
    MPI_Finalize();
    return 0;
}
