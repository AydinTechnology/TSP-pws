#include <stdio.h>
#include <stdlib.h>
#include "variables.h"

int parse_waypoints(const char* passed_filename) {
    FILE *f = fopen(passed_filename, "r");
    if(!f) return -1;   //make it known if there was any issue with creating the file handler

    waypoint_x = malloc(sizeof(double));    //we'll dynamically grow our waypoint arrays so that
    waypoint_y = malloc(sizeof(double));    //even ridiculous amounts of waypoints could theoratically be processed (probably will take longer than the universe exists, good luck!)

    int waypoints_loaded = 0;
    while(1) {
        if(fscanf(f, "(%lf, %lf)", &waypoint_x[waypoints_loaded], &waypoint_y[waypoints_loaded]) == EOF) break;

        waypoints_loaded++;
        waypoint_x = realloc(waypoint_x, (waypoints_loaded+1)*sizeof(double));
        waypoint_y = realloc(waypoint_y, (waypoints_loaded+1)*sizeof(double));
        fseek(f, 1, SEEK_CUR);   //there is a newline symbol after each "enter" in the file which we skip by incrementing our file pointer by one relative or "SEEK_CUR"
    }

    fclose(f);
    return waypoints_loaded;
}
