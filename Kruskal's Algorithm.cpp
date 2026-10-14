#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge
struct Edge
{
    int u, v, weight;
};

// Find the parent of a vertex
int findParent(int parent[], int x)
{
    if (parent[x] == x)
        return x;

    return parent[x] = findParent(parent, parent[x]);
}

// Join two sets
void unionSets(int parent[], int rank[], int u, int v)
{
    int rootU = findParent(parent, u);
    int rootV = findParent(parent, v);

    if (rootU != rootV)
    {
        if (rank[rootU] < rank[rootV])
            parent[rootU] = rootV;

        else if (rank[rootU] > rank[rootV])
            parent[rootV] = rootU;

        else
        {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Compare edges by weight
bool compareEdges(Edge a, Edge b)
{
    return a.weight < b.weight;
}

// Kruskal's Algorithm
void kruskal(int V, vector<Edge> edges)
{
    // Sort edges by increasing weight
    sort(edges.begin(), edges.end(), compareEdges);

    int parent[V];
    int rank[V];

    // Initially, every vertex is its own set
    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    int totalCost = 0;
    int edgeCount = 0;

    cout << "\nMinimum Spanning Tree:\n";
    cout << "Edge\tWeight\n";

    // Process edges
    for (Edge edge : edges)
    {
        int rootU = findParent(parent, edge.u);
        int rootV = findParent(parent, edge.v);

        // If different sets, adding the edge will not create a cycle
        if (rootU != rootV)
        {
            cout << char(edge.u + 'A')
                 << " - "
                 << char(edge.v + 'A')
                 << "\t"
                 << edge.weight
                 << endl;

            totalCost += edge.weight;

            unionSets(parent, rank, edge.u, edge.v);

            edgeCount++;

            // MST contains V - 1 edges
            if (edgeCount == V - 1)
                break;
        }
    }

    cout << "\nTotal cost of MST = " << totalCost << endl;
}

int main()
{
    int V = 5;

    // Graph edges
    vector<Edge> edges =
    {
        {0, 1, 2},  // A-B
        {0, 3, 6},  // A-D
        {1, 2, 3},  // B-C
        {1, 3, 8},  // B-D
        {1, 4, 5},  // B-E
        {2, 4, 7},  // C-E
        {3, 4, 9}   // D-E
    };

    kruskal(V, edges);

    return 0;
}
