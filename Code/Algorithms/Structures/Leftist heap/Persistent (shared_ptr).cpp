struct Node
{
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    int value;
    int d;

    Node(): Node(0) {}
    explicit Node(int value) : value(value), left(nullptr), right(nullptr), d(0) {}
};

shared_ptr<Node> create_node(int value = 0)
{
    return make_shared<Node>(value);
}

shared_ptr<Node> merge(const shared_ptr<Node>& root1, const shared_ptr<Node>& root2)
{
    if (!root1 || !root2)
    {
        return root1 ? root1 : root2;
    }

    if (root1->value > root2->value)
    {
        return merge(root2, root1);
    }

    shared_ptr<Node> new_node = create_node(root1->value);
    new_node->left = root1->left;
    new_node->right = merge(root1->right, root2);
    
    if (!new_node->left || (new_node->left->d < new_node->right->d))
    {
        swap(new_node->left, new_node->right);
    }
    new_node->d = 1;
    if (new_node->right)
    {
        new_node->d += new_node->right->d;
    }
    return new_node;
}

shared_ptr<Node> add(const shared_ptr<Node>& root, int new_value)
{
    shared_ptr<Node> new_node = create_node(new_value);
    return merge(root, new_node);
}

int get_min(const shared_ptr<Node>& root)
{
    if (root)
    {
        return root->value;
    }
    return NOT_EXIST;
}

pair<shared_ptr<Node>, int> pop_min(const shared_ptr<Node>& root)
{
    if (!root)
    {
        return {nullptr, NOT_EXIST};
    }
    return {merge(root->left, root->right), root->value};
}