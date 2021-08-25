#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>
using namespace std;

class Task{
    public:   
        int index; 
        int start; //starting time
        int end; //finish time
        Task(){}
        Task(int index, int start, int end){
            this->index = index;
            this->start = start;
            this->end = end;
        }
        void print(){
            cout<<this->start<<"->"<<this->end<<endl;
        }   
        friend ostream& operator<<(ostream& os, const Task& selected){
            os << "(" << selected.index << ") " << selected.start<<"->"<<selected.end;
            return os;
        } 
}; 

//Compare tasks 
bool areCompatible(Task t1, Task t2){
    // If they dont overlap
    return t1.start >= t2.end || t2.start >= t1.end;
}

//Sort by earliest finishing time
template<class T>
void swap(T* a, T* b) { 
    //Swap Tasks
    T selected = *a; 
    *a = *b; 
    *b = selected; 
} 

int partition (Task tasks[], int low, int high) { 
    Task pivot = tasks[high]; 
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++) { 
        if (tasks[j].end < pivot.end) { //Compares end time, sorting by earliest end time 
            i++;
            swap(&tasks[i], &tasks[j]); //Swaps Tasks
        } 
    } 
    swap(&tasks[i + 1], &tasks[high]); 
    return (i + 1); 
} 

void quickSort(Task tasks[], int low, int high) { 
    if (low < high) 
    { 
        int indx = partition(tasks, low, high); 
        quickSort(tasks, low, indx - 1); 
        quickSort(tasks, indx + 1, high); 
    } 
} 

// Print array of Tasks
void printArray(Task arr[], int size) { 
    for (int i = 0; i < size; i++) cout << arr[i] << " "; 
    cout << endl; 
} 

vector<int> findCompatible(Task allTasks[], int N){

    //Sort by earliest end time
    quickSort(allTasks, 0, N-1); 
    //Vector with the indexes of compatible tasks
    vector<int> result; 
    // Current task
    Task selected = allTasks[0];
    // 
    result.push_back(selected.index);
    // Iterate all tasks
    for(int i = 0; i<N; i++){
        if( areCompatible(selected, allTasks[i]) ){
            result.push_back(allTasks[i].index);
            selected = allTasks[i]; 
        }
    }
    // Order results 
    sort(result.begin(), result.end());
    return result; 
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
        Task selected(i, startValues[i], endValues[i]);
        allTasks[i] = selected;
    }
    // Resultados
    vector<int> resultados = findCompatible(allTasks, N);

    for(int i = 0; i < resultados.size(); i++){
        cout << resultados[i] << " ";  
    } 
    //imprimir result printArray(allTasks, N);
    return 0;
}