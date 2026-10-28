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

void dijkstra(vector<vector<int>>& graph, vector<vector<int>>& distance_matrix, int start_node){
    vector<int> distance(graph.size(), INT_MAX);
    vector<bool> visited(graph.size(), false);
    distance[start_node] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, compareNode> q;   // Pqueue for candidate nodes: .first is node number, .second is cost to this node. 
    q.push({start_node, 0});
    while (!q.empty()){
        int curNode = q.top().first; 
        q.pop();
        if (visited[curNode]) continue;
        visited[curNode] = true;
        for (int i = 1; i < graph.size(); i++){
            if (!visited[i] && graph[curNode][i] > 0 && distance[curNode] != INT_MAX && distance[curNode] + graph[curNode][i] < distance[i]){
                distance[i] = (distance[curNode] + graph[curNode][i]);
                q.push({i, distance[i]});
            }
        }
    }
    distance_matrix[start_node] = distance;
}

int main(){
    int n, m; cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, -1));
    vector<vector<int>> distance_matrix(n + 1);
    for (int i = 0; i < m; i++){
        int u, v, w; cin >> u >> v >> w;
        graph[u][v] = w; 
    }

    for (int i = 1; i <= n; i++){
        dijkstra(graph, distance_matrix, i);
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            cout << distance_matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}