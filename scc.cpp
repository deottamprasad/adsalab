#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
public:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    void SCCUtil(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& stackMember);
    void SCC();
};

void Graph::SCCUtil(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& stackMember) {
    static int time = 0;

    disc[u] = low[u] = ++time;
    st.push(u);
    stackMember[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            SCCUtil(v, disc, low, st, stackMember);
            low[u] = min(low[u], low[v]);
        } else if (stackMember[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    int w = 0; // To store stack extracted vertices
    if (low[u] == disc[u]) {
        cout << "SCC: ";
        while (st.top() != u) {
            w = st.top();
            cout << w << " ";
            stackMember[w] = false;
            st.pop();
        }
        w = st.top();
        cout << w << " ";
        stackMember[w] = false;
        st.pop();
        cout << endl;
    }
}

void Graph::SCC() {
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    vector<bool> stackMember(V, false);
    stack<int> st;

    for (int i = 0; i < V; i++) {
        if (disc[i] == -1) {
            SCCUtil(i, disc, low, st, stackMember);
        }
    }
}

int main() {
	#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int V; // Number of vertices
    cout << "Enter the number of vertices: ";
    cin >> V; // Read the number of vertices

    Graph g(V);

    cout << "Enter the edges (format: v w). Enter -1 -1 to stop:\n";
    int v, w; // Variables for edges
    while (true) {
        cin >> v >> w;
        if (v == -1 && w == -1) {
            break; // Stop input when -1 -1 is entered
        }
        g.addEdge(v, w); // Read edges
    }

    cout << "Strongly Connected Components in the given graph:\n";
    g.SCC();

    return 0;
}

