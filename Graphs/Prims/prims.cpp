/**
 * @author Lourdes Badillo Granillo, Eduardo Villalpando Mello
 * @date 2021-10-15
 * Prims algorithm for minimum spanning trees
*/

#include <bits/stdc++.h>
#include "graph.hpp"
using namespace std;

void getMST(Graph g){
    // Result vector
    vector<GraphEdge> results;
    // Visited nodes map
    map<int, bool> visited;
    for(auto it : g.nodes) visited[it.first] = false;
    // Priority queue of edges
    priority_queue<GraphEdge, vector<GraphEdge>, greater<GraphEdge>> edges;

    // Select first node
    visited[0] = true;
    // Get neighbor nodes
    for(GraphEdge &edge : g.getNeighboringEdges(0)) edges.push(edge);

    while(!edges.empty()){
        // CURRENT = ort and take lightest 
        GraphEdge current = edges.top();
        edges.pop();

        // Ignore if visited[src] && visited[dest]
        if(visited[current.src] && visited[current.dest]) continue;
        // add to results
        results.push_back(current);
        // Get next node (not visited)
        if(!visited[current.src]){
            // Visit next node
            visited[current.src] = true;
            // Add new node edges
            for(GraphEdge &edge : g.getNeighboringEdges(current.src)) edges.push(edge);
        }
        if(!visited[current.dest]){
            // Visit next node
            visited[current.dest] = true;
            // Add new node edges
            for(GraphEdge &edge : g.getNeighboringEdges(current.dest)) edges.push(edge);
        }
        // Repeat
    }
    // Order answers
    sort(results.begin(), results.end());
    // Print
    for(GraphEdge &edge : results) cout << edge << endl;
}


int main(int argc, char **argv){
    // Create graph
    Graph g;
    // Read edges from arguments. [number of elements] [...src] [...dest] [...weight]
    // And add to graph
    int N = atoi(argv[1]);
    for(int i = 0; i < N; i++){
        int src = atoi(argv[i+2]);
        int dest = atoi(argv[i+2+N]);
        int weight = atoi(argv[i+2+N+N]);
        g.insertEdge(src, dest, weight);
    }
    getMST(g);
}