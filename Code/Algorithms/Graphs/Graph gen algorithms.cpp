random_device rd;
mt19937 rnd(rd());

int randint(int a, int b)
{
    return rnd() % (b - a + 1) + a;
}

void tree_gen(int size = randint(1, 10))
{
    cout << size << '\n';
    int max_level_size = randint(1, size);
    int prev_left, mid, cur_right;
    prev_left = mid = 0;
    cur_right = mid + 1;
    while (cur_right < size)
    {
        cur_right = randint(mid + 1, min(size - 1, mid + max_level_size));
        for (int i = mid + 1; i <= cur_right; ++i)
        {
            int parent = randint(prev_left, mid);
            cout << parent + 1 << ' ' << i + 1 << '\n';
        }
        prev_left = mid + 1;
        mid = cur_right;
        cur_right = mid + 1;
    }
}