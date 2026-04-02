#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsing_waypoints.h"
#include "variables.h"
#include "geometry_functions.h"
#include "heldkarp.h"

int main(int argc, char *argv[]) {
//===================== initialising (parsing waypoints etc.)
    if(argc != 2) {                                                 //if the user executes the program but gives wrong/no arguments, make a problem of it
        printf("Please provide a text file with waypoints.\n");
        printf("Example input: %s waypoints.txt\n", argv[0]);
        return 1;
    }

    int waypoints_parsed_count = parse_waypoints(argv[1]); //read waypoints and show to the user what they look like in memory (makes debugging the input file for the user a lot lot easier)
    int size_array = waypoints_parsed_count - 1;
    printf("Amount of waypoints parsed: %i\n\n", waypoints_parsed_count);
    for(int i = 0; i < waypoints_parsed_count; i++) {
        printf("%lf, %lf\n", waypoint_x[i], waypoint_y[i]);
    }

//===================== actual calculating (creating arrays, permuting, running algorithm etc.)

    heldkarp(waypoints_parsed_count);

    return 0;
}
