struct Edge
{
    int to;
    int id;

    Edge() : Edge(-1, -1) {}
    Edge(int to, int id) : to(to), id(id) {}
};

vector<int> bridges;
vector< vector<Edge> > graph;
vector<char> used;
vector<int> heights;
vector<int> min_heights;

void dfs(int v, int height, int p = -1)
{
    heights[v] = height;
    min_heights[v] = height;
    used[v] = 1;
    for (Edge& edge : graph[v])
    {
        if (edge.id == p)
        {
            continue;
        }
        if (!used[edge.to])
        {
            dfs(edge.to, height + 1, edge.id);
            if (min_heights[edge.to] > heights[v])
            {
                bridges.push_back(edge.id);
            }
            else
            {
                min_heights[v] = min(min_heights[v], min_heights[edge.to]);
            }
        }
        else
        {
            min_heights[v] = min(min_heights[v], heights[edge.to]);
        }
    }
}