#ifndef unionfind_h
#define unionfind_h

#include <bits/stdc++.h>
using namespace std;

class UnionFind{
private:
    vector<int> parent;
public:
    UnionFind(){}
    UnionFind(int n){
        this->parent = vector<int>(n, -1);
    }
    int find(int x){
        if(parent[x] == -1) return x;
        parent[x] = find(parent[x]); 
        return parent[x];
    }
    void unionSets(int x, int y){
        int setX = this->find(x);
        int setY = this->find(y);
        if(setX == setY) return;
        parent[setX] = setY;
    }
    int size(){
        int count = 0;
        for(int i = 0; i < this->parent.size(); i++){
            if(i == parent[i]) count++;
        }
        return count;
    }
};

#endif