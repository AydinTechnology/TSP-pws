#include <math.h>
#include "waypoints.h"

double calculate_distance(double firstwp_x, double firstwp_y, double secondwp_x, double secondwp_y) {       //pythagoras theorem
    firstwp_x = firstwp_x - secondwp_x;
    firstwp_y = firstwp_y - secondwp_y;
    firstwp_x = firstwp_x * firstwp_x;
    firstwp_y = firstwp_y * firstwp_y;
    return sqrt(firstwp_x + firstwp_y);
}

double find_total_distance_route(int index_array[], int printing_size) {
    double total_distance = 0;
    int indexone = index_array[0], indextwo;
    total_distance += calculate_distance(waypoint_x[0], waypoint_y[0], waypoint_x[indexone], waypoint_y[indexone]);       //from our spawn point to the first in the array

    for(int i = 0; i < printing_size - 1; i++) {
        indexone = index_array[i];
        indextwo = index_array[i + 1];
        total_distance += calculate_distance(waypoint_x[indexone], waypoint_y[indexone], waypoint_x[indextwo], waypoint_y[indextwo]);
    }

    total_distance += calculate_distance(waypoint_x[0], waypoint_y[0], waypoint_x[indextwo], waypoint_y[indextwo]);       //back to our "spawn point"
    return total_distance;
}
