#include <bits/stdc++.h>
#define array vector
#define umap unordered_map
#define endl '\n'
using namespace std;

// @author: Thawan Ribeiro, 2024-07-14
// @algorithm: Dijkstra for Competitive Programming
// @url: https://github.com/thawan-xyz

struct edge {
    int origin;
    int destination;
    int weight;

    bool operator < (const edge& other) const {
        return weight > other.weight;
    }
};

class Graph {
private:
    const int VERTICES; int edges;
    array<umap<int, int>> adjacency; array<bool> marked;

    bool is_marked(int x) const {
        return marked[x];
    }

    void set_mark(int x, bool m = true) {
        marked[x] = m;
    }

public:
    Graph(const int N) : VERTICES(N), edges(0), adjacency(N), marked(N) {}

    ~Graph() = default;

    bool has_edge(int x, int y) const {
        return adjacency[x].count(y);
    }

    void set_edge(int x, int y, int w) {
        if (!has_edge(x, y)) edges++;

        adjacency[x][y] = w;
    }

    void del_edge(int x, int y) {
        if (has_edge(x, y)) edges--;

        adjacency[x].erase(y);
    }

    int get_weight(int x, int y) const {
        if (!has_edge(x, y)) return 0;

        return adjacency[x].at(y);
    }

    int num_vertices() const {
        return VERTICES;
    }

    int num_edges() const {
        return edges;
    }

    pair<array<int>, array<int>> dijkstra(int x) {
        array<int> predecessor(VERTICES, -1), distance(VERTICES, INT_MAX);
        marked.assign(VERTICES, false);

        priority_queue<edge> edge_priority;
        edge_priority.push({x, x, 0});

        predecessor[x] = x, distance[x] = 0;
        for (int i = 0; i < VERTICES - 1; ++i) {
            do {
                if (edge_priority.empty()) goto end;

                x = edge_priority.top().destination, edge_priority.pop();
            } while (is_marked(x)); set_mark(x);

            for (auto [y, w] : adjacency[x]) {
                if (!is_marked(y) && distance[x] + w < distance[y]) {
                    predecessor[y] = x, distance[y] = distance[x] + w;

                    edge_priority.push({x, y, distance[y]});
                }
            }
        }
        end: return {predecessor, distance};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cerr << "Thawan";
    return 0;
}
