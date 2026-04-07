#include <stdio.h>
#include <stdlib.h>
#include "geometry_functions.h"
#include "variables.h"

void heldkarp(int n) {
    int entries_count = 1 << n;

    //we'll make a 2^n * n sized cost_table
    double **cost_table = malloc(entries_count * sizeof(double*));
    for(int i = 0; i < entries_count; i++) {
        cost_table[i] = malloc(n * sizeof(double));
        for(int j = 0; j < n; j++) {
            cost_table[i][j] = 1e9;      //we must represent infinity as a distance. if the waypoints are not very far away from each other, 10^9 gets the job done quite well
        }
    }

    //we'll also make a previously_visited_table so that we can easily extract what route we generated since our cost_table is only useful for adding up route cost
    unsigned char **previously_visited_table = malloc(entries_count * sizeof(unsigned char*)); //we won't have to bother with large datatypes since we won't be exceeding 2^8 ie. n>255 anytime soon (ram shortages)
    for(int i = 0; i < entries_count; i++) {
        previously_visited_table[i] = malloc(n * sizeof(unsigned char));
    }


    //we need to make room for the first entry in our cost_table since else it'd keep skipping iterations because everything is 1e9 - in a world full of 1e9s, dare to be different, pave the path for others
    cost_table[1][0] = 0.0;

    for(int unfinished_route = 1; unfinished_route < entries_count; unfinished_route++) {
        for(int last = 0; last < n; last++) {
            if(!(unfinished_route & (1 << last))) continue; //if we are not at the latest finished route, skip this iteration and immediately go to the next one

            double best = cost_table[unfinished_route][last];
            if(best == 1e9) continue;   //same story, we know that this entry remains unused

            for(int next = 0; next < n; next++) {
                if(unfinished_route & (1 << next)) continue;

                int new_unfinished_route = unfinished_route | (1 << next);

                double candidate = best + calculate_distance(waypoint_x[last], waypoint_y[last], waypoint_x[next], waypoint_y[next]);
                if(candidate < cost_table[new_unfinished_route][next]) {
                    cost_table[new_unfinished_route][next] = candidate;
                    previously_visited_table[new_unfinished_route][next] = last;
                }
            }
        }
    }

    //we need to return back to our "spawnpoint" to complete the Hamiltonian cycle
    double answer = 1e9;
    int full = entries_count - 1;

    int best_last;    //we use the last which apparently resulted in the shortest route to backtrack the route through our cost_table
    for(int last = 1; last < n; last++) {
        double route = cost_table[full][last] + calculate_distance(waypoint_x[last], waypoint_y[last], waypoint_x[0], waypoint_y[0]);
        if(route < answer) {
            answer = route;
            best_last = last;
        }
    }

    int route[n+1];     //we also need space for the last waypoint back to the "spawn" so that our route becomes n+1
    int unfinished_route = (1 << n) - 1;    //essentially a zero-indexed entries_count from earlier

    for (int i = n-1; i > 0; i--) {         //we essentially recode the bitmask according to the best last variable and then grab the waypoint index numbers from the previously_visited_table
        route[i] = best_last;
        int prev = previously_visited_table[unfinished_route][best_last];
        unfinished_route = unfinished_route ^ (1 << best_last);
        best_last = prev;
    }

    route[0] = 0;   //we start from...
    route[n] = 0;   //and leave from waypoint[0]

    printf("\nThe optimal route is ");
    array_printing(route, n+1);
    printf("with a distance of %lf units.\n", answer);

    //clean up the mess we made in the heap
    for(int i = 0; i < entries_count; i++) free(cost_table[i]);
    free(cost_table);
    for(int i = 0; i < entries_count; i++) free(previously_visited_table[i]);
    free(previously_visited_table);
    return;
}
