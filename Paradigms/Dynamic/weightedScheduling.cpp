//Top down with Memoization Weighted Interval Scheduling

#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>
#include <math.h>
using namespace std;

// Task Object
class Task{
    public:   
        int index; 
        int start; //starting time
        int end; //finish time
        int weight; //weight of task
        Task(){}
        Task(int index, int start, int end, int weight){
            this->index = index;
            this->start = start;
            this->end = end;
            this->weight = weight;
        }
        void print(){
            cout<<this->start<<"->"<<this->end<<endl;
        }   
        friend ostream& operator<<(ostream& os, const Task& selected){
            os << "(" << selected.index << ") " << selected.start<<"->"<<selected.end<<", w: "<<selected.weight;
            return os;
        }      
}; 

struct TaskW {
    vector<Task> task; //keep track of tasks used to generate value
    int value; //total profit value 
};

//No overlap
bool areCompatible(Task t1, Task t2){
    // If they dont overlap
    return t1.start >= t2.end || t2.start >= t1.end;
}

//SORTING
// Merge
void merge(Task tasks[], int const left, int const mid, int const right)
{
    auto const subArrayLeft = mid - left + 1;
    auto const subArrayRight = right - mid;
 
    auto *leftArray = new Task[subArrayLeft],
         *rightArray = new Task[subArrayRight];
 
    for (auto i = 0; i < subArrayLeft; i++)
        leftArray[i] = tasks[left + i];
    for (auto j = 0; j < subArrayRight; j++)
        rightArray[j] = tasks[mid + 1 + j];
 
    auto indexOfSubArrayLeft = 0, 
        indexOfSubArrayRight = 0;
    int indexOfMergedArray = left; 

    while (indexOfSubArrayLeft < subArrayLeft && indexOfSubArrayRight < subArrayRight) {
        if (leftArray[indexOfSubArrayLeft].end <= rightArray[indexOfSubArrayRight].end) {
            tasks[indexOfMergedArray] = leftArray[indexOfSubArrayLeft];
            indexOfSubArrayLeft++;
        }
        else {
            tasks[indexOfMergedArray] = rightArray[indexOfSubArrayRight];
            indexOfSubArrayRight++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayLeft < subArrayLeft) {
        tasks[indexOfMergedArray] = leftArray[indexOfSubArrayLeft];
        indexOfSubArrayLeft++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayRight < subArrayRight) {
        tasks[indexOfMergedArray] = rightArray[indexOfSubArrayRight];
        indexOfSubArrayRight++;
        indexOfMergedArray++;
    }
}

// Merge sort
void mergeSort(Task tasks[], int const low, int const high){
    if (low >= high)
        return; // Returns recursivly
 
    auto mid = low + (high - low) / 2;
    mergeSort(tasks, low, mid);
    mergeSort(tasks, mid + 1, high);
    merge(tasks, low, mid, high);
}

// Find task that is compatible
int binarySearch(Task tasks[], int currentIndex){
    int low = 0; 
    int high = currentIndex - 1;
  
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (tasks[mid].end <= tasks[currentIndex].start)
        {
            if (tasks[mid + 1].end <= tasks[currentIndex].start)
                low = mid + 1;
            else
                return mid;
        }
        else
            high = mid - 1;
    }
    return -1;
}

// Find tasks that give max profit value
vector<int> findCompatible(Task allTasks[], int N){
    
    vector<int> results;
    
    //Sort by end time with mergeSort 
    mergeSort(allTasks, 0, N-1);

    //Keep track of tasks
    TaskW OPT[N]; 
    //initialize
    OPT[0].value = allTasks[0].weight; 
    OPT[0].task.push_back(allTasks[0]); 

    for (int i = 1; i < N; i++) {
        int profit = allTasks[i].weight;
        int l = binarySearch(allTasks, i);
        if (l != - 1)
            profit += OPT[l].value;
        if (profit > OPT[i - 1].value){
            OPT[i].value = profit;
            OPT[i].task = OPT[l].task;
            OPT[i].task.push_back(allTasks[i]);
        }
        else
            OPT[i] = OPT[i - 1];
    }

    for (int i=0; i<OPT[N-1].task.size(); i++) {
        Task t = OPT[N-1].task[i];
        results.push_back(t.index); //original indexes
    }

    //sort the original indexes 
    sort(results.begin(), results.end());
    return results;
}




/**
 *
 * @param argc Size of argv
 * @param argv N, N start values, N finish values. N weight values
 * @return Indexes of tasks in the max set of compatible tasks with max weight value
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
    // Weights
    int weightValues[N]; 
    for(int i = 0; i<N; i++){
        weightValues[i] = atoi(argv[i+2+N+N]);
    }

    // Create tasks
    Task allTasks[N];
    for(int i = 0; i<N; i++){
        Task selected(i, startValues[i], endValues[i], weightValues[i]);
        allTasks[i] = selected;
    }

    // Resultados
    vector<int> resultados = findCompatible(allTasks, N);
    for(int i = 0; i < resultados.size(); i++){
        cout << resultados[i] << " ";  
    }  

    return 0;
}