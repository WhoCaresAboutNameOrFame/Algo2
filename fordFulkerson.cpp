#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();
vector<vector<int>> residualGraph;
vector<int> parent;

bool dfs(int s, int t, int V) {
    vector<bool> visited(V, false);
    parent.assign(V, -1);
    visited[s] = true;
    bool foundPath = false;
    while (!foundPath) {
        foundPath = true; // Assume no more paths until proven otherwise
        for (int u = 0; u < V; ++u) {
            if (visited[u]) {
                for (int v = 0; v < V; ++v) {
                    if (!visited[v] && residualGraph[u][v] > 0) {
                        parent[v] = u;
                        visited[v] = true;
                        if (v == t) // If we reached the sink, break out of the loop
                            return true;
                        foundPath = false; // We found a path, so we're not done yet
                        break;
                    }
                }
            }
        }
    }
    return false; // If we're here, no path was found
}

int fordFulkerson(int s, int t, int V) {
    int max_flow = 0;
    parent.assign(V, -1);
    while (dfs(s, t, V)) {
        int path_flow = INF;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, residualGraph[u][v]);
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= path_flow;
            residualGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

void addEdge(vector<vector<int>>& graph, int u, int v, int w) {
    graph[u][v] = w;
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;
    vector<vector<int>> graph(V, vector<int>(V, 0));

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cout << "Enter edge " << i + 1 << " (u v w): ";
        cin >> u >> v >> w;
        addEdge(graph, u, v, w);
    }

    int source, sink;
    cout << "Enter source node: ";
    cin >> source;
    cout << "Enter sink node: ";
    cin >> sink;

    residualGraph = graph;

    cout << "\nMaximum Flow Using Ford Fulkerson Algo: " << fordFulkerson(source, sink, V) << endl;
    return 0;
}
