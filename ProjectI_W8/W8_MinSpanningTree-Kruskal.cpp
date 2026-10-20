#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge{
    int src;
    int dest;
    int weight;
    Edge(int s, int d, int w): src(s), dest(d), weight(w){}
};

int n, m;
vector<Edge> edges;
vector<int> parent;

int findRoot(int u){
    if (parent[u] == u) return u;
    return parent[u] = findRoot(parent[u]);
}

bool unite(int u, int v){
    int root_u = findRoot(u);
    int root_v = findRoot(v);

    if (root_u == root_v) return false;

    parent[root_v] = root_u;
    return true;
}

void kruskal(){
    long long total_weight = 0;
    int edges_count = 0;

    for (const auto& edge : edges){
        if (unite(edge.src, edge.dest)){
            total_weight += edge.weight;
            edges_count += 1;
            if (edges_count == n - 1) break;
        }
    }
    cout << total_weight << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    parent = vector<int>(n + 1);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++){
        int s, d, w;
        cin >> s >> d >> w;
        edges.emplace_back(s, d, w);
    }

    sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2){
        return e1.weight < e2.weight;
    });

    kruskal();
    return 0;
}
