#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Graph {
    int V;
    vector<vector<bool>> adj;
    
    void dfs(int v, vector<bool> &visited, stack<int> &Stack) {
        visited[v] = true;
        for (int i = 0; i < V; i++) {
            if (adj[v][i] &&!visited[i])
                dfs(i, visited, Stack);
        }
        Stack.push(v);
    }
public:
    Graph(int V) {
        this->V = V;
        adj = vector<vector<bool>>(V, vector<bool>(V, false));
    }

    void addEdge(int v, int w) {
        adj[v][w] = true;
    }

    void topologicalSort() {
        stack<int> Stack;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (visited[i] == false)
                dfs(i, visited, Stack);
        }

        cout << "Result of Topological Sorting is: ";
        while (Stack.empty() == false) {
            cout << Stack.top() << " ";
            Stack.pop();
        }
        cout << endl;
    }
};

int main() {
    int n, u, v;
    cout<<"Enter the number of edges: ";
    cin>>n;
    Graph g(n);

    for(int i=0; i<n; i++){
        cout<<"Enter u"<<(i+1)<<": ";
        cin>>u;
        cout<<"Enter v"<<(i+1)<<": ";
        cin>>v;
        g.addEdge(u, v);
    }
    g.topologicalSort();
    return 0;
}