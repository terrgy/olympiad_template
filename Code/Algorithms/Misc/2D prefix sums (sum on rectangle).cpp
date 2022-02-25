vector< vector<ll> > sums;

ll get_sum(int x1, int y1, int x2, int y2)
{
    --x1, --y1;
    return sums[x2][y2] + sums[x1][y1] - sums[x1][y2] - sums[x2][y1];
}

void build(vector< vector<int> >& field)
{
    sums.resize(len(field) + 1, vector<ll>(len(field[0])));
    for (int i = 1; i <= len(field); ++i)
    {
        for (int j = 1; j <= len(field[0]); ++j)
        {
            sums[i][j] = sums[i][j - 1] + sums[i - 1][j] + field[i - 1][j - 1] - sums[i - 1][j - 1];
        }
    }
}