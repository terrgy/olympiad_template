struct DinicAlgorithm {

    FlowNetwork& network;
    queue<int> q;
    vector<int> height;
    vector<int> inds;

    explicit DinicAlgorithm(FlowNetwork& network) : network(network) {};

    int get_max_flow() {
        int flow = 0;

        for (;;) {
            if (!bfs()) {
                break;
            }
            inds.assign(network.size(), 0);
            while (int pushed = dfs(network.s, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

    bool bfs() {
        height.assign(network.size(), -1);
        q.push(network.s);
        height[network.s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto& edge : network[v]) {
                if ((height[edge.to] != -1) || edge.remain() <= 0) {
                    continue;
                }
                height[edge.to] = height[v] + 1;
                q.push(edge.to);
            }
        }
        return height[network.t] != -1;
    }

    int dfs(int v, int flow) {
        if (!flow || (v == network.t)) {
            return flow;
        }
        for (; inds[v] < network[v].size(); ++inds[v])
        {
            auto& edge = network[v][inds[v]];
            if (height[edge.to] != height[v] + 1)
            {
                continue;
            }
            int pushed = dfs(edge.to, min(flow, edge.remain()));
            if (pushed)
            {
                network.fill_edge(edge, pushed);
                return pushed;
            }
        }
        return 0;
    }
};