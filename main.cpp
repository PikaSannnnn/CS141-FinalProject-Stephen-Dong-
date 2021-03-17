#include <iostream>
#include <vector>
#include <map>

#define INF 2147483647  // integer limit

class Node {
public:
    char label;
    int v_d;
    Node* v_p;
    std::map<Node*, int> edges;
    Node(char label) : label(label), v_d(INF), v_p(0), edges() {}
};

class Graph {
private:
    std::vector<Node*> vertices;
    std::map<std::pair<Node*, Node*>, int> AllEdges;
    bool VertexExists(char label) { // Checks if vertex already exists
        for (auto i : vertices) {
            if (label == i->label) {
                return true;
            }
        }
        return false;
    }
    //############################
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
    //############################
    void PrintPath(Node* v) {   // Recursive Traversal
        if (v == nullptr) {
            return;
        }
        PrintPath(v->v_p);
        std::cout << v->label;
    }
public:
    Graph() : vertices(0) {}
    void AddEdge(char, char, int);
    bool BellmanFord(Node*);
    void PrintEdges();
    void PrintShortestPaths(char);
};

void Graph::AddEdge(char from, char to, int weight) {
    Node* fromNode = nullptr;
    Node* toNode = nullptr;
    for (auto v : vertices) {
        if (v->label == from) {
            fromNode = v;
        }
        if (v->label == to) {
            toNode = v;
        }
    }
    if (!fromNode && !toNode) {  // Empty Graph or Neither Vertices exist
        fromNode = new Node(from);
        toNode = new Node(to);
        fromNode->edges[toNode] = weight;
        vertices.push_back(fromNode);
        vertices.push_back(toNode);

        std::pair<Node*, Node*> newEdge = std::make_pair(fromNode, toNode);
        AllEdges[newEdge] = weight; // Add to AllEdges
    }
    else if (!fromNode && toNode) { // From Vertex does not exist, Adding it
        fromNode = new Node(from);
        fromNode->edges[toNode] = weight;
        vertices.push_back(fromNode);

        std::pair<Node*, Node*> newEdge = std::make_pair(fromNode, toNode);
        AllEdges[newEdge] = weight; // Add to AllEdges
    }
    else if (fromNode && !toNode) { // To Vertex does not exist, Adding it
        toNode = new Node(to);
        fromNode->edges[toNode] = weight;
        vertices.push_back(toNode);

        std::pair<Node*, Node*> newEdge = std::make_pair(fromNode, toNode);
        AllEdges[newEdge] = weight; // Add to AllEdges
    }
    else {  // Both Vertices already exist
        if (fromNode == toNode) { return; } // Goes to itself

        bool isAdjacent = false;
        for (auto i : fromNode->edges) {
            if (i.first == toNode) {    // toNode already adjacent to fromNode => No need to add
                isAdjacent = true;
            }
        }
        if (!isAdjacent) {  // toNode not adjacent to fromNode => OK to add
            fromNode->edges[toNode] = weight;

            std::pair<Node*, Node*> newEdge = std::make_pair(fromNode, toNode);
            AllEdges[newEdge] = weight; // Add to AllEdges
        }
    }
}

//############################

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

//############################

void Graph::PrintEdges () {   // FOR TESTING: Prints ALL Edges
    for (auto v : vertices) {
        std::cout << v->label << ": ";
        std::map<Node*, int>::iterator it = v->edges.begin();
        for (; it != v->edges.end(); it++) {
            std::cout << it->first->label << it->second;
        }
        std::cout << std::endl;
    }

    std::cout << "All Edges: ";
    for (auto e : AllEdges) {
        std::cout << e.first.first->label << e.first.second->label << e.second;
    }
    std::cout << std::endl;
}
void Graph::PrintShortestPaths(char sourceLabel) {  
    Node* source = nullptr;
    for (auto i : vertices) {
        if (i->label == sourceLabel) {
            source = i;
            break;
        }
    }
    
    if (BellmanFord(source)) {
        std::cout << "Source: " << sourceLabel << std::endl;
        for (auto v : vertices) {
            if (v != source) {
                std::cout << sourceLabel << " to " << v->label << ": ";
                PrintPath(v);
                std::cout << std::endl << "\tWeight: ";
                if (v->v_d != INF) { std::cout << v->v_d; }
                else { std::cout << "INF"; }
                std::cout << std::endl;
            }
        }
    }
    else {
        std::cout << "Negative Cycle Present!" << std::endl;
    }
}

