struct Edge
{
    int to;
    int capacity;
    int flow;
    int reversed_edge;
    int id;
    bool is_original;

    Edge() : Edge(-1, -INF, -INF, -1) {}
    Edge(int to, int capacity, int flow, int id, bool is_original = false) : to(to), capacity(capacity), flow(flow),
                                                                             id(id), is_original(is_original)
    {
        reversed_edge = -1;
    }
};

typedef vector< vector<Edge> > Graph;

void add_single_direction_edge(int from, int to, int capacity, int id, Graph& graph)
{
    graph[from].emplace_back(to, capacity, 0, id, true);
    graph[to].emplace_back(from, 0, 0, id);
    graph[from].back().reversed_edge = len(graph[to]) - 1;
    graph[to].back().reversed_edge = len(graph[from]) - 1;
}

void add_bidirectional_edge(int from, int to, int capacity, int id, Graph& graph)
{
    graph[from].emplace_back(to, capacity, 0, id, true);
    graph[to].emplace_back(from, capacity, 0, id);
    graph[from].back().reversed_edge = len(graph[to]) - 1;
    graph[to].back().reversed_edge = len(graph[from]) - 1;
}

Edge& get_reversed_edge(Edge& edge, Graph& graph)
{
    return graph[edge.to][edge.reversed_edge];
}

int get_flow(int s, int n, int m, Graph& graph, vector<int>& edges_flow)
{
    edges_flow.resize(m);
    for (int i = 0; i < n; ++i)
    {
        for (Edge& edge : graph[i])
        {
            if (edge.flow > 0)
            {
                edges_flow[edge.id] = edge.flow * (edge.is_original ? 1 : -1);
            }
        }
    }

    int flow = 0;
    for (Edge& edge : graph[s])
    {
        flow += edge.flow;
    }
    return flow;
}