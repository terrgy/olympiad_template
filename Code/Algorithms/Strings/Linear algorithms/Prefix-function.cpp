void prefix_function(string& str, vector<int>& p)
{
    p.resize(len(str));
    p[0] = 0;
    for (int i = 1; i < len(str); ++i)
    {
        p[i] = p[i - 1];
        while (p[i] && (str[i] != str[p[i]]))
        {
            p[i] = p[p[i] - 1];
        }
        if (str[i] == str[p[i]])
        {
            ++p[i];
        }
    }
}