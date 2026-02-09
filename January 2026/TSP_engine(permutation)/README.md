Changelog

We merged our engine from December 2025 with the Lehmer code experiment so that we can now permute starting at any given index number instead of having to start all over from the beginning.
This allows for parallel processing since we can have a bunch of instances run ie. you run 0-n, you run n-m etc.
