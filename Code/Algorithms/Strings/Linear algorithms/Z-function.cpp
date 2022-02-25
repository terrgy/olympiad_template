void z_function(string& s, vector<int>& result)
{
    result.resize(s.size());
    int left, right;
    left = right = 0;
    for (int i = 1; i < (int)s.size(); ++i)
    {
        if (i <= right)
        {
            result[i] = min(right - i + 1, result[i - left]);
        }
        while ((i + result[i] < s.size()) && (s[i + result[i]] == s[result[i]]))
        {
            ++result[i];
        }
        if (i + result[i] - 1 > right)
        {
            left = i;
            right = i + result[i] - 1;
        }
    }
}