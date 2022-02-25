struct FenwickTree
{
    int size;
    vector<ll> tree;
    vector<ll>* data;

    explicit FenwickTree(int size) : size(size)
    {
        tree.resize(size);
    }

    explicit FenwickTree(vector<ll>& data) : size(len(data)), data(&data)
    {
        tree.resize(size);
        build();
    }

    void build()
    {
        for (int i = 0; i < size; ++i)
        {
            add(i, (*data)[i]);
        }
    }

    ll get(int right)
    {
        ll res = 0;
        for (; right >= 0; right = (right & (right + 1)) - 1)
        {
            res += tree[right];
        }
        return res;
    }

    ll get(int left, int right)
    {
        return get(right) - (left ? get(left - 1) : 0);
    }

    void add(int pos, ll value)
    {
        for (; pos < size; pos = (pos | (pos + 1)))
        {
            tree[pos] += value;
        }
    }
};
