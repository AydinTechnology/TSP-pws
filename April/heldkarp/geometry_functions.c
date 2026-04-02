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
