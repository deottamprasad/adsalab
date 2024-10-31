#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

// Bellman-Ford algorithm to find shortest paths from a single source
bool bellmanFord(const vector<vector<Edge> >& graph, int source, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    dist[source] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            if (dist[u] == INF) continue;
            for (int j = 0; j < graph[u].size(); ++j) {
                Edge e = graph[u][j];
                if (dist[u] != INF && dist[u] + e.weight < dist[e.to]) {
                    dist[e.to] = dist[u] + e.weight;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < n; ++u) {
        if (dist[u] == INF) continue;
        for (int j = 0; j < graph[u].size(); ++j) {
            Edge e = graph[u][j];
            if (dist[u] + e.weight < dist[e.to]) {
                return false; // Negative-weight cycle detected
            }
        }
    }
    return true;
}

// Dijkstra's algorithm to find shortest paths from a single source
vector<int> dijkstra(const vector<vector<Edge> >& graph, int source) {
    int n = graph.size();
    vector<int> dist(n, INF);
    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (int j = 0; j < graph[u].size(); ++j) {
            Edge e = graph[u][j];
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                pq.push(make_pair(dist[e.to], e.to));
            }
        }
    }

    return dist;
}

// Johnson's Algorithm to find shortest paths between all pairs of nodes
vector<vector<int> > johnsonAlgorithm(const vector<vector<Edge> >& graph) {
    int n = graph.size();
    vector<vector<Edge> > modifiedGraph = graph;

    // Add a new node connected to all other nodes with weight 0
    modifiedGraph.push_back(vector<Edge>());
    for (int u = 0; u < n; ++u) {
        modifiedGraph[n].push_back({u, 0});
    }

    // Run Bellman-Ford from the new node
    vector<int> h;
    if (!bellmanFord(modifiedGraph, n, h)) {
        cout << "Graph contains a negative-weight cycle" << endl;
        return {};
    }

    // Reweight the edges
    vector<vector<Edge> > reweightedGraph(n);
    for (int u = 0; u < n; ++u) {
        for (int j = 0; j < graph[u].size(); ++j) {
            Edge e = graph[u][j];
            reweightedGraph[u].push_back({e.to, e.weight + h[u] - h[e.to]});
        }
    }

    // Run Dijkstra's algorithm from each node
    vector<vector<int> > distances(n, vector<int>(n, INF));
    for (int u = 0; u < n; ++u) {
        vector<int> dist = dijkstra(reweightedGraph, u);
        for (int v = 0; v < n; ++v) {
            if (dist[v] != INF) {
                distances[u][v] = dist[v] + h[v] - h[u];
            }
        }
    }

    return distances;
}

int main() {
	#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int n, m;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    if (n <= 0 || m < 0) {
        cout << "Invalid number of nodes or edges." << endl;
        return 0;
    }

    vector<vector<Edge> > graph(n);
    cout << "Enter the edges (format: u v w, where u and v are node indices and w is the weight):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u < 0 || u >= n || v < 0 || v >= n || w < 0) {
            cout << "Invalid edge input." << endl;
            return 0;
        }
        graph[u].push_back({v, w});
    }

    vector<vector<int> > distances = johnsonAlgorithm(graph);

    if (!distances.empty()) {
        cout << "Shortest distances between all pairs of nodes:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (distances[i][j] == INF) {
                    cout << "INF ";
                } else {
                    cout << distances[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    return 0;
}

//4 5
//0 1 1
//0 2 4
//1 2 2
//1 3 2
//2 3 3

//Shortest distances between all pairs of nodes:
//0 1 3 3 
//INF 0 2 2 
//INF INF 0 3 
//INF INF INF 0
