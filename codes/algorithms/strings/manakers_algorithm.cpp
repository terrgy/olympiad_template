void manakers_algorithm_odd(string& str, vector<int>& p)
{
    p.resize(len(str));
    int left, right;
    left = right = -1;
    for (int i = 0; i < len(str); ++i)
    {
        if (i <= right)
        {
            p[i] = min(p[left + right - i], right - i + 1);
        }
        while ((i - p[i] > -1) && (i + p[i] < len(str)) && (str[i - p[i]] == str[i + p[i]]))
        {
            ++p[i];
        }
        if (i + p[i] - 1 > right)
        {
            left = i - p[i] + 1;
            right = i + p[i] - 1;
        }
    }
}

void manakers_algorithm_even(string& str, vector<int>& p)
{
    p.resize(len(str) - 1);
    int left, right;
    left = right = -1;
    for (int i = 0; i < len(str) - 1; ++i)
    {
        if (i < right)
        {
            p[i] = min(p[left + right - i - 1], right - i);
        }
        while ((i - p[i] > -1) && (i + p[i] + 1 < len(str)) && (str[i - p[i]] == str[i + p[i] + 1]))
        {
            ++p[i];
        }
        if (i + p[i] > right)
        {
            left = i - p[i] + 1;
            right = i + p[i];
        }
    }
}