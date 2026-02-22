#include <stdio.h>
#include <math.h>
#include "variables.h"

void array_printing(int array[], int printing_size) {
    for(int i = 0; i < printing_size; i++) {
        printf("%i ", array[i]);
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

double find_total_distance_route(int index_array[], int size_array) {
    double total_distance = 0;
    int indexone = index_array[0], indextwo;
    total_distance += calculate_distance(waypoint_x[0], waypoint_y[0], waypoint_x[indexone], waypoint_y[indexone]);       //from our "spawn point" to the first in the array

    for(int i = 0; i < size_array - 1; i++) {
        indexone = index_array[i];
        indextwo = index_array[i + 1];
        total_distance += calculate_distance(waypoint_x[indexone], waypoint_y[indexone], waypoint_x[indextwo], waypoint_y[indextwo]);
    }

    total_distance += calculate_distance(waypoint_x[0], waypoint_y[0], waypoint_x[indextwo], waypoint_y[indextwo]);       //back to our "spawn point"
    return total_distance;
}

void check_optimal_route(int size_array) {
    double distance = find_total_distance_route(temporary_route, size_array);
    if((optimal_distance > distance) | first_run) {
            first_run = 0;
            optimal_distance = distance;

            optimal_route[0] = 1;                       //replace optimal_route[] array with currently generated one
            for(int i = 0; i < size_array; i++) {
                optimal_route[i+1] = temporary_route[i] + 1;
            }
            array_printing(optimal_route, size_array + 1);
            printf(" --- with distance %f units.\n\n", distance);
    }
    return;
}
