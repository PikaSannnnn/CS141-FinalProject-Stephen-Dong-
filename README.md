# Notes and Guidelines

This Bellman-ford algorithm was implemented such that it is built into a graph class. In order to implement this algorithm, additional factors must be considered:
* An `std::map` data structure, that will store all the edges in the graph, will need to be added as it plays a major role in the algorithm *(Line 19)*. 
* The vertex class or struct will require additional variables `v_d` and `v_p` to be the shortest path distance from the source and the predecessor respectively. 
* There must also be a global value defined as `INF` with the value `2147483647` that will represent infinity.

The names of any variables added can be modified as seen fit.  

The given code includes all code for both the implementation of the Graph class and the Bellman-ford algorithm. The code also includes unit tests for multiple graphs of different attributes, each testing the outputs and ability to find the shortest path tree and each edge given a source.  
**All vital parts of the Bellman-ford algorithm can be found between the # lines (Line 28 - 49 and Line 120 - 143).**