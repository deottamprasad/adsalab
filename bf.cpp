#include <iostream>
#include <vector>
#include <climits>
#include <sstream>  // For ostringstream
using namespace std;

struct Path {
    int from;
    int to;
    int cost;
};

class Network {
    int vertices;
    vector<Path> connections;

public:
    Network(int vertices) : vertices(vertices) {}

    void addConnection(int start, int end, int cost) {
        if (start < 0 || end < 0 || start >= vertices || end >= vertices) {
            cout << "Invalid connection from " << start << " to " << end << endl;
            return;
        }
        Path conn;
        conn.from = start;
        conn.to = end;
        conn.cost = cost;
        connections.push_back(conn);
    }

    // Helper function to convert int to string (to avoid std::to_string)
    string intToString(int value) {
        ostringstream oss;
        oss << value;
        return oss.str();
    }

    void shortestPath(int source) {
        if (source < 0 || source >= vertices) {
            cout << "Invalid source node: " << source << endl;
            return;
        }

        vector<int> minDistance(vertices, INT_MAX);
        minDistance[source] = 0;

        // Perform V-1 relaxations for all connections
        for (int step = 1; step < vertices; ++step) {
            for (int j = 0; j < connections.size(); ++j) {
                Path conn = connections[j];
                if (minDistance[conn.from] != INT_MAX && minDistance[conn.from] + conn.cost < minDistance[conn.to]) {
                    minDistance[conn.to] = minDistance[conn.from] + conn.cost;
                }
            }
        }

        // Check for cycles with negative weights
        for (int k = 0; k < connections.size(); ++k) {
            Path conn = connections[k];
            if (minDistance[conn.from] != INT_MAX && minDistance[conn.from] + conn.cost < minDistance[conn.to]) {
                cout << "Cycle with negative weight detected" << endl;
                return;
            }
        }

        // Display shortest distances from the source
        for (int node = 0; node < vertices; ++node) {
            cout << "Node " << node << " \t Distance: " 
                 << (minDistance[node] == INT_MAX ? "INF" : intToString(minDistance[node])) << endl;
        }
    }
};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int vertices, edges;
    cin >> vertices >> edges;
    if (vertices <= 0) {
        cout << "Number of nodes must be positive." << endl;
        return 0;
    }
    if (edges < 0) {
        cout << "Number of connections cannot be negative." << endl;
        return 0;
    }

    Network net(vertices);
    for (int i = 0; i < edges; ++i) {
        int start, end, weight;
        cin >> start >> end >> weight;
        net.addConnection(start, end, weight);
    }

    int source;
    cout << "Enter source node: ";
    cin >> source;
    net.shortestPath(source);
    return 0;
}





//5 8
//0 1 -1
//0 2 4
//1 2 3
//1 3 2
//1 4 2
//3 2 5
//3 1 1
//4 3 -3

//0 0
//1 -1
//2 2
//3 -2
//4 1
