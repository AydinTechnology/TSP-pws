#include <stdio.h>
#include <stdlib.h>
#include "geometry_functions.h"
#include "variables.h"

void nearest_neighbour(int n) {

    int *already_visited = calloc(n, sizeof(int));  //we need this array zero-initialized so that we won't be confused by potential garbage when checking if we visited everything
    int lowest_from_current_index = 0;
    double lowest_from_current_dist;
    int current_location;

    route[0] = 0;   //we already know these (these are our spawnpoint)
    already_visited[0] = 1;
    route[n] = 0;

    for(int route_position = 1; route_position < n; route_position++) {
        lowest_from_current_dist = 1e9;
        current_location = lowest_from_current_index;

        for(int i = 0; i < n; i++) {        //closest to us check
            if(i == current_location) continue;

            double temp = 1e9;
            if(already_visited[i] == 0) {
                temp = calculate_distance(waypoint_x[current_location], waypoint_y[current_location], waypoint_x[i], waypoint_y[i]);
            }

            if(temp < lowest_from_current_dist) {
                lowest_from_current_dist = temp;
                lowest_from_current_index = i;
            }
        }

        //flag the result from our "closest to us" check as already visited
        already_visited[lowest_from_current_index] = 1;
        //also store it
        route[route_position] = lowest_from_current_index;

        int test = 0;   //have we had all waypoints
        for(int i = 0; i < n; i++) {
            test += already_visited[i];
            if(test == n) break;
        }
    }

    //we now have a nearest_neighbour route, time to significantly improve it with 2-opt
    n++;    //we now increment n by 1 to accurately reflect the amount of elements within our route instead of the amount of waypoints

    int new_improvement = 1;    //acts like a toggle for once we finally can't find new improvements to stop iterating
    while(new_improvement) {
        new_improvement = 0;

        for(int i = 0; i < n - 1; i++) {
            for(int j = i + 2; j < n; j++) {
                int a = route[i];
                int b = route[(i + 1) % n];
                int c = route[j];
                int d = route[(j + 1) % n];

                double prev_dist = calculate_distance(waypoint_x[a], waypoint_y[a], waypoint_x[b], waypoint_y[b]) + calculate_distance(waypoint_x[c], waypoint_y[c], waypoint_x[d], waypoint_y[d]);

                double new_dist = calculate_distance(waypoint_x[a], waypoint_y[a], waypoint_x[c], waypoint_y[c]) + calculate_distance(waypoint_x[b], waypoint_y[b], waypoint_x[d], waypoint_y[d]);

                if(new_dist < prev_dist) {
                    swap_waypoints(route, i + 1, j);
                    new_improvement = 1;
                }
            }
        }
    }

    printf("\nThe optimal route is ");
    array_printing(route, n);
    printf("with a distance of %lf units.\n", find_total_distance_route(route, n-1));

    free(already_visited);
    return;
}
