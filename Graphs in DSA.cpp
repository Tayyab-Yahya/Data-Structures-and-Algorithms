#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

class UndirGraph {
	int V;
	list<int> *l;
	
public:
	UndirGraph(int V) {
		this->V = V;
		l = new list<int>[V];
	}
	
	void addEdge(int u, int v) {
		l[u].push_back(v);
		l[v].push_back(u);
	}
	
	void printGraph() {
		for(int i=0; i<V; i++) {
			cout<<i<<": ";
			for(int &val: l[i]) {
				cout<<val<<" ";
			}
			cout<<endl;
		}
	}

    void bfs() {
        queue<int> Q;
        vector<bool> isVisited(V, false);

        Q.push(0);
        isVisited[0] = true;

        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            cout<<u<<" ";
            for(int &val : l[u]) {
                if(!isVisited[val]) {
                    isVisited[val] = 1;
                    Q.push(val);
                }
            }            
        }
        cout<<endl;
    }

    void dfsHelper(int u, vector<bool>& isVisited) {
        cout<<u<<" ";
        isVisited[u] = true;
        for(int &v : l[u]) {
            if(!isVisited[v]) {
                dfsHelper(v, isVisited);
            }
        }
    }
    void dfs() {
        vector<bool> isVisited(V, false);
        int src = 0;
        dfsHelper(src, isVisited);
        cout<<endl;
    }

    bool isCycleUndirDFS(int src, int par, vector<bool>& isVisited) {
        isVisited[src] = true;
        list<int> &neighbors = l[src];
        for(int &v : neighbors) {
            if(!isVisited[v]) {
                if(isCycleUndirDFS(v, src, isVisited))
                    return true;
            } else if(par != v) {
                return true;
            }
        }
        return false;
    }    
    bool isCycleDFS() {
        vector<bool> isVis(V, false);
        for(int i=0; i<V; i++) {
            if(!isVis[i]){
                if(isCycleUndirDFS(i, -1, isVis))
                    return true;
            }
        }
        return false;
    }

    bool isCycleUndirBFS(int src, vector<bool>& isVis) {
        queue<pair<int, int>> Q; //<val, par>
        Q.push({src, -1});
        isVis[src] = true;
        while(!Q.empty()) {
            int u = Q.front().first;
            int par = Q.front().second;
            Q.pop();
            for(int &v : l[u]) {
                if(!isVis[v]) {
                    Q.push({v, u});
                    isVis[v] = true;
                } else if(v != par) {
                    return true;
                }
            }            
        }
        return false;
    }
    bool isCycleBFS() {
        vector<bool> isVis(V, false);
        for(int i=0; i<V; i++) {
            if(!isVis[i]) {
                if(isCycleUndirBFS(i, isVis))
                    return true;
            }
        }
        return false;
    }
};

class DirGraph {
    int V;
    list<int> *l;

    public:

    DirGraph(int V) {
        this->V = V;
        l = new list<int> [V];
    }

    bool isCycleDirDFS(int src, vector<bool> &vis, vector<bool> &recPath) {
        vis[src] = true;
        recPath[src] = true;

        for(int v : l[src]) {
            if(!vis[v]) {
                if(isCycleDirDFS(v, vis, recPath))
                    return true;
            } else if(recPath[v]) {
                return true;
            }
        }

        recPath[src] = false;
        return false;
    }
    bool isCycleDFS() {
        vector<bool> vis(V, false);
        vector<bool> recPath(V, false);

        for(int i=0; i<V; i++) {
            if(!vis[i]) {
                if(isCycleDirDFS(i, vis, recPath))
                    return true;
            }
        }
        return false;
    }

    void addEdge(int u, int v) {
        l[u].push_back(v);
    }

    //Topological Sorting
    void dfs(int curr, vector<bool>& vis, stack<int>& s) {
        vis[curr] = true;
        for(int &v : l[curr]) {
            if(!vis[v]) {
                dfs(v, vis, s);
            }
        }
        s.push(curr);
    }
    void topoSort() {
        stack<int> s;
        vector<bool> vis(V, false);
        for(int i=0; i<V; i++) {
            if(!vis[i]) {
                dfs(i, vis, s);
            }
        }

        cout<<"Topological Sorting: ";
        while(!s.empty()) {
            cout<<s.top()<<" ";
            s.pop();
        }
        cout<<endl;
    }

    void topologicalSortUsingKahnsAlgo() {
        vector<int> inDegree(V, 0);
        
        // Calc the in-degree
        for(int i=0; i<V; i++) {
            for(int &v : l[i]) {
                inDegree[v]++;
            }
        }
        // Push 0 In-degree Nodes
        queue<int> q;
        for(int i=0; i<V; i++) {
            if(inDegree[i] == 0) {
                q.push(i);
            }
        }
        // Main part
        vector<int> result;
        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            for(int &v : l[curr]) {
                inDegree[v]--;
                if(inDegree[v] == 0) {
                    q.push(v);                    
                }      
            }
            result.push_back(curr);
        }

        // Incase if we don't know whether the graph is a DAG (Directed 
        // Acyclic Graph) or not? We can uncomment the below code.
        
        // if(result.size() == V) {
        //     cout<<"DAG! No cycle exists."<<endl;
        // } else {
        //     cout<<"Cycle exists! Not a DAG."<<endl;
        // }
        
        for(int & val : result) {
            cout<<val<<" ";
        }
        cout<<endl;
    }
};

int main() {
	
	UndirGraph g(5);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(0, 3);
	g.addEdge(1, 2);
    g.addEdge(3, 4);
	
	// g.printGraph();
    // cout<<"BFS: "; g.bfs();    
    // cout<<"DFS: "; g.dfs();
    // cout<<g.isCycleBFS()<<endl;

    DirGraph g1(6);
    g1.addEdge(3, 1);
    g1.addEdge(2, 3);
    g1.addEdge(4, 0);
    g1.addEdge(4, 1);
    g1.addEdge(5, 0);
    g1.addEdge(5, 2);
    // cout<<g1.isCycleDFS()<<endl;
    // g1.topoSort();

    g1.topologicalSortUsingKahnsAlgo();
	
	return 0;
}
