//what happens? we run an array with index numbers through a permutation function. after generating each, the distance is calculated, if it's shorter than already, it's replaced with the current one

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "geometry.h"       //contains geometric helper functions: distance between two points and distance covered entire route
#include "waypoints.h"      //contains all waypoint data
#include "permutations.h"   //contains heap's algorithm to permute our route array

int first_run = 1; //bool so that we can get a first optimal route (before the first there's nothing to compare it against yet)
int temporary_route[] = {1, 2, 3, 4, 5, 6};

void array_printing(int array[], int printing_size) {
    for(int i = 0; i < printing_size; i++) {
        printf("%i ", array[i]);
    }
    return;
}

void check_optimal_route(int array[], int printing_size) {
    double distance = find_total_distance_route(array, printing_size);
    if((optimal_distance > distance) | first_run) {
            first_run = 0;
            optimal_distance = distance;

            optimal_route[0] = 1;                       //replace optimal_route[] array with currently generated one
            for(int i = 0; i < printing_size; i++) {
                optimal_route[i+1] = temporary_route[i] + 1;
            }
            array_printing(optimal_route, printing_size + 1);
            printf(" --- with distance %f units.\n\n", distance);
    }
    return;
}

int main() {
    int size = sizeof(temporary_route)/sizeof(temporary_route[0]);
    int total_permutations = 1;
    for(int i = 1; i <= size; i++) {
        total_permutations *= i; 
    }   //basically just size!

    for(int permutation_index = 0; permutation_index < total_permutations; permutation_index++) {
        permute(size, permutation_index, temporary_route);
    }
    return 0;
}
