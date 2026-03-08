Changelog

Fixed a critical bug in the part where each node sents their "optimal route" to node 0 to check which one is truly the best.
Fixed a piece of logic in the distance checking part so that complexity becomes O((n-1)!/2) instead of just O((n-1)!)
