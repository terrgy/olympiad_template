struct FlowNetwork {
    struct Edge {
        int to;
        int capacity;
        int flow;
        int reversed_edge;

        Edge() : Edge(-1, 0, 0, -1) {}
        Edge(int to, int capacity, int flow, int reversed_edge) : to(to), capacity(capacity), flow(flow), reversed_edge(reversed_edge) {}
        Edge(int to, int capacity, int reversed_edge) : Edge(to, capacity, 0, reversed_edge) {}
        Edge(int to, int capacity) : Edge(to, capacity, -1) {};

        int remain() {
            return capacity - flow;
        }
    };

    int s, t;
    vector< vector<Edge> > e;

    FlowNetwork(int n, int s, int t) : e(n), s(s), t(t) {}
    explicit FlowNetwork(int n) : FlowNetwork(n, -1, -1) {};

    vector<Edge>& operator[](size_t idx) {
        return e[idx];
    }

    int add_edge(int u, int v, int capacity) {
        int idx_straight, idx_reversed;
        idx_straight = (int)e[u].size();
        idx_reversed = (int)e[v].size();
        e[u].emplace_back(v, capacity, idx_reversed);
        e[v].emplace_back(u, 0, idx_straight);
        return idx_straight;
    }

    int add_bi_edge(int u, int v, int capacity) {
        int idx_straight, idx_reversed;
        idx_straight = (int)e[u].size();
        idx_reversed = (int)e[v].size();
        e[u].emplace_back(v, capacity, idx_reversed);
        e[v].emplace_back(u, capacity, idx_straight);
        return idx_straight;
    }

    Edge& get_reversed_edge(Edge& edge) {
        return e[edge.to][edge.reversed_edge];
    }

    void fill_edge(Edge& edge, int flow) {
        edge.flow += flow;
        get_reversed_edge(edge).flow -= flow;
    }

    size_t size() const {
        return e.size();
    }

    int get_flow() const {
        int flow = 0;
        for (auto& edge : e[s]) {
            flow += edge.flow;
        }
        return flow;
    }
};