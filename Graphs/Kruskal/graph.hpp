#ifndef graph_h
#define graph_h
#include <bits/stdc++.h>
using namespace std;

class GraphNode {
public:
    int value;
    GraphNode() : value(0) {}
    GraphNode(int value) : value(value) {}
};

class GraphEdge {
public:
    int src;
    int dest;
    float weight;
    int index; 
    GraphEdge() : src(0), dest(0), weight(0), index(0) {}
    GraphEdge(int src, int dest, int index) : src(src), dest(dest), index(index), weight(0) {}
    GraphEdge(int src, int dest, float weight, int index) : src(src), dest(dest), weight(weight), index(index) {} 

    friend ostream &operator<<(ostream &os, const GraphEdge &g){
        os << g.src << " " << g.dest << " " << g.weight;
        return os;
    }
    friend bool operator<(const GraphEdge &a, const GraphEdge &b){
        // Use to order by weight and then by src
        if(a.weight != b.weight) return a.weight < b.weight;
        return a.index < b.index;
    }
};

class Graph{
public:
    map<int, GraphNode> nodes;
    vector<GraphEdge> edges;
    Graph(){}
    Graph(vector<GraphEdge> &v){
        // Individually check for each vertex
        for(GraphEdge &edge : v) this->insertEdge(edge);
    }
    void insertEdge(GraphEdge edge){
            // Check if src exists
            if(nodes.find(edge.src) == nodes.end()) nodes[edge.src] = GraphNode(edge.src);
            // Check if dest exists
            if(nodes.find(edge.dest) == nodes.end()) nodes[edge.dest] = GraphNode(edge.dest);
            // Add edge to graph
            this->edges.push_back(edge);
    }
    void insertEdge(int src, int dest, float weight, int index){
        this->insertEdge(GraphEdge(src, dest, weight, index));
    }
    void print(){
        for(GraphEdge edge : this->edges){
            cout << edge << endl;
        }
    }
    bool contains(int value){
        return this->nodes.find(value) != this->nodes.end();
    }
    bool contains(GraphNode value){
        return this->contains(value.value);
    }
    vector<GraphEdge> getEdges(){
        sort(this->edges.begin(), this->edges.end());
        return this->edges;
    }
};


#endif