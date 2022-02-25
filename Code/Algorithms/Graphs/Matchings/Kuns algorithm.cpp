vector< vector<int> > graph;
vector<char> used;
vector<int> parent;

bool kun_dfs(int v)
{
    used[v] = 1;
    for (int to : graph[v])
    {
        if ((parent[to] == -1) || (!used[parent[to]] && kun(parent[to])))
        {
            parent[to] = v;
            return true;
        }
    }
    return false;
}

void kun()
{
    parent.assign(m, -1);
    for (int i = 0; i < n; ++i)
    {
        used.assign(n, 0);
        kun_dfs(i);
    }
}