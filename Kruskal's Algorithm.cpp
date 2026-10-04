#include <iostream>
#include <vector>
#include <algorithm> //For sort()
using namespace std;

// Kruskal's Algorithm is used to find the MST in an Undirected, connect and weighted graph.
// MST stands for Minimum Spanning Tree

// In Kruskal's algorithm, we always pick the smallest edge among all the edges as long as it creates no cycle.

// 1- Sort all the edges based on their weights
// 2- Select edge with the least weight such that no cycle is created.

// NOTE: We use Disjoint Set Union data structure for detecting a cycle in the graph.

class Edge {
public:
    int u, v, wt;
    Edge(int u, int v, int wt) {
        this->u = u;
        this->v = v;
        this->wt = wt;
    }
    // Custom Comparator => '<'
    bool operator<(const Edge &other) const {
        return this->wt < other.wt;
    }
};

class Graph {
public:
    int V;
    vector<Edge> edges;
    vector<int> par, rank;

    Graph(int V) {
        this->V = V;

        for(int i=0; i<V; i++) {
            par.push_back(i);
            rank.push_back(0);
        }
    }

    void addEdge(int u, int v, int wt) {
        edges.push_back(Edge(u, v, wt));
    }

    int find(int x) {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    void unionByRank(int a, int b) {
        int parA = find(a);
        int parB = find(b);

        if(parA == parB) return;

        if(rank[parA] == rank[parB]) {
            par[parB] = parA;
            rank[parA]++;
        } else if(rank[parA] > rank[parB])
            par[parB] = parA;
        else 
            par[parA] = parB;
    }

    void KruskalsAlgorithm() {
        sort(edges.begin(), edges.end()); //O(ElogE)
        int mstCost = 0;
        int count = 0;

        for(int i=0; i<edges.size() && count<V-1; i++) {
            Edge e = edges[i];
            int parU = find(e.u);
            int parV = find(e.v);

            if(parU != parV) {
                unionByRank(e.u, e.v);
                mstCost += e.wt;
                count++;
            }
        }

        cout << "MST Cost: " << mstCost << endl;
    }
};

int main() {    

    Graph graph(4);

    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);

    graph.KruskalsAlgorithm();
    
    return 0;
}