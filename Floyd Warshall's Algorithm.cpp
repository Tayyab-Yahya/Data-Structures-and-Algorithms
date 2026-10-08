#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Floyd Warshall Algorithm:
// Shortest distance between every pair of vertices in a weighted graph.
// It is a dynamic programming based algorithm.

// It can be used for:
    // => Directed graph
    // => Undirected graph
    // => +ve and -ve edge values

class Graph {
public:
    int V;
    vector<vector< pair<int, int> >> adj; // {v, wt}

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int wt) {
        adj[u].push_back({v, wt});
    }

    void floydWarshall() {
        const int INF = 1e9; // Infinifty value => 1 billion
        vector<vector<int>> dist(V, vector<int> (V, INF));

        // Storing current graph info
        for(int i=0; i<V; i++)
            dist[i][i] = 0;
        for(int u=0; u<V; u++) {
            for(auto edge : adj[u]) {
                int v = edge.first;
                int wt = edge.second;
                dist[u][v] = wt;
            }
        }

        // Actual algorithm
        for(int k=0; k<V; k++) {
            for(int i=0; i<V; i++) {
                for(int j=0; j<V; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
                }
            }
        }

        // Print
        for(int i=0; i<V; i++) {
            for(int j=0; j<V; j++) {
                if(dist[i][j] == INF) {
                    cout << "INF ";
                } else {
                    cout << dist[i][j] << " ";
                }
            }
            cout << endl;
        }

        // Check for negative weighted cycles in the graph
        for(int i=0; i<V; i++) {
            if(dist[i][i] < 0) {
                cout << "Negative weighted cycle exists.\n";
                break;
            }
        }
    }
};

int main() {
    Graph graph(4);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 11);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 8);
    graph.addEdge(2, 3, 3);

    graph.floydWarshall();
    
    return 0;
}