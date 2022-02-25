struct pair_hash
{
    inline size_t operator()(const pair<int, int>& p) const
    {
        return p.first * 31 + p.second;
    }
};

unordered_set< pair<int, int>, pair_hash > st;