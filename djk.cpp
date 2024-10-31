#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>

using namespace std;

struct Edge {
    int v;
    int weight;
};

class Graph {
    int V;
    vector<vector<Edge> > adj;

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v, int weight) {
        if (u < 0 || v < 0 || u >= V || v >= V) {
            cout << "Invalid edge from " << u << " to " << v << endl;
            return;
        }
        if (weight < 0) {
            cout << "Negative weights are not allowed for Dijkstra's algorithm." << endl;
            return;
        }
        Edge edge;
        edge.v = v;
        edge.weight = weight;
        adj[u].push_back(edge);
    }

    void dijkstra(int src) {
        if (src < 0 || src >= V) {
            cout << "Invalid source vertex: " << src << endl;
            return;
        }

        vector<int> dist(V, INT_MAX);
        vector<bool> visited(V, false);
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        
        dist[src] = 0;
        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (int i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i].v;
                int weight = adj[u][i].weight;
                if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        for (int i = 0; i < V; ++i) {
            cout << "Node " << i << " \t Distance: ";
            if (dist[i] == INT_MAX) {
                cout << "INF" << endl;
            } else {
                cout << dist[i] << endl;
            }
        }
    }
};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int V, E;
    cin >> V >> E;
    if (V <= 0) {
        cout << "Number of vertices must be positive." << endl;
        return 0;
    }
    if (E < 0) {
        cout << "Number of edges cannot be negative." << endl;
        return 0;
    }

    Graph g(V);
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    int src;
    cout << "Enter source vertex: ";
    cin >> src;
    g.dijkstra(src);
    return 0;
}

//5 7
//0 1 10
//0 2 3
//1 2 1
//1 3 2
//2 1 4
//2 3 8
//3 4 7
//0
//
//0 0
//1 7
//2 3
//3 9
//4 16
