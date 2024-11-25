#include <iostream>
#include <deque>
#include <queue>
#include <vector>
using namespace std;

const int SIZE = 7;

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
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }


    void DFS(int s, vector<bool> &visited) {

        cout << s << " "; 

        visited[s] = true; 

        for (auto &neighbor : adjList[s]) {

            int n = neighbor.first; 

            if (!visited[n]) {

                DFS(n, visited); 
            }
        }
    }

    void BFS(int s) {

        vector<bool> visited(SIZE, false); 

        queue<int> q; 

        visited[s] = true; 

        q.push(s); 

        while (!q.empty()) {

            int n = q.front(); 

            q.pop(); 

            cout << n << " "; 

            for (auto &neighbor : adjList[n]) {

                int next = neighbor.first; 

                if (!visited[next]) {

                    visited[next] = true; 

                    q.push(next); 
                }
            }
        }
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,8},{0,2,21},{1,2,6},{1,3,5},{1,4,4},{2,7,11},{2,8,8},{3,4,9}, {5,6,10}, {5,7,15}, {5,8,5}, {6,7,3}, {6,8,7}, {7,8,8}, {7,9,5}, {9,10,7}, {9,11,3}, {10,12,4}, {11,12,6}; 
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    cout << "DFS starting from vertex 0: \n"; 
    vector<bool> visited(SIZE, false); 
    graph.DFS(0, visited); 

    cout << endl; 

    cout << "BFS starting from vertex 0: \n"; 
    graph.BFS(0);

    cout << endl; 

    return 0;
}
