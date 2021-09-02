int bin_pow(int a, int n, int mod)
{
    if (n == 0)
    {
        return 1;
    }
    int temp = bin_pow(a, n / 2, mod);
    temp = (temp * temp) % mod;
    if (n % 2)
    {
        temp = (temp * a) % mod;
    }
    return temp;
}

int phi(int value)
{
    int result = value;
    for (int i = 2; i * i <= value; ++i)
    {
        if (value % i == 0)
        {
            while (value % i == 0)
            {
                value /= i;
            }
            result -= result / i;
        }
    }
    if (value > 1)
    {
        result -= result / value;
    }
    return result;
}

int invert(int value, int mod)
{
    return bin_pow(value, phi(mod) - 1, mod);
}

pair<int, int> chinese_remainder_theorem(vector< pair<int, int> >& arr)
{
    int mods_mult = 1;
    for (auto [value, mod] : arr)
    {
        mods_mult *= mod;
    }
    int x = 0;
    for (auto [value, mod] : arr)
    {
        int except_x = mods_mult / mod;
        x += value * except_x * invert(except_x, mod);
    }
    return {x, mods_mult};
}