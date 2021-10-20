/**
 * @author Lourdes Badillo Granillo, Eduardo Villalpando Mello
 * @date 2021-10-07
 * Kruskal algortihm for finding minimum spanning tree
*/

#include <bits/stdc++.h>
#include "graph.hpp"
#include "unionfind.hpp"
using namespace std;

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
        g.insertEdge(src, dest, weight, i);
    }
    // g.print();
    // Create unionfind structure
    UnionFind u(g.nodes.size());
    for(GraphEdge edge : g.getEdges()){
        if(u.find(edge.src) != u.find(edge.dest)){
            u.unionSets(edge.src, edge.dest);
            cout << edge << endl;
        }
    }
    return 0;
}
