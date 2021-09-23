/*
Eduardo Villalpando, A01023646
Lourdes Badillo, A01024232
Manacher algorithm for finding the longest palindrome substring
09/09/21
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//transfrom input into new string with # chars, without spaces and all lowercases
string preProcess(string s) {
    string result = "#";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != ' ') {
            result += tolower(s[i]);
            result += "#";
        }
    }
    return result;
}

//returns beginning and size of longest palindrome
pair<int,int> find(string s) {
    s = preProcess(s);

    int len = s.length();

    vector<int> P(len,0);

    int mid = 0; 

    int side = 0;

    int maxIdx = 0;

    for (int i = 1; i < len-1; i++) {
        int mirror = 2*mid-1;

        if(i < side) {
            P[i] = min(side-i, P[mirror]);
        }

        int a = s[i + (1 + P[i])];
        int b = s[i - (1 + P[i])];

        while (a == b) {
            P[i]++;
            a = s[i + (1 + P[i])];
            b = s[i - (1 + P[i])];
        }

        if (i + P[i] > side) {
            mid = i;
            side = i + P[i];
            if (P[i] > P[maxIdx]) {
                maxIdx = i;
            }
        }
    }

    pair<int, int> result;

    // beginning of palindrome
    result.first = (maxIdx - P[maxIdx]) / 2;
    // palindrome size
    result.second = P[maxIdx];
    
    return result;
}

int main(int argc, char** argv){

    //Get input string
    string s = argv[1];

    //Find longest palindrome
    pair<int,int> results = find(s);

    //Print results with desired format :) 
    printf("%d %d \n", results.first, results.second);

	return 0; 
}