random_device rd;
mt19937 rnd(rd());

int randint(int a, int b)
{
    return rnd() % (b - a + 1) + a;
}

struct Node
{
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    int value;
    int sum;
    int size;

    Node() : Node(0) {}
    explicit Node(int value) : left(nullptr), right(nullptr), value(value), sum(value), size(1) {}
};

int get_size(const shared_ptr<Node>& node)
{
    return node ? node->size : 0;
}

int get_sum(const shared_ptr<Node>& node)
{
    return node ? node->sum : 0;
}

void update(shared_ptr<Node>& node)
{
    if (node)
    {
        node->size = get_size(node->left) + get_size(node->right) + 1;
        node->sum = (int)(((ll)get_sum(node->left) + get_sum(node->right) + node->value) % MOD);
    }
}

pair< shared_ptr<Node>, shared_ptr<Node> > split(const shared_ptr<Node>& node, int key)
{
    if (!node)
    {
        return {nullptr, nullptr};
    }
    if (get_size(node->left) < key)
    {
        auto [left, right] = split(node->right, key - get_size(node->left) - 1);
        shared_ptr<Node> new_node = make_shared<Node>(node->value);
        new_node->left = node->left;
        new_node->right = left;
        update(new_node);
        return {new_node, right};
    }
    auto [left, right] = split(node->left, key);
    shared_ptr<Node> new_node = make_shared<Node>(node->value);
    new_node->left = right;
    new_node->right = node->right;
    update(new_node);
    return {left, new_node};
}

bool merge_choose(int left_size, int right_size)
{
    int p = (int)((double)left_size * 10000 / (left_size + right_size));
    return randint(0, 10000) <= p;
}

shared_ptr<Node> merge(const shared_ptr<Node>& left, const shared_ptr<Node>& right)
{
    if (!left || !right)
    {
        return left ? left : right;
    }
    if (merge_choose(get_size(left), get_size(right)))
    {
        shared_ptr<Node> new_node = make_shared<Node>(left->value);
        new_node->left = left->left;
        new_node->right = merge(left->right, right);
        update(new_node);
        return new_node;
    }
    shared_ptr<Node> new_node = make_shared<Node>(right->value);
    new_node->right = right->right;
    new_node->left = merge(left, right->left);
    update(new_node);
    return new_node;
}

pair< shared_ptr<Node>, shared_ptr<Node> > head(const shared_ptr<Node>& node)
{
    return split(node, 1);
}

pair< shared_ptr<Node>, shared_ptr<Node> > tail(const shared_ptr<Node>& node)
{
    return split(node, node->size - 1);
}