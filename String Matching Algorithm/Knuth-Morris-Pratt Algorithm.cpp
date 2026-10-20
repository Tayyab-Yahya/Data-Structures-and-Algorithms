#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Knuth-Morris-Pratt String Matching Algorithm (KMP)

// Used to find a sub-string inside another string.

// Suppose the length of STRING = n
// And length of sub-string = m

// Then,
// Brute Force TC => O(n * m)
// KMP Algo's TC  => O(n)

// Helper Func
void computeLPS(string& pat, vector<int>& LPS, int M) {
    int length = 0;
    int i = 1;
    
    while(i < M) {
        if(pat[i] == pat[length]) {
            length++;
            LPS[i] = length;
            i++;
        } else {
            if(length != 0) {
                length = LPS[length-1];
            } else {
                LPS[i] = 0;
                i++;
            }
        }
    }
}

vector<int> search(string pat, string txt) {
    int N = txt.size();
    int M = pat.size();
    
    vector<int> result;

    // Create an LPS array to store the length of longest proper prefix which is also a suffix.
    // lps[i] = The longest proper prefix of pat[0..i] which is also a suffix of pat[0..i].
    
    vector<int> LPS(M, 0);
    computeLPS(pat, LPS, M);

    // Apply KMP Code
    
    int i = 0, j = 0;
    while(i < N) {
        if(pat[j] == txt[i]) {
            i++; j++;
        }

        if(j == M) {
            int idx = i - j + 1; // If 1-based Indexing
            result.push_back(idx);
            j = LPS[j-1];
        } else if(i < N && pat[j] != txt[i]) {
            if(j != 0) {
                j = LPS[j-1];
            } else {
                i++;
            }
        }
    }

    return result;
}

int main() {
    string txt = "ABABDABACDABABCABAB";
    string pat = "ABABCABAB";

    vector<int> matches = search(pat, txt);

    cout << "Pattern found at indices: ";
    for (int idx : matches) {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}