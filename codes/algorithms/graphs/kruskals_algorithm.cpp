struct DSU
{
    vector<int> parent;
    vector<int> rank;

    explicit DSU(int size = 0)
    {
        resize(size);
    }

    void resize(int size = 0)
    {
        if (size)
        {
            parent.resize(size);
            rank.assign(size, 0);
        }
        iota(parent.begin(), parent.end(), 0);
    }

    int get(int u)
    {
        if (parent[u] == u)
        {
            return u;
        }
        return parent[u] = get(parent[u]);
    }

    void unite(int u, int v)
    {
        u = get(u);
        v = get(v);
        if (u == v)
        {
            return;
        }
        if (rank[u] > rank[v])
        {
            swap(u, v);
        }
        if (rank[u] == rank[v])
        {
            ++rank[v];
        }
        parent[u] = v;
    }

    bool check(int u, int v)
    {
        return get(u) == get(v);
    }
};

struct Edge
{
    int from;
    int to;
    int weight;

    Edge() : Edge(-1, -1, INF) {}
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
};

int kruskals_algorithm(vector<Edge>& edges_list, int n, vector< pair<int, int> >& edges)
{
    auto comp = [](const Edge& a, const Edge& b)
    {
        return a.weight < b.weight;
    };
    sort(edges_list.begin(), edges_list.end(), comp);
    DSU dsu(n);
    int weight_sum = 0;
    for (Edge& edge : edges_list)
    {
        if (dsu.check(edge.from, edge.to))
        {
            continue;
        }
        weight_sum += edge.weight;
        edges.emplace_back(edge.from, edge.to);
        dsu.unite(edge.from, edge.to);
    }
    return weight_sum;
}