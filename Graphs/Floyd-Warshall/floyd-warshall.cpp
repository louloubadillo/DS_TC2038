/**
 * @author Lourdes Badillo Granillo, Eduardo Villalpando Mello
 * @date 2021-10-19
 * Floyd-Warshall for finding the shortest path
*/

#include <bits/stdc++.h>
#include "graph.hpp"
using namespace std;


void floyd_warshall(Graph g, int u, int v){
    int V = g.nodes.size();
    // Matrix to store distances
    vector<vector<float>> dist(V, vector<float>(V, MAXFLOAT));
    // Matrix to store next node
    vector<vector<int>> next(V, vector<int>(V, -1));
    // Matrix to easily retrieve edges
    vector<vector<GraphEdge>> edges(V, vector<GraphEdge>(V));

    // For each edge do
    for(GraphEdge &edge : g.edges){
        // Update dist, next and edges
        dist[edge.src][edge.dest] = edge.weight;
        next[edge.src][edge.dest] = edge.dest;
        edges[edge.src][edge.dest] = edge;
    }
    // For each vertex do
    for(pair<int, GraphNode> node : g.nodes){
        // Update dist, next and edges
        dist[node.first][node.first] = 0;
        next[node.first][node.first] = node.first;
        edges[node.first][node.first] = GraphEdge(node.first, node.first, 0);
    }
    //
    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                if( dist[i][j] > dist[i][k] + dist[k][j] ){
                    // Update dist and next edge
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
    // Return if path does not exist
    if(next[u][v] == -1) return;
    do{
        // Print edge at (u, next(u,v))
        cout << edges[u][next[u][v]] << endl;
        // Update u to next node
        u = next[u][v];
    } while(u != v);
}


int main(int argc, char **argv){
    // Create graph
    Graph g;
    // Read edges from arguments. [number of elements] [...src] [...dest] [...weight] [path src] [path dest]
    // And add to graph
    int N = atoi(argv[1]);
    for(int i = 0; i < N; i++){
        int src = atoi(argv[i+2]);
        int dest = atoi(argv[i+2+N]);
        int weight = atoi(argv[i+2+N+N]);
        g.insertEdge(src, dest, weight);
    }
    int origin = atoi(argv[N+N+N+2]); 
    int dest = atoi(argv[N+N+N+3]); 

    floyd_warshall(g, origin, dest);
    return 0; 
}