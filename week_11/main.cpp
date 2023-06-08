#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure for the edges of the graph
struct Edge {
    int src, dest, weight;
};

void addEdge(vector<vector<pair<int, int>>>& graph, int src, int dest, int weight) {
    graph[src].push_back(make_pair(dest, weight));
    graph[dest].push_back(make_pair(src, weight));
}

// Find the MST using Prim's algorithm
vector<Edge> primMST(const vector<vector<pair<int, int>>>& graph, int V, int n){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);
    vector<Edge> mstEdges;

    int src = n;
    pq.push(make_pair(n, src));
    key[src] = n;

    while (!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;

        for (const auto& neighbor:graph[u]){
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!inMST[v] && weight<key[v]){
                key[v] = weight;
                pq.push(make_pair(key[v],v));
                parent[v] =u;
            }
        }
    }

    // Construct the MST of the grp
    for (int i=1; i<V;++i){
        mstEdges.push_back({parent[i],i,key[i]});
    }

    return mstEdges;
}

void printMST(const vector<Edge>& mstEdges){
    cout << "Minimum Spanning Tree:\n";
    for (const auto& edge : mstEdges){
        cout << edge.src << " -- " << edge.dest << " \tWeight: " << edge.weight << endl;
    }
}

int main(){
    int V =6;
    vector<vector<pair<int, int>>> graph(V);

    addEdge(graph, 0, 1, 3);
    addEdge(graph, 0, 5, 1);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 1, 4, 10);
    addEdge(graph, 2, 3, 3);
    addEdge(graph, 2, 5, 5);
    addEdge(graph, 3, 4, 5);
    addEdge(graph, 4, 5, 4);

    vector<Edge> mstEdges = primMST(graph, V, 0);

    printMST(mstEdges);

    return 0;
}
