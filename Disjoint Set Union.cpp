#include <iostream>
#include <vector>
using namespace std;

// Disjoint Set Union is an important data structure in which:
// we perform union of sets and find the parent (top-most entity of a set) of a particular entity.
// An entity itself can also be a set with one value.
// We perform the union by considering the rank (height of the set tree).

class DisjointSetUnion {
    public:

    int n;
    vector<int> par, rank;

    DisjointSetUnion(int n) {
        this->n = n;

        for(int i = 0; i < n; i++) {
            par.push_back(i);
            rank.push_back(0);
        }
    }

    void unionByRank(int a, int b) {
        int parA = find(a);
        int parB = find(b);

        if(parA == parB) return;

        if(rank[parA] == rank[parB]) { //case 1
            par[parB] = parA;
            rank[parA]++;
        } else if(rank[parA] > rank[parB]) { //case 2
            par[parB] = parA;
        } else { //case 3
            par[parA] = parB;
        }
    }

    int find(int x) {
        if(par[x] == x) return x;

        return par[x] = find(par[x]); //Path Compression
    }

    // Additional function for printing the parents and ranks
    void printInfo() {
        cout << "Parents: ";
        for(int i=0; i<n; i++) {
            cout<<par[i]<<" ";
        }
        cout<<endl;
        
        cout << "Ranks: ";
        for(int i=0; i<n; i++) {
            cout<<rank[i]<<" ";
        }
        cout<<endl;
    }
};

int main() {    
    DisjointSetUnion dsu(6);

    dsu.unionByRank(0, 2);
    cout << dsu.find(2) << endl;

    dsu.unionByRank(1, 3);
    dsu.unionByRank(2, 5);
    dsu.unionByRank(0, 3);

    cout << dsu.find(2) << endl;

    dsu.unionByRank(0, 4);

    dsu.printInfo();
    
    return 0;
}