int main() {
    std::cout << "###############" << std::endl;
    std::cout << "Graph A" << std::endl;
    std::cout << "###############" << std::endl;
    Graph GraphA;   // Graph A - No Cycles
    GraphA.AddEdge('A', 'B', 10);
    GraphA.AddEdge('A', 'C', 7);
    GraphA.AddEdge('B', 'C', 3);
    GraphA.AddEdge('C', 'D', 12);
    GraphA.AddEdge('C', 'F', 10);
    GraphA.AddEdge('A', 'E', 13);
    GraphA.AddEdge('D', 'E', 5);
    GraphA.AddEdge('D', 'F', 30);
    GraphA.PrintShortestPaths('A'); std::cout << std::endl;
    GraphA.PrintShortestPaths('B'); std::cout << "\n\n\n";

    std::cout << "###############" << std::endl;
    std::cout << "Graph B" << std::endl;
    std::cout << "###############" << std::endl;
    Graph GraphB;   // Graph B - Negative Weights No cycles
    GraphB.AddEdge('A', 'B', 10);
    GraphB.AddEdge('A', 'C', 7);
    GraphB.AddEdge('B', 'C', -5);
    GraphB.AddEdge('C', 'D', 12);
    GraphB.AddEdge('C', 'F', 10);
    GraphB.AddEdge('A', 'E', 13);
    GraphB.AddEdge('D', 'E', 5);
    GraphB.AddEdge('D', 'F', 30);
    GraphB.PrintShortestPaths('A'); std::cout << std::endl;
    GraphB.PrintShortestPaths('B'); std::cout << "\n\n\n";

    std::cout << "###############" << std::endl;
    std::cout << "Graph C" << std::endl;
    std::cout << "###############" << std::endl;
    Graph GraphC;   // Graph C - Positive Cycle
    GraphC.AddEdge('A', 'B', 10);
    GraphC.AddEdge('A', 'C', 7);
    GraphC.AddEdge('B', 'C', 3);
    GraphC.AddEdge('C', 'A', 7);
    GraphC.AddEdge('C', 'D', 12);
    GraphC.AddEdge('C', 'F', 10);
    GraphC.AddEdge('A', 'E', 13);
    GraphC.AddEdge('D', 'E', 5);
    GraphC.AddEdge('D', 'F', 30);
    GraphC.PrintShortestPaths('A'); std::cout << std::endl;
    GraphC.PrintShortestPaths('B'); std::cout << "\n\n\n";

    std::cout << "###############" << std::endl;
    std::cout << "Graph D" << std::endl;
    std::cout << "###############" << std::endl;
    Graph GraphD;   // Graph C - Negative Cycle
    GraphD.AddEdge('A', 'B', 10);
    GraphD.AddEdge('A', 'C', 7);
    GraphD.AddEdge('B', 'C', 3);
    GraphD.AddEdge('C', 'A', -10);
    GraphD.AddEdge('C', 'D', 12);
    GraphD.AddEdge('C', 'F', 10);
    GraphD.AddEdge('A', 'E', 13);
    GraphD.AddEdge('D', 'E', 5);
    GraphD.AddEdge('D', 'F', 30);
    GraphD.PrintShortestPaths('A'); std::cout << std::endl;
    GraphD.PrintShortestPaths('B'); std::cout << std::endl;
}





/*

    After finding the shortest path to each vertex, what does an additional relaxation imply?
    
    a) Nothing, we’re just making an additional correction
    b) Negative Cycle
    c) Negative Weights

*/