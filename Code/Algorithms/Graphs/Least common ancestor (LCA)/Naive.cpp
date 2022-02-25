struct SlowLCA
{
    int root;
    int size;
    vector< vector<int> >& graph;
    vector<int> parents;

    explicit SlowLCA(vector< vector<int> >& graph, int root = 0) : graph(graph)
    {
        this->root = root;
        size = (int)graph.size();
        parents.resize(size);
        dfs(root);
    }

    void dfs(int v, int p = -1)
    {
        parents[v] = p;
        for (int to : graph[v])
        {
            if (to == p)
            {
                continue;
            }
            dfs(to, v);
        }
    }

    int get(int u, int v)
    {
        set<int> first_parents;
        while (u != root)
        {
            first_parents.insert(u);
            u = parents[u];
        }
        while (v != root)
        {
            if (first_parents.count(v))
            {
                return v;
            }
            v = parents[v];
        }
        return root;
    }
};