#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct compareNode{
    bool operator() (const pair<int, int>& node1, const pair<int, int>& node2){
        return node1.second > node2.second;
    }
};

vector<int> dijkstra(vector<vector<pair<int, int>>>& adj, int start_node){
    vector<int> distance(adj.size(), INT_MAX);
    vector<bool> visited(adj.size(), false);
    distance[start_node] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, compareNode> q;   // Pqueue for candidate nodes: .first is node number, .second is cost to this node. 
    q.push({start_node, 0});
    while (!q.empty()){
        int curNode = q.top().first; 
        q.pop();
        if (visited[curNode]) continue;
        visited[curNode] = true;

        for (auto& edge : adj[curNode]){
            int neighbor = edge.first;
            int weight = edge.second;
            
            if (!visited[neighbor] && distance[curNode] + weight < distance[neighbor]){
                distance[neighbor] = distance[curNode] + weight;
                q.push({neighbor, distance[neighbor]});
            }
        }
    }
    return distance;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++){
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    int node1, node2; cin >> node1 >> node2;
    vector<int> distance = dijkstra(adj, node1);

    if (distance[node2] == INT_MAX){
        cout << "-1" << endl;
        
    } else {
        cout << distance[node2] << endl;
    }
    
    return 0;
}