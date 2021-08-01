struct Edge
{
    int to;
    int weight;

    Edge() : Edge(-1, INF) {}
    Edge(int to, int weight) : to(to), weight(weight) {}
};

int prims_algorithm_n2(vector< vector<Edge> >& graph, int n, vector< pair<int, int> >& edges)
{
    vector<char> used(n);
    vector<int> min_edge(n, INF);
    vector<int> min_edge_dest(n, -1);
    min_edge[0] = 0;
    int weight_sum = 0;
    for (int i = 0; i < n; ++i)
    {
        int min_v = -1;
        for (int j = 0; j < n; ++j)
        {
            if (!used[j] && ((min_v == -1) || (min_edge[min_v] > min_edge[j])))
            {
                min_v = j;
            }
        }
        if (min_v == -1)
        {
            return -1;
        }
        weight_sum += min_edge[min_v];
        used[min_v] = 1;
        if (min_edge_dest[min_v] != -1)
        {
            edges.emplace_back(min_v, min_edge_dest[min_v]);
        }
        for (Edge &edge : graph[min_v])
        {
            if (min_edge[edge.to] > edge.weight)
            {
                min_edge[edge.to] = edge.weight;
                min_edge_dest[edge.to] = min_v;
            }
        }
    }
    return weight_sum;
}

int prims_algorithm_mlogn(vector< vector<Edge> >& graph, int n, vector< pair<int, int> >& edges)
{
    set< pair<int, int> > q;
    vector<int> min_edge(n, INF);
    vector<int> min_edge_dest(n, -1);
    vector<char> used(n);
    int weight_sum = 0;
    min_edge[0] = 0;
    q.insert({0, 0});
    for (int i = 0; i < n; ++i)
    {
        if (q.empty())
        {
            return -1;
        }
        auto [cur_min_edge, min_v] = *q.begin();
        q.erase(q.begin());
        used[min_v] = 1;
        weight_sum += cur_min_edge;
        if (min_edge_dest[min_v] != -1)
        {
            edges.emplace_back(min_v, min_edge_dest[min_v]);
        }
        for (Edge &edge : graph[min_v])
        {
            if (!used[edge.to] && (min_edge[edge.to] > edge.weight))
            {
                q.erase({min_edge[edge.to], edge.to});
                min_edge[edge.to] = edge.weight;
                min_edge_dest[edge.to] = min_v;
                q.insert({min_edge[edge.to], edge.to});
            }
        }
    }
    return weight_sum;
}