#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Graph {
public:
    vector<vector<int>> adj;
    int V;

    // For Tarjan's Algorithm
    vector<int> dt, low;
    int time;

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int parU, set<int> &criticalPoints) {
        dt[u] = low[u] = ++time;
        int children = 0;

        for(int i=0; i<adj[u].size(); i++) {
            int v = adj[u][i];
            
            if(dt[v] == -1) {
                children++;
                dfs(v, u, criticalPoints);
                //update low
                low[u] = min(low[u], low[v]);
                if(parU != -1 && low[v] >= dt[u]) {
                    criticalPoints.insert(u);
                }                
            } else if(parU != v) {
                low[u] = min(low[u], dt[v]);
            }            
        }

        if(parU == -1 && children > 1) {
            criticalPoints.insert(u);
        }
    }
    
    int articulationPoints() { // Main Function
        time = 0;
        dt.resize(V, -1); // dt[i] == -1 => Unvisited Node
        low.resize(V);

        set<int> criticalPoints;

        for(int i=0; i<V; i++) {
            if(dt[i] == -1) {
                dfs(i, -1, criticalPoints);
            }
        }

        cout << "Critical Points: ";
        for(auto val : criticalPoints) {
            cout << val << " ";
        }
        cout << endl;

        return criticalPoints.size();
    }
};

int main() {
    Graph graph(6);

    graph.addEdge(1, 0);
    graph.addEdge(1, 2);
    graph.addEdge(4, 3);
    graph.addEdge(4, 5);
    graph.addEdge(4, 1);

    int cp = graph.articulationPoints();
    cout << "Critical Points count: " << cp << endl;
    
    return 0;
}
