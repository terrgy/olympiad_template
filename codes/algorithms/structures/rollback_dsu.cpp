/*#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize ("O3")*/

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <numeric>
#include <map>

#define ll long long
#define ld long double
#define accuracy(a) fixed << setprecision(a)

const int INF = (int)1e9;
const ll LINF = (ll)1e18;
const double EPS = 0.000000000000001;
const double PI = acos(-1.0);
const int MOD = 1e9 + 7;

using namespace std;

void fast_io()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void file_in(const string& filename)
{
    freopen(filename.c_str(), "r", stdin);
}

void file_out(const string& filename)
{
    freopen(filename.c_str(), "w", stdout);
}

double diffclock(clock_t clock1, clock_t clock2)
{
    double diffticks = clock2 - clock1;
    return diffticks / ((double)CLOCKS_PER_SEC / 1000);
}

void sleep(int milliseconds)
{
    clock_t start = clock();
    for (clock_t end = clock(); diffclock(start, end) < milliseconds; end = clock()) {}
}

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

struct Edge
{
    int from;
    int to;

    Edge() : Edge(-1, -1) {}
    Edge(int from, int to) : from(from), to(to) {}
};

vector<Edge> edges;
map< pair<int, int>, int> edge_assign;

void normalize_edge(int& u, int& v)
{
    if (u > v)
    {
        swap(u, v);
    }
    --u, --v;
}

int add_edge(int u, int v)
{
    if (edge_assign.count({u, v}))
    {
        return edge_assign[{u, v}];
    }
    edge_assign[{u, v}] = (int)edges.size();
    edges.emplace_back(u, v);
    return (int)edges.size() - 1;
}

const char TYPE_QUERY = 0;
const char TYPE_ADD = 1;
const char TYPE_REMOVE = 2;

struct Query
{
    char type;
    int id;

    Query() : Query(127, -1) {}
    Query(char type, int id) : type(type), id(id) {}
};

struct Node
{
    vector<int> edges;
    int queries;

    Node() = default;
    explicit Node(int queries) : queries(queries) {}
};

vector<Node> tree;

bool get_queries(Node& node)
{
    if (node.queries == -INF)
    {
        return false;
    }
    if (node.queries < 0)
    {
        return true;
    }
    return node.queries;
}

void merge(int p)
{
    tree[p].queries = get_queries(tree[2 * p + 1]) || get_queries(tree[2 * p + 2]);
}

void build(int p, int left, int right)
{
    if (right - left == 1)
    {
        tree[p].queries = -INF;
        return;
    }
    int mid = (left + right) / 2;
    build(2 * p + 1, left, mid);
    build(2 * p + 2, mid, right);
    merge(p);
}

void add_query(int p, int left, int right, int index, int id)
{
    if (right - left == 1)
    {
        tree[p].queries = -(id + 1);
        return;
    }
    int mid = (left + right) / 2;
    if (index < mid)
    {
        add_query(2 * p + 1, left, mid, index, id);
    }
    else
    {
        add_query(2 * p + 2, mid, right, index, id);
    }
    merge(p);
}

void add_segment(int p, int left, int right, int t_left, int t_right, int id)
{
    if ((right <= t_left) || (t_right <= left))
    {
        return;
    }
    if ((t_left <= left) && (right <= t_right))
    {
        tree[p].edges.push_back(id);
        return;
    }
    int mid = (left + right) / 2;
    add_segment(2 * p + 1, left, mid, t_left, t_right, id);
    add_segment(2 * p + 2, mid, right, t_left, t_right, id);
}

DSU dsu;
vector<int> answers;

void descent(int p, int left, int right)
{
    if (!get_queries(tree[p]))
    {
        return;
    }
    for (int edge_id : tree[p].edges)
    {
        dsu.unite(edges[edge_id].from, edges[edge_id].to);
    }

    if (right - left == 1)
    {
        int query_id = -(tree[p].queries + 1);
        answers[query_id] = dsu.components_count;
        for (int i = 0; i < tree[p].edges.size(); ++i)
        {
            dsu.rollback();
        }
        return;
    }
    int mid = (left + right) / 2;
    descent(2 * p + 1, left, mid);
    descent(2 * p + 2, mid, right);
    for (int i = 0; i < tree[p].edges.size(); ++i)
    {
        dsu.rollback();
    }
}


void solve()
{
    int n, k;
    cin >> n >> k;
    if (!k)
    {
        return;
    }
    vector<Query> queries(k);

    int query_count = 0;
    for (int i = 0; i < k; ++i)
    {
        char operation;
        cin >> operation;
        if (operation == '?')
        {
            queries[i] = Query(TYPE_QUERY, query_count++);
            continue;
        }

        int u, v, edge_id;
        cin >> u >> v;

        normalize_edge(u, v);
        edge_id = add_edge(u, v);
        queries[i] = Query(operation == '+' ? TYPE_ADD : TYPE_REMOVE, edge_id);
    }
    answers.resize(query_count);

    tree.resize(4 * k);
    build(0, 0, k);

    vector<int> last_alive(edges.size(), k);
    for (int i = k - 1; i > -1; --i)
    {
        if (queries[i].type == TYPE_QUERY)
        {
            add_query(0, 0, k, i, queries[i].id);
            continue;
        }
        if (queries[i].type == TYPE_REMOVE)
        {
            last_alive[queries[i].id] = i;
        }
        else
        {
            add_segment(0, 0, k, i, last_alive[queries[i].id], queries[i].id);
        }
    }

    dsu.prepare(n);
    descent(0, 0, k);

    for (int i : answers)
    {
        cout << i << '\n';
    }
}

signed main()
{
#ifndef LOCAL
    fast_io();
#else
    file_in("input.txt");
    file_out("output.txt");
    clock_t start = clock();
#endif

    solve();

#ifdef LOCAL
    cerr << "TIME = " << (clock() - start) / ((double)CLOCKS_PER_SEC / 1000) << '\n';
#endif

    return 0;
}