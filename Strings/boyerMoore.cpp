//Boyer-Moore Algorithm for Exact String Matching

#include <iostream>
#include <vector>
using namespace std;

// bad character heuristic 
void badCharacterHeuristic(string str, int size, int badChar[256]){
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }   
    
    for (int i = 0; i < size; i++){
        badChar[(int)str[i]] = i;
    }
}

//search using bad char heuristic
vector<int> search( string text, string pattern){
    vector<int> results; 

	int m = pattern.size(); 
	int n = text.size(); 

	int badchar[256]; 

	badCharacterHeuristic(pattern, m, badchar); 

	int shift = 0; 

	while(shift <= (n - m)) { 
		int j = m - 1; 

		while(j >= 0 && pattern[j] == text[shift + j]){
			j--; 
        } 

		if (j < 0) { 
            results.push_back(shift);
            if(shift + m < n){
                shift += m - badchar[text[shift + m]];
            }
            else{
                 shift += 1; 
            }
		} 

		else{
            shift += max(1, j - badchar[text[shift + j]]);
        }
			
	} 

    return results; 
} 


int main(int argc, char** argv){
    string text = argv[1];
    string pattern = argv[2];
    vector<int> results = search(text, pattern); 
    for(int i = 0; i < results.size(); i++){
        cout << results[i] << " ";
    }
	return 0; 
}
