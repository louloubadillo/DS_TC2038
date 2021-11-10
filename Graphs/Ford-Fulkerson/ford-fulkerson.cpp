/**
 * @author Lourdes Badillo Granillo, Eduardo Villalpando Mello
 * @date 2021-10-19
 * Ford-Fulkerson for Maximum Flow in Networks
*/

#include <bits/stdc++.h>
#include "graph.hpp"
#include "ResidualGraph.hpp"
using namespace std;

vector<ResidualEdge*> findPath(ResidualGraph &g, int source, int sink) {
    vector<ResidualEdge*> path;
    queue<int> q;
    bool visited[g.n];
    ResidualEdge *parent[g.n];
    for (int i = 0; i < g.n; i++) {
        visited[i] = false;
    }
    visited[source] = true;
    q.push(source);
    while((!q.empty()) && (visited[sink] == false)) {
        for(auto outEdge : g.getNeighbors(q.front())){
            if(!visited[outEdge->dest] && outEdge->weight > 0){
                q.push(outEdge->dest);
                parent[outEdge->dest] = outEdge;
                visited[outEdge->dest] = true; 
            }
        }
        q.pop();   
    }
    if(visited[sink] == false){
        return path;
    }
    int current = sink; 
    while(!current == source){
        path.push_back(parent[current]);
        current = parent[current]->src;
    }
    
    return path; 
}
    

int maxFlow(Graph &g, int source, int sink){
    int maxFlowResult = 0;
    // Create a residual graph
    ResidualGraph residual(g);
    // Get path
    vector<ResidualEdge*> currentPath = findPath(residual, source, sink);
    // Repeat until no more augmented paths are found
    while(!currentPath.empty()){
        // ?? what is b
        int b = INT_MAX;
        // Update b for each edge
        for(auto edge: currentPath) b = min(b, edge->weight);
        // Increase max flow result
        maxFlowResult += b;
        // Substract to correct errors from previous iterations
        for(auto edge: currentPath){
            // Decrease weight
            edge->weight -= b;
            // Increase in counterpart
            edge->counterpart->weight += b;
        }
        // Update path
        currentPath = findPath(residual, source, sink);
    }
    // TODO: remove
    //residual.printFlow();
    return maxFlowResult;
}

int main(int argc, char **argv){
    // Create graph
    Graph g;
    // Read edges from arguments. [number of elements] [...src] [...dest] [...weight] [path src] [path sink]
    // And add to graph
    int N = atoi(argv[1]);
    for(int i = 0; i < N; i++){
        int src = atoi(argv[i+2]);
        int dest = atoi(argv[i+2+N]);
        int weight = atoi(argv[i+2+N+N]);
        g.insertEdge(src, dest, weight);
    }
    int origin = atoi(argv[N+N+N+2]); 
    int sink = atoi(argv[N+N+N+3]); 
    cout << maxFlow(g, origin, sink) << endl;

    return 0; 
}