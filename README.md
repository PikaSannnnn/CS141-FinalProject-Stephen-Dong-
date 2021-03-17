# Notes and Guidelines

This Bellman-ford algorithm was implemented such that it is built into a graph class. In order to implement this algorithm, additional factors must be considered:
* An `std::map` data structure, that will store all the edges in the graph, will need to be added as it plays a major role in the algorithm *(Line 19)*. 
* The vertex class or struct will require additional variables `v_d` and `v_p` to be the shortest path distance from the source and the predecessor respectively. 
* There must also be a global value defined as `INF` with the value `2147483647` that will represent infinity.

The names of any variables added can be modified as seen fit.  

The given code includes all code for both the implementation of the Graph class and the Bellman-ford algorithm. The code also includes unit tests for multiple graphs of different attributes, each testing the outputs and ability to find the shortest path tree and each edge given a source.  
**All vital parts of the Bellman-ford algorithm can be found between the # lines (Line 28 - 49 and Line 120 - 143).** Below is the snippets for each of these parts.
</br>
</br>
</br>
</br>
```c++
void InitSingleSource(Node* source) {   // Inits all vertices given source
    for (auto v : vertices) {
        v->v_d = INF;
        v->v_p = nullptr;
    }
    source->v_d = 0;
}
bool Relax(std::map<std::pair<Node*, Node*>, int>::iterator it) { // it = (u, v, w)
    Node* u = it->first.first;
    Node* v = it->first.second;
    int w = it->second;
    if ((u->v_d + w) < v->v_d) { // u.d + w(u,v) < v.d
        if (u->v_d == INF) { return false; }    // Not in original algorithm, specific to C++ (No real INF in C++)
        v->v_d = u->v_d + w;
        v->v_p = u;
        return true;
    }

    return false;
}
bool Graph::BellmanFord(Node* source) { 
    InitSingleSource(source);   // Init Single Source
    int verticesSZ = vertices.size();

    for (int i = 0; i < verticesSZ - 1; i++) {  // V - 1            // O(VE)
        std::map<std::pair<Node*, Node*>, int>::iterator it = AllEdges.begin(); // iterator for all edges given u
        for (; it != AllEdges.end(); it++) {  // E
            Relax(it);
        }
    }
    
    std::map<std::pair<Node*, Node*>, int>::iterator it = AllEdges.begin(); // iterator for all edges given u
    for (; it != AllEdges.end(); it++) {  // E
        if (Relax(it)) {    // it => (u, v, w)
            return false;
        }
    }

    return true;
}
```