struct DSU
{
    struct HistoryNode
    {
        int changed_v;
        int previous_value;
        int increased_rank_v;

        HistoryNode() : HistoryNode(-1, -1, -1) {}
        HistoryNode(int changed_v, int previous_value, int increased_rank_v) :
                changed_v(changed_v), previous_value(previous_value), increased_rank_v(increased_rank_v) {}
    };

    vector<int> parent;
    vector<int> rank;
    vector<HistoryNode> history;
    int components_count;

    DSU() = default;
    explicit DSU(int size)
    {
        components_count = -1;
        prepare(size);
    }

    void prepare(int size)
    {
        components_count = size;
        parent.resize(size);
        iota(parent.begin(), parent.end(), 0);
        rank.assign(size, 0);
    }

    int get(int u)
    {
        if (u == parent[u])
        {
            return u;
        }
        return get(parent[u]);
    }

    void unite(int u, int v)
    {
        u = get(u);
        v = get(v);
        if (u == v)
        {
            history.emplace_back();
            return;
        }
        HistoryNode new_history;
        --components_count;

        if (rank[u] > rank[v])
        {
            swap(u, v);
        }
        if (rank[u] == rank[v])
        {
            new_history.increased_rank_v = v;
            ++rank[v];
        }
        new_history.changed_v = u;
        new_history.previous_value = parent[u];
        history.push_back(new_history);
        parent[u] = v;
    }

    void rollback()
    {
        if (history.empty())
        {
            return;
        }
        HistoryNode last_history = history.back();
        history.pop_back();

        if (last_history.changed_v == -1)
        {
            return;
        }

        if (last_history.increased_rank_v != -1)
        {
            --rank[last_history.increased_rank_v];
        }
        parent[last_history.changed_v] = last_history.previous_value;
        ++components_count;
    }
};