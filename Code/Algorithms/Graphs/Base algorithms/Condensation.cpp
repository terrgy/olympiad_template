vector< vector<int> > graph;
vector< vector<int> > tgraph;
vector<char> used;
vector<int> topsort;
vector<int> comps;

void add_edge(int from, int to)
{
    graph[from].push_back(to);
    tgraph[to].push_back(from);
}

void dfs_topsort(int v)
{
    used[v] = 1;
    for (int to : graph[v])
    {
        if (used[to])
        {
            continue;
        }
        dfs_topsort(to);
    }
    topsort.push_back(v);
}

void dfs_comp(int v)
{
    used[v] = 1;
    for (int to : tgraph[v])
    {
        if (used[to])
        {
            continue;
        }
        comps[to] = comps[v];
        dfs_comp(to);
    }
}

void condensation()
{
    for (int i = 0; i < len(graph); ++i)
    {
        if (!used[i])
        {
            dfs_topsort(i);
        }
    }

    reverse(topsort.begin(), topsort.end());
    used.assign(len(graph), 0);
    int last_comp = 0;
    for (int i = 0; i < len(graph); ++i)
    {
        int v = topsort[i];
        if (!used[v])
        {
            comps[v] = last_comp++;
            dfs_comp(v);
        }
    }
}