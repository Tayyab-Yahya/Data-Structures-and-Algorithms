#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

// Prim's Algorithm is used to find the Minimum Spanning Tree (MST)
// Spanning Tree is a graph in which all the vertices (V) are connected with exactly (V-1) edges.
// And the spanning tree having minimum value of the sum of all edges is called Minimum Spanning Tree.
// For a MST, the original graph must be connected, undirected and weighted graph.

// Prim's Algorithm is a greedy algorithm.
// In Greedy algorithm, we always choose the minimum/maximum value from all available values.

int primMST(int V, vector<vector<pair<int, int>>>& adj) {
    
    vector<bool> inMst(V, false);
    int mstCost = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

    pq.push({0, 0});    // {wt, u}

    while(!pq.empty()) {        
        int u = pq.top().second;
        int wt = pq.top().first;
        pq.pop();

        if(!inMst[u]) {
            inMst[u] = true;
            mstCost += wt;
            
            for(int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first;
                int w = adj[u][i].second;
                if(!inMst[v])
                    pq.push({w, v});
            }
        }
    }
    
    return mstCost;
}

int main() {
    int V = 4;
    vector< vector< pair<int, int> > > adj(V);
    
    // Undirected weighted graph
    
    adj[0].push_back({1, 10});    // v, wt
    adj[1].push_back({0, 10});    // u, wt

    adj[0].push_back({3, 30});
    adj[3].push_back({0, 30});
    
    adj[0].push_back({2, 15});
    adj[2].push_back({0, 15});
    
    adj[1].push_back({3, 40});
    adj[3].push_back({1, 40});
    
    adj[2].push_back({3, 50});
    adj[3].push_back({2, 50});

    cout << "Cost of MST: " << primMST(V, adj) << endl;
    
    return 0;
}