/**
 * @author Lourdes Badillo Granillo, Eduardo Villalpando Mello
 * Residual Graph class 
*/
#ifndef residual_h
#define residual_h
#include <bits/stdc++.h>
#include <climits>
#include "graph.hpp"

using namespace std;

class ResidualEdge : public GraphEdge{
    public:
        bool isForward;
        ResidualEdge *counterpart;
        ResidualEdge() : GraphEdge(){
            isForward = false;
            counterpart = nullptr;
        }
        ResidualEdge(int src, int dest) : GraphEdge(src, dest){
            this->isForward = false;
            this->counterpart = nullptr;
        }
        ResidualEdge(int src,int dest, int weight) : GraphEdge(src, dest, weight){
            this->isForward = false;
            this->counterpart = nullptr;
        }
        ResidualEdge(int src, int dest, int weight, bool isForward) : GraphEdge(src, dest, weight){
            this->isForward = isForward;
            this->counterpart = nullptr;
        }
        void set_couterpart(ResidualEdge *n){
            this->counterpart = n;
        }
};            

class ResidualGraph{
    private: 
        vector<ResidualEdge*> *edges;
    
    public: 
        int n; 
        ResidualGraph(Graph &g){
            this->n = g.nodes.size();
            this->edges = new vector<ResidualEdge *>[this->n];
            // Obtener combinaciones u, v
            for(int i = 0; i < this-> n; i++){
                for(GraphEdge &it: g.getNeighboringEdges(i)){
                    // Crear residual edges
                    ResidualEdge *fwd = new ResidualEdge(i, it.dest, it.weight, true);
                    ResidualEdge *bwd = new ResidualEdge(it.dest, i, 0, false);
                    // Asignar contrapartes
                    fwd->set_couterpart(bwd);
                    bwd->set_couterpart(fwd);
                    // Agregar a lista de adjacencia
                    this->edges[i].push_back(fwd);
                    this->edges[it.dest].push_back(bwd);
                    
                }
            }
        }
        vector<ResidualEdge *> getNeighbors(int v){
            return this->edges[v];
        }
        /* void printFlow(){
            for(int i = 0; i < this->n; i++){
                for(auto it: this->edges[i]){
                    if(!it->isForward) cout << it << endl;
                }
            }
        } */
};
    
#endif
