istream& operator>>(istream& in, __int128& value)
{
    string str;
    in >> str;
    value = 0;
    for (char c : str)
    {
        value = value * 10 + (c - '0');
    }
    return in;
}

ostream& operator<<(ostream& out, __int128& value)
{
    if (value == 0)
    {
        out << '0';
        return out;
    }
    vector<char> str;
    while (value)
    {
        str.push_back((char)(value % 10 + '0'));
        value /= 10;
    }
    for (int i = (int)str.size() - 1; i > -1; --i)
    {
        out << str[i];
    }
    return out;
}