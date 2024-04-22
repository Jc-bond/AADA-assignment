#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent an edge between two nodes
struct Edge {
    int dest, weight;
};

// Function to find Minimum Spanning Tree (MST) using Prim's algorithm
vector<vector<Edge>> primMST(vector<vector<Edge>>& graph, int numNodes) {
    vector<bool> inMST(numNodes, false);
    vector<vector<Edge>> mst(numNodes);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // (weight, node)
    pq.push({0, 0}); // Start from node 0 with weight 0

    while (!pq.empty()) {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;

        for (const auto& edge : graph[u]) {
            int v = edge.dest;
            int w = edge.weight;
            if (!inMST[v]) {
                mst[u].push_back({v, w});
                mst[v].push_back({u, w});
                pq.push({w, v});
            }
        }
    }

    return mst;
}

int main() {
    // Example: Neighbourhoods represented as nodes and connections as weighted adjacency list
    int numNodes = 6;
    vector<vector<Edge>> graph(numNodes);

    // Populate graph with edges (neighbourhood connections)
    graph[0].push_back({1, 4});
    graph[0].push_back({2, 3});
    graph[1].push_back({0, 4});
    graph[1].push_back({2, 1});
    graph[1].push_back({3, 2});
    graph[2].push_back({0, 3});
    graph[2].push_back({1, 1});
    graph[2].push_back({3, 4});
    graph[3].push_back({1, 2});
    graph[3].push_back({2, 4});
    graph[3].push_back({4, 2});
    graph[4].push_back({3, 2});
    graph[4].push_back({5, 6});
    graph[5].push_back({4, 6});

    // Find Minimum Spanning Tree (MST) using Prim's algorithm
    vector<vector<Edge>> mst = primMST(graph, numNodes);

    // Output the edges of the MST
    cout << "Edges of Minimum Spanning Tree (MST) using Prim's algorithm:" << endl;
    for (int u = 0; u < numNodes; u++) {
        for (const auto& edge : mst[u]) {
            cout << u << " - " << edge.dest << " : " << edge.weight << endl;
        }
    }

    return 0;
}
