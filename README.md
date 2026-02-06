# TSP_bruteforcing

What is this?
Traveling salesman problem worked out through bruteforcing written in ANSI C

How does it work?
By generating each permutation, we can calculate its distance between points. Each route is compared against the previous optimal distance and if lower, the optimal route gets replaced. Eventually it will spit out the optimal route with the shortest distance to cover each waypoint each number corresponding to its waypoint.
Suppose (10, 50); (40, 10) etc then route (2 1 2) means start at (40, 10) then to (10, 50) and back to (40, 10).
