#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

class Dinic {
    struct Edge {
        int to;
        long long capacity;
    };

    std::vector<std::vector<int>> adjacency;
    std::vector<Edge> edges;
    std::vector<int> level;
    std::vector<int> nextEdge;

    bool buildLevels(int source, int target) {
        std::fill(level.begin(), level.end(), -1);
        std::queue<int> pending;
        level[source] = 0;
        pending.push(source);

        while (!pending.empty()) {
            int node = pending.front();
            pending.pop();
            for (int id : adjacency[node]) {
                const Edge& edge = edges[id];
                if (edge.capacity > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[node] + 1;
                    pending.push(edge.to);
                }
            }
        }
        return level[target] != -1;
    }

    long long sendFlow(int node, int target, long long limit) {
        if (node == target) return limit;

        for (int& i = nextEdge[node]; i < static_cast<int>(adjacency[node].size()); ++i) {
            int id = adjacency[node][i];
            Edge& edge = edges[id];
            if (edge.capacity == 0 || level[edge.to] != level[node] + 1) continue;

            long long pushed = sendFlow(edge.to, target, std::min(limit, edge.capacity));
            if (pushed > 0) {
                edge.capacity -= pushed;
                edges[id ^ 1].capacity += pushed;
                return pushed;
            }
        }
        return 0;
    }

public:
    Dinic(int nodes, int arcCount)
        : adjacency(nodes + 1), level(nodes + 1), nextEdge(nodes + 1) {
        edges.reserve(2 * arcCount);
    }

    void addArc(int from, int to, long long capacity) {
        // Each arc and its reverse occupy consecutive positions.
        int id = static_cast<int>(edges.size());
        adjacency[from].push_back(id);
        adjacency[to].push_back(id + 1);
        edges.push_back({to, capacity});
        edges.push_back({from, 0});
    }

    long long maxFlow(int source, int target) {
        if (source == target) return 0;

        long long total = 0;
        while (buildLevels(source, target)) {
            std::fill(nextEdge.begin(), nextEdge.end(), 0);
            while (long long pushed = sendFlow(source, target, std::numeric_limits<long long>::max())) {
                total += pushed;
            }
        }
        return total;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nodes, arcCount, source, target;
    if (!(std::cin >> nodes >> arcCount >> source >> target)) return 0;

    Dinic network(nodes, arcCount);
    for (int i = 0; i < arcCount; ++i) {
        int from, to;
        long long capacity;
        std::cin >> from >> to >> capacity;
        network.addArc(from, to, capacity);
    }
    std::cout << network.maxFlow(source, target) << '\n';
}
