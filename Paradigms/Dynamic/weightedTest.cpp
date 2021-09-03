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

class TaskCombination{
    public: 
        int maxProfit; 
        vector<int> indexes; 

        TaskCombination(){
            maxProfit = 0;
        };
        void push_back(Task t){
            maxProfit += t.weight;
            indexes.push_back(t.index);
        }
        friend ostream& operator<<(ostream& os, const TaskCombination& t){
            os << "Max Profit: " << t.maxProfit << "\t Indexes: ";
            for (int i = 0; i < t.indexes.size(); i++) os << t.indexes[i] << " ";
            return os;
        }
};

bool areCompatible(Task t1, Task t2){
    // If they dont overlap
    return t1.start >= t2.end || t2.start >= t1.end;
}

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

Task selectMaxWeight(Task t1, Task t2){
    if(t1.weight > t2.weight) return t1;
    return t2;
}

// Fin
vector<int> findCompatible(Task allTasks[], int N){
    // Indices will be stored here
    vector<int> results;
    //Sort by end time with mergeSort 
    mergeSort(allTasks, 0, N-1);

    for(int i = 0; i < N; i++){
        cout << i << ": " << allTasks[i].index << endl; 
    }

    pair<int, vector<int>> *OPT = new  pair<int, vector<int>>[N]; 
    OPT[0].first = allTasks[0].weight; 


    vector<int> indexes; 
    for (int i=1; i<N; i++){
        int currWeight = allTasks[i].weight; //weight of task
        int indexsum =  allTasks[i].index; 
        int lastCompatibleTaskIndex = binarySearch(allTasks, i); //lastCompatibleTaskIndex is index 2
        vector<int> currentIndexes = { lastCompatibleTaskIndex };
        
        // TODO: cambiar
        if (lastCompatibleTaskIndex != -1){ // if theres compatible task 
            // Sumar el weight
            currWeight += OPT[lastCompatibleTaskIndex].first; //weight of task + weight of task 2
            //indexsum += OPT[lastCompatibleTaskIndex].second; 
            // Agregar los indices que tiene el task compatible
            for(int j = 0; j<OPT[lastCompatibleTaskIndex].second.size(); j++){
                currentIndexes.push_back(OPT[lastCompatibleTaskIndex].second[j]);
            }
            //currentIndexes = OPT[lastCompatibleTaskIndex].second;
            // currentIndexes.push_back(lastCompatibleTaskIndex);
            for(int j = 0; j<currentIndexes.size(); j++){
                cout<<allTasks[currentIndexes[j]]<<", ";
            }
            cout << allTasks[i];
            cout << " Weight: " << currWeight << endl; 
        
            //cout<<allTasks[i]<<", "<<allTasks[lastCompatibleTaskIndex]<<", "<<currWeight<<endl;

        }
        //================================
        if(currWeight > OPT[i-1].first){
            OPT[i].first = currWeight;
            OPT[i].second.push_back(allTasks[i].index);  
            //OPT[i].second.push_back(currentIndexes[0]); 
            //OPT[i].second.push_back(allTasks[lastCompatibleTaskIndex].index);
        }
        else{
            OPT[i].first = OPT[i-1].first;              
        }
    }
  
    results = OPT[N-1].second;
    cout << "Profit: " <<OPT[N-1].first << endl; 
    delete[] OPT;

    //sort(results.begin(), results.end());
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
        // Print tasks
        // TODO: remove
        cout<<selected<<endl<<"====================="<<endl;
    }

    // Resultados
    vector<int> resultados = findCompatible(allTasks, N);
    for(int i = 0; i < resultados.size(); i++){
        cout << resultados[i] << " ";  
    }  
    //imprimir result printArray(allTasks, N);
    return 0;
}