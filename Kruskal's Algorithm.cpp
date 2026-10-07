#include <iostream>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

int parent[20];

int findParent(int x) {
    if (parent[x] == x)
        return x;

    return parent[x] = findParent(parent[x]);
}

void unionSet(int a, int b) {
    a = findParent(a);
    b = findParent(b);

    parent[b] = a;
}

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

int main() {
    int n, e;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    Edge edges[50];

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < e; i++) {
        cin >> edges[i].u
            >> edges[i].v
            >> edges[i].weight;
    }

    for (int i = 0; i < n; i++)
        parent[i] = i;

    sort(edges, edges + e, compare);

    int total = 0;
    int count = 0;

    cout << "\nMinimum Spanning Tree:\n";

    for (int i = 0; i < e && count < n - 1; i++) {

        int u = edges[i].u;
        int v = edges[i].v;

        if (findParent(u) != findParent(v)) {

            cout << u << " - " << v
                 << " = " << edges[i].weight << endl;

            total += edges[i].weight;
            unionSet(u, v);
            count++;
        }
    }

    cout << "Total MST Cost = " << total << endl;

    return 0;
}
