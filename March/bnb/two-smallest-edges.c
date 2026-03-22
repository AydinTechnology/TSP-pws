#include <stdlib.h>
#include <stdio.h>
#include "variables.h"
#include "geometry_functions.h"

void initialize_smallest_edges(int total_waypoints) {
    first_smallest_edge = malloc(sizeof(double) * total_waypoints);
    second_smallest_edge = malloc(sizeof(double) * total_waypoints);
    printf("\n");
    for(int current_waypoint = 0; current_waypoint < total_waypoints; current_waypoint++) {
        first_smallest_edge[current_waypoint] = -1;
        second_smallest_edge[current_waypoint] = -1;
        int firstrun = 1;
        for(int other = 0; other < total_waypoints; other++) {
            if(other == current_waypoint) continue; //we obviously cannot go from said city to the same city

            double dist_smallest_edges_calculation = calculate_distance(waypoint_x[current_waypoint], waypoint_y[current_waypoint], waypoint_x[other], waypoint_y[other]);

            if((dist_smallest_edges_calculation < first_smallest_edge[current_waypoint]) || firstrun) {
                firstrun = 0;
                second_smallest_edge[current_waypoint] = first_smallest_edge[current_waypoint];
                first_smallest_edge[current_waypoint] = dist_smallest_edges_calculation;
            } else if(dist_smallest_edges_calculation < second_smallest_edge[current_waypoint]) {       //it might still be shorter than the current one in the second
                second_smallest_edge[current_waypoint] = dist_smallest_edges_calculation;
            }
        }
        printf("%lf, %lf\n", first_smallest_edge[current_waypoint], second_smallest_edge[current_waypoint]);
    }
}
