tuple<int, int, int> ext_gcd(int a, int b)
{
    if (!b)
    {
        return {1, 0, a};
    }
    auto [x1, y1, g] = ext_gcd(b, a % b);
    return {y1, x1 - a / b * y1, g};
}

void diophantine_equation_solve(int a, int b, int c)
{
    if (!a && !b)
    {
        if (c)
        {
            cout << "Impossible\n";
        }
        else
        {
            cout << "0 0\n";
        }
        return;
    }
    auto [x, y, g] = ext_gcd(a, b);
    if (c % g)
    {
        cout << "Impossible\n";
        return;
    }
    x *= c / g;
    y *= c / g;

    int best_x, best_k;
    best_x = best_k = INF;
    int base_k = -x / (b / g);
    for (int k = base_k - 1; k <= base_k + 1; ++k)
    {
        int temp = x + k * b / g;
        if ((temp >= 0) && (temp < best_x))
        {
            best_x = temp;
            best_k = k;
        }
    }
    cout << best_x << ' ' << y - best_k * a / g << '\n';
}