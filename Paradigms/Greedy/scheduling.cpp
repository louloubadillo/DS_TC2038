#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>
using namespace std;

class Task{
    public:   
        int start; //starting time
        int end; //finish time
        Task(){}
        Task(int start, int end){
            this->start = start;
            this->end = end;
        }
        void print(){
            cout<<this->start<<"->"<<this->end<<endl;
        }
        
}; 

 sortTasks(Task allTasks[]){
    // Sort by earliest finishing time
    
}


/**
 *
 * @param argc Size of argv
 * @param argv N, N start values, N finish values
 * @return Indexes of tasks in the max set of compatible tasks 
*/
int main(int argc, char** argv){ 

    //First argument is the amount of tasks
    int N = atoi(argv[1]);
    
    // 2 - N+2 Start values
    int startValues[N]; 
    for(int i = 0; i<N; i++){
        startValues[i] = atoi(argv[i+2]);
        
    }
    // N - 2*N End values
    int endValues[N]; 
    for(int i = 0; i<N; i++){
        endValues[i] = atoi(argv[i+2+N]);
    }
    // Create tasks
    Task allTasks[N];
    for(int i = 0; i<N; i++){
        if(startValues[i] < endValues[i]){
            Task t(startValues[i], endValues[i]);
            //Testing
            allTasks[i] = t;
            t.print();
        }
        else{
            cout << "The start time can't be larget than the finish time" << endl; 
        }   
    } 

    return 0;
}