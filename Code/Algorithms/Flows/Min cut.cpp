int get_min_cut(int s, int n, Graph& graph, vector<int>& edges)
{
    vector<char> used(n);
    queue<int> q;
    used[s] = 1;
    q.push(s);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (Edge& edge : graph[v])
        {
            if (used[edge.to] || (edge.flow == edge.capacity))
            {
                continue;
            }
            used[edge.to] = 1;
            q.push(edge.to);
        }
    }

    int cut_capacity = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!used[i])
        {
            continue;
        }
        for (Edge& edge : graph[i])
        {
            if (used[edge.to])
            {
                continue;
            }

            cut_capacity += edge.capacity;
            edges.push_back(edge.id);
        }
    }
    return cut_capacity;
}