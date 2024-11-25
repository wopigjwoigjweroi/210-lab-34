// COMSC-210 | Lab-34 | Jeremiah Ortiz
include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

struct Edge {
    int src, dest, weight;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

typedef pair<int, int> Pair;

class CityRoadNetwork {
private:
    vector<Edge> edges;
    vector<vector<Pair>> adjList;
    int numNodes;

public:
    CityRoadNetwork(vector<Edge> const& inputEdges, int n) : edges(inputEdges), numNodes(n) {
        adjList.resize(numNodes);
        for (auto& edge : inputEdges) {
            adjList[edge.src].push_back({ edge.dest, edge.weight });
            adjList[edge.dest].push_back({ edge.src, edge.weight });
        }
    }

    void displayNetwork() {
        cout << "City Road Network Topology:\n================================\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Block " << i << " connects to:\n";
            for (auto& neighbor : adjList[i]) {
                cout << "  → Block " << neighbor.first << " (Travel Time: " << neighbor.second << " min)\n";
            }
        }
        cout << endl;
    }

    void inspectBFS(int start) {
        if (start < 0 || start >= numNodes) {
            cout << "Invalid starting block.\n";
            return;
        }

        vector<bool> visited(numNodes, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "Layer-by-Layer Inspection (BFS) from Block " << start << ":\n";
        while (!q.empty()) {
            int block = q.front();
            q.pop();
            cout << "Checking Block " << block << "\n";

            for (auto& neighbor : adjList[block]) {
                if (!visited[neighbor.first]) {
                    cout << "  → Next accessible block: Block " << neighbor.first << " - Travel Time: " << neighbor.second << " min\n";
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    void DFSUtil(int start, vector<bool>& visited) {
        visited[start] = true;
        cout << "Inspecting Block " << start << "\n";

        for (auto& neighbor : adjList[start]) {
            if (!visited[neighbor.first]) {
                cout << "  → Possible route to Block " << neighbor.first << " - Travel Time: " << neighbor.second << " min\n";
                DFSUtil(neighbor.first, visited);
            }
        }
    }

    void planInspectionDFS(int start) {
        if (start < 0 || start >= numNodes) {
            cout << "Invalid starting block.\n";
            return;
        }

        vector<bool> visited(numNodes, false);
        cout << "Network Trace (DFS) from Block " << start << ":\n";
        DFSUtil(start, visited);
        cout << endl;
    }

    void findShortestPaths(int start) {
        if (start < 0 || start >= numNodes) {
            cout << "Invalid starting block.\n";
            return;
        }

        vector<int> dist(numNodes, INT_MAX);
        dist[start] = 0;
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({ 0, start });

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentDist > dist[currentNode]) continue;

            for (auto& neighbor : adjList[currentNode]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;

                if (dist[currentNode] + weight < dist[nextNode]) {
                    dist[nextNode] = dist[currentNode] + weight;
                    pq.push({ dist[nextNode], nextNode });
                }
            }
        }

        cout << "Shortest path from block " << start << ":\n";
        for (int i = 0; i < numNodes; i++) {
            cout << start << " -> " << i << " : " << dist[i] << " min\n";
        }
        cout << endl;
    }

    void printMST() {
        sort(edges.begin(), edges.end());
        vector<int> parent(numNodes);
        for (int i = 0; i < numNodes; i++) parent[i] = i;

        function<int(int)> find = [&](int node) {
            if (parent[node] != node) {
                parent[node] = find(parent[node]);
            }
            return parent[node];
            };

        auto unite = [&](int u, int v) {
            int rootU = find(u);
            int rootV = find(v);
            if (rootU != rootV) {
                parent[rootV] = rootU;
                return true;
            }
            return false;
            };

        cout << "Minimum Spanning Tree edges:\n";
        for (auto& edge : edges) {
            if (unite(edge.src, edge.dest)) {
                cout << "Edge from " << edge.src << " to " << edge.dest
                    << " with capacity: " << edge.weight << " units\n";
            }
        }
        cout << endl;
    }
};

int main() {
    vector<Edge> edges = {
        {0, 1, 5}, {0, 2, 10}, {1, 2, 3}, {1, 3, 2}, {2, 4, 8},
        {3, 4, 4}, {3, 5, 7}, {4, 6, 6}, {5, 7, 3}, {6, 8, 5},
        {7, 8, 4}, {6, 7, 2}, {2, 5, 9}
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
