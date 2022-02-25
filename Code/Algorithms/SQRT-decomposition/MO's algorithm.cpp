const int MAX_NUMBER = (int)1e6;

struct WorkingSegment
{
    vector<int>& arr;
    ll answer;
    int left_;
    int right_;
    int counts[MAX_NUMBER + 1];

    explicit WorkingSegment(vector<int>& arr) : arr(arr)
    {
        answer = 0;
        left_ = 0;
        right_ = -1;
        fill(counts, counts + MAX_NUMBER + 1, 0);
    }

    ll count_intake(int value)
    {
        return (ll)counts[value] * counts[value] * value;
    }

    void move(int left, int right)
    {
        while (left < left_)
        {
            add_left();
        }
        while (right_ < right)
        {
            add_right();
        }
        while (left_ < left)
        {
            remove_left();
        }
        while (right < right_)
        {
            remove_right();
        }
    }

    void add(int value)
    {
        answer -= count_intake(value);
        ++counts[value];
        answer += count_intake(value);
    }

    void remove(int value)
    {
        answer -= count_intake(value);
        --counts[value];
        answer += count_intake(value);
    }

    void add_left()
    {
        add(arr[--left_]);
    }

    void add_right()
    {
        add(arr[++right_]);
    }

    void remove_left()
    {
        remove(arr[left_++]);
    }

    void remove_right()
    {
        remove(arr[right_--]);
    }

    ll get_answer()
    {
        return answer;
    }
};

void mo_algorithm(vector<int>& arr, vector< pair<int, int>, int>& queries, vector<ll>& answers)
{
    int block_size = (int)sqrt(len(arr));
    auto cmp = [&](const pair< pair<int, int>, int>& a, const pair< pair<int, int>, int>& b)
    {
        return make_pair(a.first.first / block_size, a.first.second) < make_pair(b.first.first / block_size, b.first.second);
    };
    sort(queries.begin(), queries.end(), cmp);

    WorkingSegment seg(arr);

    vector<ll> answers(m);
    for (auto [borders, id] : queries)
    {
        seg.move(borders.first, borders.second);
        answers[id] = seg.get_answer();
    }
}