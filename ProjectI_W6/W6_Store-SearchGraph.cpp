#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

struct Graph {
    int n, m;
    vector<int> deg;
    vector<vector<bool>> adj_mat;      // Ma trận kề để kiểm tra cạnh trong O(1) lúc Backtrack
    vector<vector<int>> node_color;    // Nhãn màu Tầng 2 của từng đỉnh: [deg(u), sorted(deg(v))]
    vector<vector<int>> signature;     // Chữ ký toàn đồ thị (đã sắp xếp node_color của mọi đỉnh)
};

// Hàm đọc 1 đồ thị và tính luôn Chữ ký (Tầng 1 + Tầng 2)
Graph readGraph() {
    Graph G;
    cin >> G.n >> G.m;
    G.deg.assign(G.n + 1, 0);
    G.adj_mat.assign(G.n + 1, vector<bool>(G.n + 1, false));
    vector<vector<int>> adj_list(G.n + 1);

    for (int i = 0; i < G.m; ++i) {
        int u, v;
        cin >> u >> v;
        if (!G.adj_mat[u][v]) {
            G.adj_mat[u][v] = G.adj_mat[v][u] = true;
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
            G.deg[u]++;
            G.deg[v]++;
        }
    }

    // Tính màu Tầng 2 cho từng đỉnh: [bậc của u, dãy bậc láng giềng tăng dần]
    G.node_color.resize(G.n + 1);
    for (int u = 1; u <= G.n; ++u) {
        vector<int> neighbor_degs;
        for (int v : adj_list[u]) {
            neighbor_degs.push_back(G.deg[v]);
        }
        sort(neighbor_degs.begin(), neighbor_degs.end());

        G.node_color[u].push_back(G.deg[u]);
        for (int d : neighbor_degs) {
            G.node_color[u].push_back(d);
        }
        G.signature.push_back(G.node_color[u]);
    }

    // Sắp xếp danh sách màu để tạo Phân phối màu (Chữ ký đồ thị)
    sort(G.signature.begin(), G.signature.end());
    return G;
}

// Tầng 3: Quay lui kiểm tra song ánh f: H -> G
bool backtrack(int u, const Graph& H, const Graph& G, vector<int>& f, vector<bool>& used) {
    if (u > H.n) return true; // Đã gán thành công hết các đỉnh

    for (int v = 1; v <= G.n; ++v) {
        // Chỉ thử gán u -> v nếu v chưa dùng và có cùng nhãn màu láng giềng
        if (!used[v] && H.node_color[u] == G.node_color[v]) {
            bool ok = true;
            for (int prev = 1; prev < u; ++prev) {
                if (H.adj_mat[u][prev] != G.adj_mat[v][f[prev]]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                used[v] = true;
                f[u] = v;
                if (backtrack(u + 1, H, G, f, used)) return true;
                used[v] = false;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    // Lưu các đồ thị trong kho, phân nhóm theo Chữ ký (Signature)
    map<pair<pair<int, int>, vector<vector<int>>>, vector<Graph>> database;

    for (int i = 0; i < N; ++i) {
        Graph G = readGraph();
        database[{{G.n, G.m}, G.signature}].push_back(G);
    }

    string delimiter;
    cin >> delimiter; // Đọc dấu '#'

    int K;
    if (!(cin >> K)) return 0;

    for (int k = 0; k < K; ++k) {
        Graph H = readGraph();
        auto key = make_pair(make_pair(H.n, H.m), H.signature);

        bool found = false;
        // Chỉ lấy các đồ thị có cùng chữ ký (cùng phân phối màu) ra để kiểm tra
        if (database.count(key)) {
            for (const Graph& G : database[key]) {
                vector<int> f(H.n + 1, 0);
                vector<bool> used(G.n + 1, false);
                if (backtrack(1, H, G, f, used)) {
                    found = true;
                    break;
                }
            }
        }
        cout << (found ? 1 : 0) << "\n";
    }
    return 0;
}