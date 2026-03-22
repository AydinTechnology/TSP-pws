#include <stdio.h>
#include <stdlib.h>
#include "variables.h"
#include "geometry_functions.h"
#include "two-smallest-edges.h"

void recursive_branching(int depth, int under_construction_route[], int visited[], double distance_so_far, double bound, double *best_cost_local, int best_route_local[], int total_wpt_count) {

    if(depth == total_wpt_count) {
        double tour_cost = distance_so_far + calculate_distance(waypoint_x[under_construction_route[depth-1]],
                                                                waypoint_y[under_construction_route[depth-1]],
                                                                waypoint_x[0],
                                                                waypoint_y[0]);

        if(tour_cost < *best_cost_local) {
            *best_cost_local = tour_cost;
            for(int i=0; i < total_wpt_count; i++) {
                best_route_local[i] = under_construction_route[i];
            }
            best_route_local[total_wpt_count] = under_construction_route[0];
            array_printing(best_route_local, total_wpt_count+1);
            printf(" --- with distance %f units.\n\n", tour_cost);
        }
        return;
    }

    for(int i=0; i < total_wpt_count; i++) {
        if(!visited[i]) {
            double d = calculate_distance(
                waypoint_x[under_construction_route[depth-1]],
                waypoint_y[under_construction_route[depth-1]],
                waypoint_x[i],
                waypoint_y[i]
            );

            double new_cost = distance_so_far + d;

            // bound for remaining cities
            double new_bound = find_bound(under_construction_route, visited, depth+1, new_cost, total_wpt_count);

            if(new_bound < *best_cost_local) {
                under_construction_route[depth] = i;
                visited[i] = 1;
                recursive_branching(depth+1, under_construction_route, visited, new_cost, new_bound, best_cost_local, best_route_local, total_wpt_count);
                visited[i] = 0;
            }
        }
    }
}
