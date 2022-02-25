struct LCA_RMQ
{
    int root;
    int size;
    int order_size;
    vector< vector<int> >& graph;
    vector<int> order;
    vector<int> first_pos;
    vector<int> depths;

    vector<int> seg_tree;
    int seg_left;
    int seg_right;

    explicit LCA_RMQ(vector< vector<int> >& graph, int root = 0) : graph(graph)
    {
        this->root = root;
        size = (int)graph.size();
        first_pos.resize(size);
        depths.resize(size);
        order.reserve(2 * size);
        dfs(root, 0);
        order_size = (int)order.size();
        seg_tree.resize(4 * (order_size));
        build(0, 0, order_size);
        seg_left = seg_right = -1;
    }

    int vertex_min(int u, int v)
    {
        if ((u == INF) || (v == INF))
        {
            return u == INF ? v : u;
        }
        if (depths[u] < depths[v])
        {
            return u;
        }
        return v;
    }

    void build(int p, int left, int right)
    {
        if (right - left == 1)
        {
            seg_tree[p] = order[left];
            return;
        }
        int mid = (left + right) / 2;
        build(2 * p + 1, left, mid);
        build(2 * p + 2, mid, right);
        seg_tree[p] = vertex_min(seg_tree[2 * p + 1], seg_tree[2 * p + 2]);
    }

    int get_min(int p, int left, int right)
    {
        if ((right <= seg_left) || (seg_right <= left))
        {
            return INF;
        }
        if ((seg_left <= left) && (right <= seg_right))
        {
            return seg_tree[p];
        }
        int mid = (left + right) / 2;
        return vertex_min(get_min(2 * p + 1, left, mid), get_min(2 * p + 2, mid, right));
    }

    void dfs(int v, int depth, int p = -1)
    {
        depths[v] = depth;
        first_pos[v] = (int)order.size();
        order.push_back(v);
        for (int to : graph[v])
        {
            if (to == p)
            {
                continue;
            }
            dfs(to, depth + 1, v);
            order.push_back(v);
        }
    }

    int get(int u, int v)
    {
        seg_left = first_pos[u];
        seg_right = first_pos[v];
        if (seg_left > seg_right)
        {
            swap(seg_left, seg_right);
        }
        ++seg_right;
        return get_min(0, 0, order_size);
    }
};