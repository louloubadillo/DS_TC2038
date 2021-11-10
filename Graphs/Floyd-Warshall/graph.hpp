#ifndef graph_h
#define graph_h
#include <bits/stdc++.h>
#include <climits>
#define i_max INT_MAX
using namespace std;

/**
 * Represents a node in a graph. May be extended in the future.
 **/
class GraphNode {
public:
    int value;
    GraphNode() : value(0) {}
    GraphNode(int value) : value(value) {}
};

/**
 * Represents a weighted edge connecting two nodes.
**/
class GraphEdge {
public:
    static int counter;
    // Index of insertion
    int index;
    // Index of src node 
    int src;
    // Index of dest node
    int dest;
    // Weight of edge. Default is i_max
    float weight;
 
    GraphEdge() : src(0), dest(0), weight(i_max) {
        this->index = GraphEdge::counter++;
    }
    GraphEdge(int src, int dest) : src(src), dest(dest), weight(i_max) {
        this->index = GraphEdge::counter++;
    }
    GraphEdge(int src, int dest, float weight) : src(src), dest(dest), weight(weight) {
        this->index = GraphEdge::counter++;
    } 

    // otuputs src, dest, weight
    friend ostream &operator<<(ostream &os, const GraphEdge &g){
        os << g.src << " " << g.dest << " " << g.weight;
        return os;
    }
    // Compare by weight and then by src indexes
    friend bool operator<(const GraphEdge &a, const GraphEdge &b){
        if(a.weight != b.weight) return a.weight < b.weight;
        return a.index < b.index;
    }
    // Compare by weight and then by src indexes
    friend bool operator>(const GraphEdge &a, const GraphEdge &b){
        if(a.weight != b.weight) return a.weight > b.weight;
        return a.index > b.index;
    }
};
int GraphEdge::counter = 0;

class Graph{
public:
    // Map containing all the nodes in the graph. Map allows for non-subsequent items
    map<int, GraphNode> nodes;
    // Vector containing all the edges in the graph
    vector<GraphEdge> edges;
    Graph(){}
    Graph(vector<GraphEdge> &v){
        // Individually check for each vertex
        for(GraphEdge &edge : v) this->insertEdge(edge);
    }
    // Inserts a GraphEdge and its nodes if not already in the graph
    void insertEdge(GraphEdge edge){
            // Check if src exists
            if(nodes.find(edge.src) == nodes.end()) nodes[edge.src] = GraphNode(edge.src);
            // Check if dest exists
            if(nodes.find(edge.dest) == nodes.end()) nodes[edge.dest] = GraphNode(edge.dest);
            // Add edge to graph
            this->edges.push_back(edge);
    }
    // Constructs a GraphEdge and inserts it in the graph
    void insertEdge(int src, int dest, float weight){
        this->insertEdge(GraphEdge(src, dest, weight));
    }
    // Prints every edge in the graph
    void printEdges(){
        for(GraphEdge edge : this->edges){
            cout << edge << endl;
        }
    }
    // Checks if a value exists in the graph nodes
    bool contains(int value){
        return this->nodes.find(value) != this->nodes.end();
    }
    // Checks if a node exists in the graph
    bool contains(GraphNode value){
        return this->contains(value.value);
    }
    // Sorts and returns edges
    vector<GraphEdge> getEdges(){
        sort(this->edges.begin(), this->edges.end());
        return this->edges;
    }
    
    vector<GraphEdge> getNeighboringEdges(int n){
        vector<GraphEdge> result;
        for(GraphEdge &edge : this->edges){
            if(edge.dest == n || edge.src == n) result.push_back(edge);
        }
        sort(result.begin(), result.end());
        return result;
    }

    // GraphEdge getEdge(int dest, int)

};


#endif