#include <iostream>
#include <deque>
#include <queue>
#include <vector>
using namespace std;

const int SIZE = 13;

struct Edge {
    int src, dest, weight;

    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

class DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if (parent[node] != node) {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    }

    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV) {
            return false;
        }

        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }

        return true;
    }
};

class CityRoadNetwork {
private:
    vector<Edge> edges;
    int numNodes;

public:
    CityRoadNetwork(vector<Edge> const &inputEdges, int n) : edges(inputEdges), numNodes(n) {}

    void printMST() {
        sort(edges.begin(), edges.end());
        DSU dsu(numNodes);
        vector<Edge> mst;

        for (auto &edge : edges) {
            if (dsu.unite(edge.src, edge.dest)) {
                mst.push_back(edge);
                if (mst.size() == numNodes - 1) break;
            }
        }

        cout << "Minimum Spanning Tree edges:\n";
        for (auto &edge : mst) {
            cout << "Edge from " << edge.src << " to " << edge.dest
                 << " with capacity: " << edge.weight << " units\n";
        }
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,8},{0,2,21},{1,2,6},{1,3,5},{1,4,4},{2,7,11},{2,8,8},{3,4,9}, {5,6,10}, {5,7,15}, {5,8,5}, {6,7,3}, {6,8,7}, {7,8,8}, {7,9,5}, {9,10,7}, {9,11,3}, {10,12,4}, {11,12,6}
    };

  CityRoadNetwork network(edges, 9);


    int choice;
    do {
        cout << "City Road Network Menu:\n";
        cout << "[1] Display road network\n";
        cout << "[2] Check contaminant spread (BFS)\n";
        cout << "[3] Plan inspection route (DFS)\n";
        cout << "[4] Calculate shortest paths\n";
        cout << "[5] Find Minimum Spanning Tree\n";
        cout << "[0] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                network.displayNetwork();
                break;
            case 2: {
                int start;
                cout << "Enter starting block: ";
                cin >> start;
                network.inspectBFS(start);
                break;
            }
            case 3: {
                int start;
                cout << "Enter starting block: ";
                cin >> start;
                network.planInspectionDFS(start);
                break;
            }
            case 4: {
                int start;
                cout << "Enter starting block: ";
                cin >> start;
                network.findShortestPaths(start);
                break;
            }
            case 5:
                network.printMST();
                break;
            case 0:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
