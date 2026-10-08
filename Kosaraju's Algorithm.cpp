#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Strongly Connected Components:
// A SCC is a group of vertices where every vertex is reachable from every other vertex in the same group.

// Strongly connected components are found using Kosaraju's Algorithm

// Kosaraju Algorithm:

// This algorithm uses Reversed-DFS (Depth-First Search). Below are the steps:
// 1) Get nodes in Stack (Topological sort)
// 2) Transpose the Graph (reverse edges directions)
// 3) Do DFS acc. to stack nodes on Transpose Graph

class Graph {
public:
    int V;
    vector<vector<int>> adj;

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int curr, vector<bool>& vis, vector<vector<int>>& transpose) {
        vis[curr] = 1;

        cout << curr << " ";

        for(int neigh : transpose[curr]) {
            if(!vis[neigh]) {
                dfs(neigh, vis, transpose);
            }
        }        
    }

    void topoSort(int curr, vector<bool> &vis, stack<int> &s) {
        vis[curr] = 1;

        for(int neigh : adj[curr]) {
            if(!vis[neigh]) {
                topoSort(neigh, vis, s);
            }
        }
        s.push(curr);
    }

    void kosaraju() {  // => O(V+E)
        // Step 1 - Topological order => O(V+E)
        vector<bool> vis(V, false);
        stack<int> s;

        for(int i=0; i<V; i++) {
            if(!vis[i]) {
                topoSort(i, vis, s);
            }
        }

        // Step 2 - Transpose graph => O(V+E)
        vector<vector<int>> transpose(V);

        for(int u=0; u<V; u++) { // u ---> v
            vis[u] = false;
            for(int v : adj[u]) {
                transpose[v].push_back(u); // v ---> u
            }
        }

        // Step 3 - dfs on transpose => O(V+E)
        cout << "Printing the SCC: " << endl;

        while(s.size() > 0) {
            int u = s.top();
            s.pop();
            if(!vis[u]) {
                dfs(u, vis, transpose);
                cout << endl;
            }            
        }
    }
};

int main() {    
    Graph graph(5);

    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 0);
    graph.addEdge(2, 1);
    graph.addEdge(3, 4);

    graph.kosaraju();
    
    return 0;
}

