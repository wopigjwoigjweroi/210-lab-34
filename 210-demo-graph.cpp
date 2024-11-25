#include <iostream>
#include <deque>
#include <queue>
#include <vector>
using namespace std;

const int SIZE = 13;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

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


    // void DFS(int s, vector<bool> &visited) {

    //     cout << "Inspecting Block: " << s << endl; 

    //     visited[s] = true; 

    //     for (auto &neighbor : adjList[s]) {

    //         int n = neighbor.first; 

    //         if (!visited[n]) {

    //             cout << " -> Possible route to block " << neighbor.first << " - Travel time: " << neighbor.second << " mins\n"; 
    //             DFS(n, visited); 
    //         }
    //     }
    // }

    // void DFSTrace(int s) {

    //     vector<bool> visited(SIZE, false);

    //     cout << "Network Trace (DFS) from Block " << s << ":\n";
    //     cout << "Purpose: Exploring possible routes through the city\n=======================================\n";
    //     DFS(s, visited);
    // }

    // void BFS(int s) {

    //     vector<bool> visited(SIZE, false); 

    //     queue<int> q; 

    //     visited[s] = true; 

    //     q.push(s); 

    //     cout << "Layer-by-Layer Network Inspection (BFS) from Block " << s << ":\n";
    //     cout << "Purpose: Analyzing access routes by distance from the central block\n" << "=================================================\n";

    //     while (!q.empty()) {

    //         int n = q.front(); 

    //         q.pop(); 

    //         cout << n << " "; 

    //         for (auto &neighbor : adjList[n]) {

    //             int next = neighbor.first; 

    //             if (!visited[next]) {

    //                 cout << " -> Next accessible block: Block " << neighbor.first << " - Travel Time: " << neighbor.second << " min\n";

    //                 visited[next] = true; 

    //                 q.push(next); 
    //             }
    //         }
    //     }
    // }
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

    // cout << "DFS starting from vertex 0: \n"; 
    // vector<bool> visited(SIZE, false); 
    graph.DFSTrace(0); 

    // cout << endl; 

    // cout << "BFS starting from vertex 0: \n"; 
    graph.BFS(0);

    // cout << endl; 

    return 0;
}
