void build_logs(vector<int>& logs, int n)
{
    logs.resize(n + 1);
    logs[1] = 0;
    int next_log = 2;
    for (int i = 2; i <= n; ++i)
    {
        logs[i] = logs[i - 1];
        if (i == next_log)
        {
            ++logs[i];
            next_log <<= 1;
        }
    }
}

void build_table(vector<int>& arr, vector< vector<int> >& sparse_table, int size_log)
{
    sparse_table.resize(size_log + 1, vector<int>(len(arr)));
    for (int i = 0; i < len(arr); ++i)
    {
        sparse_table[0][i] = arr[i];
    }

    for (int log = 0; log < size_log; ++log)
    {
        for (int left = 0; left < len(arr) - (2 << log) + 1; ++left)
        {
            sparse_table[log + 1][left] = min(sparse_table[log][left], sparse_table[log][left + (1 << log)]);
        }
    }
}

int query(int left, int right, vector< vector<int> >& sparse_table, vector<int>& logs)
{
    int log = logs[right - left + 1];
    return min(sparse_table[log][left], sparse_table[log][right - (1 << log) + 1]);
}