void EdmondsKarp(int s, int t, int n, Graph& graph)
{
    vector< pair<int, int> > parent(n);
    queue<int> q;
    for (;;)
    {
        parent.assign(n, {-1, -1});
        q.push(s);
        parent[s] = {s, -1};
        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            for (int i = 0; i < len(graph[v]); ++i)
            {
                Edge& edge = graph[v][i];
                if ((parent[edge.to].first != -1) || (edge.capacity - edge.flow <= 0))
                {
                    continue;
                }
                q.push(edge.to);
                parent[edge.to] = {v, i};
            }
        }

        if (parent[t].first == -1)
        {
            return;
        }

        int min_flow = INF;
        int cur_v = t;
        while (cur_v != s)
        {
            Edge& edge = graph[parent[cur_v].first][parent[cur_v].second];
            min_flow = min(min_flow, edge.capacity - edge.flow);
            cur_v = parent[cur_v].first;
        }
        cur_v = t;
        while (cur_v != s)
        {
            Edge& edge = graph[parent[cur_v].first][parent[cur_v].second];
            edge.flow += min_flow;
            get_reversed_edge(edge, graph).flow -= min_flow;
            cur_v = parent[cur_v].first;
        }
    }
}