vector<int> art_points;
vector< vector<int> > graph;
vector<char> used;
vector<int> heights;
vector<int> min_heights;

void dfs(int v, int height, int p = -1)
{
    heights[v] = height;
    min_heights[v] = height;
    used[v] = 1;
    int launches = 0;
    bool is_point = false;
    for (int to : graph[v])
    {
        if (to == p)
        {
            continue;
        }
        if (!used[to])
        {
            ++launches;
            dfs(to, height + 1, v);
            if (min_heights[to] >= heights[v])
            {
                is_point = true;
            }
            else
            {
                min_heights[v] = min(min_heights[v], min_heights[to]);
            }
        }
        else
        {
            min_heights[v] = min(min_heights[v], heights[to]);
        }
    }
    if (p == -1)
    {
        is_point = launches > 1;
    }
    if (is_point)
    {
        art_points.push_back(v);
    }
}