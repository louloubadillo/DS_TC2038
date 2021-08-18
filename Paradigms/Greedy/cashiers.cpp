//Find min number of denominations
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

vector<float> cashiers(int quantity, vector<float> values)
{
    sort(values.begin(), values.end());

    vector<float> result;
 
    for (int i = values.size() - 1; i >= 0; i--) {
        while (quantity >= values[i]) {
            quantity -= values[i];
            result.push_back(values[i]);
        }
    }
    return result; 
}

void print(vector<float> V){
    for (int i = 0; i < V.size(); i++)
        cout << V[i] << " ";
    cout << endl; 
}

int main()
{
    float n; 
    cout << "Enter the quantity: "; 
    cin >> n;
    vector<float> mex = {.1, .5, 1, 2, 5, 10, 50}; 
    cout << "Change for " << n
         << ": ";
    print(cashiers(n, mex));
    return 0;
}