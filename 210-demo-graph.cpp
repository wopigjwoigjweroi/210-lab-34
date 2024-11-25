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

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class min {

    private: 
        vector<int> parent, rank; 

    public: 

        DSU(int i) {

            parent.resize(i); 

            rank.resize(i, 0); 

            for (int t = 0; t = i; t++) {

                parent[t] = t; 

            }

        }

        int find(int node) {
        if (parent[node] != node) {
            parent[node] = find(parent[node]); // Path compression
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

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[edge.dest].push_back(make_pair(edge.src, edge.weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "City Road Network: " << endl << "================================\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Block: " << i << " connects to: \n";
            for (Pair v : adjList[i])
                cout << "-> Block " << v.first << "( Travel Time: " << v.second << " mins) \n";
            cout << endl;
        }
    }

    void shortestPath(int s) {

        vector<int> dist(SIZE, INT_MAX); 

        dist[s] = 0; 

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq; 

        pq.push({0, s}); 

        while (!pq.empty()) {

            int distance = pq.top().first; 
            int node = pq.top().second; 
            pq.pop(); 

            if (distance > dist[node]) continue; 

            for (auto &neighbor : adjList[node]) {

                int nextNode = neighbor.first; 
                int weight = neighbor.second; 

            if (dist[node] + weight < dist[nextNode]) {

                dist[nextNode] = dist[node] + weight; 
                pq.push({dist[nextNode], nextNode}); 
            }
            }
        }

        cout << "Shortest Path from block " << s << endl; 

        for (int i = 0; i < SIZE; i++) {

            cout << s << " -> " << i << " : " << dist[i] << endl; 
        }

    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,8},{0,2,21},{1,2,6},{1,3,5},{1,4,4},{2,7,11},{2,8,8},{3,4,9}, {5,6,10}, {5,7,15}, {5,8,5}, {6,7,3}, {6,8,7}, {7,8,8}, {7,9,5}, {9,10,7}, {9,11,3}, {10,12,4}, {11,12,6}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    graph.shortestPath(0); 

    return 0;
}
