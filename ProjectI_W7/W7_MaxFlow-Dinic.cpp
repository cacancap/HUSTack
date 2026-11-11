#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <climits>
using namespace std;

struct Edge{
    int dest;  // Dest node of edge
    int capacity;  
    int flow;
    int rev;    // Index of the backward edge in the adj[dest]
    Edge(int v, int cap, int r): dest(v), capacity(cap), flow(0), rev(r){}
    Edge(int v, int cap, int fl, int r): dest(v), capacity(cap), flow(fl), rev(r){}
};

vector<vector<Edge>> adj;
vector<int> level;
vector<int> ptr;

void add_edge(int source, int dest, int capacity){
    int idx_src = adj[source].size();
    int idx_dst = adj[dest].size();
    adj[source].push_back(Edge(dest, capacity, idx_dst));
    adj[dest].push_back(Edge(source, 0, 0, idx_src));
}


bool BFS(int source, int dest){
    fill(level.begin(), level.end(), -1); level[source] = 0;
    queue<int> q;
    q.push(source);
    vector<bool> visited (adj.size());
    visited[source] = true;
    while (!q.empty()){
        int curHop = q.front();
        q.pop();
        if (curHop == dest){
            return true;
        }

        for (Edge edge : adj[curHop]){
            if (!visited[edge.dest] && edge.capacity - edge.flow > 0){
                visited[edge.dest] = true;
                level[edge.dest] = level[curHop] + 1;
                q.push(edge.dest);
            }
        }
    }
    return false;
}

long long DFS(int u, int dest, long long pushed){
    if (pushed == 0) return 0;
    if (u == dest) return pushed;

    for (int& cid = ptr[u]; cid < adj[u].size(); cid++){
        Edge& edge = adj[u][cid];
        int nextHop = edge.dest;
        int remaining_cap = edge.capacity - edge.flow;
        
        if (level[nextHop] != level[u] + 1 || remaining_cap <= 0){
            continue;
        }

        long long tr = DFS(nextHop, dest, min(pushed, (long long)(edge.capacity - edge.flow)));
        if (tr == 0) continue;
        // Update flow
        edge.flow += tr;
        adj[nextHop][edge.rev].flow -= tr;
        return tr;
    }
    return 0;
}

int dinic(int source, int dest){
    int total_flow = 0;
    while (true){
        bool exist_path = BFS(source, dest);
        if (!exist_path) break;
        // Reset ptr
        fill(ptr.begin(), ptr.end(), 0);
        // Trying to push new flow (DFS)
        while (long long pushed = DFS(source, dest, INT_MAX)){
            total_flow += pushed;
        }
    }
    return total_flow;
}

void print_edge(int N){
    for (int i = 1; i <= N; i++){
        cout << "src " << i << ": ";
        for (int j = 0; j < adj[i].size(); j++){
            cout << " -> " << adj[i][j].dest << " (" << adj[i][j].capacity << ")" << " | "; 
        }
        cout << endl;
    }
}

void print_level_graph(int N){
    for (int i = 1; i <= N; i++){
        cout << level[i] << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int N, M; cin >> N >> M;
    int source, dest; cin >> source >> dest;
    adj = vector<vector<Edge>> (N + 1);
    level = vector<int> (N + 1, -1);
    level[source] = 0;
    ptr = vector<int> (N + 1, 0);
    for (int i = 0; i < M; i++){
        int u, v, cap;
        cin >> u >> v >> cap;
        add_edge(u, v, cap);
    }

    cout << dinic(source, dest) << endl;

    return 0;
}