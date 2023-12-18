struct EdmondsKarpAlgorithm {
    FlowNetwork& network;

    explicit EdmondsKarpAlgorithm(FlowNetwork& network) : network(network) {}

    void algo() {
        vector< pair<int, int> > parent;
        queue<int> q;
        for (;;) {
            parent.assign(network.size(), {-1, -1});
            q.push(network.s);
            while (!q.empty()) {
                int v = q.front();
                q.pop();

                for (int i = 0; i < len(network[v]); ++i) {
                    auto& edge = network[v][i];
                    if ((parent[edge.to].first != -1) || (edge.remain() <= 0)) {
                        continue;
                    }
                    q.push(edge.to);
                    parent[edge.to] = {v, i};
                }
            }

            if (parent[network.t].first == -1) {
                return;
            }

            int push_flow = INF;
            int v = network.t;
            while (v != network.s) {
                auto& edge = network[parent[v].first][parent[v].second];
                push_flow = min(push_flow, edge.remain());
                v = parent[v].first;
            }
            v = network.t;
            while (v != network.s) {
                network.fill_edge(network[parent[v].first][parent[v].second], push_flow);
                v = parent[v].first;
            }
        }
    }

    int get_max_flow() {
        algo();
        return network.get_flow();
    }
};