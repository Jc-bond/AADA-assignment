#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge between two nodes
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

// Custom comparator to sort edges by weight
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Utility function to find the root of a node using path compression
int findRoot(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = findRoot(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Utility function to perform union of two sets by rank
void unionSets(vector<Subset>& subsets, int x, int y) {
    int rootX = findRoot(subsets, x);
    int rootY = findRoot(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Function to find Minimum Spanning Tree (MST) using Kruskal's algorithm
vector<Edge> kruskalMST(vector<Edge>& edges, int numNodes) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareEdges);

    vector<Edge> mst;
    vector<Subset> subsets(numNodes);

    // Initialize subsets for each node
    for (int i = 0; i < numNodes; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int mstEdges = 0;
    int edgeIndex = 0;

    // Build MST by adding edges in sorted order
    while (mstEdges < numNodes - 1) {
        Edge nextEdge = edges[edgeIndex++];
        int rootSrc = findRoot(subsets, nextEdge.src);
        int rootDest = findRoot(subsets, nextEdge.dest);

        // Check if including this edge forms a cycle
        if (rootSrc != rootDest) {
            mst.push_back(nextEdge);
            unionSets(subsets, rootSrc, rootDest);
            mstEdges++;
        }
    }

    return mst;
}

int main() {
    // Example: Neighbourhoods represented as nodes and connections as edges
    int numNodes = 6;
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 3}, {1, 2, 1},
        {1, 3, 2}, {2, 3, 4}, {3, 4, 2},
        {4, 5, 6}
    };

    // Find Minimum Spanning Tree (MST) using Kruskal's algorithm
    vector<Edge> mst = kruskalMST(edges, numNodes);

    // Output the edges of the MST
    cout << "Edges of Minimum Spanning Tree (MST) using Kruskal's algorithm:" << endl;
    for (const auto& edge : mst) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
    }

    return 0;
}
