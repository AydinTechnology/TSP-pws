#include <stdio.h>
#include <math.h>
#include "variables.h"
#include "geometry_functions.h"

void array_printing(int array[], int printing_size) {
    for(int i = 0; i < printing_size; i++) {
        printf("%i ", array[i] + 1); //make them correspond with human-logic instead of 0-indexed index numbers
    }
    return;
}

double find_total_distance_route(int route_array[], int route_size) {
    double total_distance = 0;

    for(int i = 0; i < route_size; i++) {
        int indexone = route_array[i];
        int indextwo = route_array[i + 1];
        total_distance += calculate_distance(waypoint_x[indexone], waypoint_y[indexone], waypoint_x[indextwo], waypoint_y[indextwo]);
    }

    return total_distance;
}

double calculate_distance(double firstwp_x, double firstwp_y, double secondwp_x, double secondwp_y) {       //pythagoras theorem
    firstwp_x = firstwp_x - secondwp_x;
    firstwp_y = firstwp_y - secondwp_y;
    firstwp_x = firstwp_x * firstwp_x;
    firstwp_y = firstwp_y * firstwp_y;
    return sqrt(firstwp_x + firstwp_y);
}

double find_bound(int route[], int visited[], int depth, double distance_so_far, int total_wpt) {
    double bound = distance_so_far;

    //handle all unvisited cities
    for(int i = 0; i < total_wpt; i++) {
        if(!visited[i]) {
            bound += first_smallest_edge[i];
            bound += second_smallest_edge[i];
        }
    }

    //fix the last visited waypoint
    bound += first_smallest_edge[route[depth-1]];
    //each edge gets counted twice so divide by two to fix
    return bound / 2.0;
}
