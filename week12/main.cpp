#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge{
    int destination;
    int weight;
};

vector<int> dijkstra(const vector<vector<Edge>>& graph, int source){
    int numVertices = graph.size();

    vector<int> distances(numVertices, numeric_limits<int>::max());
    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, source));

    while (!pq.empty()){
        int currentVertex = pq.top().second;
        int currentDistance =pq.top().first;
        pq.pop();

        if (currentDistance>distances[currentVertex])
            continue;

        for (const Edge& edge:graph[currentVertex]){
            int neighbor = edge.destination;
            int weight = edge.weight;
            int distance = distances[currentVertex]+weight;

            if (distance<distances[neighbor]){
                distances[neighbor] =distance;
                pq.push(make_pair(distance,neighbor));
            }
        }
    }

    return distances;
}

int main(){
    int numVertices =6;
    vector<vector<Edge>> graph(numVertices);

    // Adding edges to the graph
    graph[0].push_back({1, 10});
    graph[1].push_back({0, 10});
    graph[0].push_back({4, 15});
    graph[4].push_back({0, 15});
    graph[0].push_back({5, 5});
    graph[5].push_back({0, 5});
    graph[1].push_back({2, 10});
    graph[2].push_back({1, 10});
    graph[1].push_back({3, 30});
    graph[3].push_back({1, 30});
    graph[2].push_back({3, 12});
    graph[3].push_back({2, 12});
    graph[2].push_back({4, 5});
    graph[4].push_back({2, 5});
    graph[5].push_back({3, 20});
    graph[3].push_back({5, 20});

    int source =5;
    vector<int> distances = dijkstra(graph,source);

    cout<<"Shortest distances from vertex "<<source<<":\n";
    for (int i=0; i<numVertices;++i){
        cout<<"Vertex " <<i<<": "<<distances[i]<<endl;
    }

    return 0;
}
