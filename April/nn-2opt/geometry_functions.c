#include <stdio.h>
#include <math.h>
#include "variables.h"

void array_printing(int array[], int printing_size) {
    for(int i = 0; i < printing_size; i++) {
        printf("%i ", array[i] + 1); //make them correspond with human-logic instead of 0-indexed index numbers
    }
    return;
}

double calculate_distance(double firstwp_x, double firstwp_y, double secondwp_x, double secondwp_y) {       //pythagoras theorem
    firstwp_x = firstwp_x - secondwp_x;
    firstwp_y = firstwp_y - secondwp_y;
    firstwp_x = firstwp_x * firstwp_x;
    firstwp_y = firstwp_y * firstwp_y;
    return sqrt(firstwp_x + firstwp_y);
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

void swap_waypoints(int *route, int start, int end) {
    while(start < end) {
        int temp = route[start];
        route[start] = route[end];
        route[end] = temp;
        start++;
        end--;
    }
}
