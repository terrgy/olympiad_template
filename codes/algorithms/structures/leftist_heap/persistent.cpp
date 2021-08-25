struct Node
{
    Node* left;
    Node* right;
    int value;
    int d;

    Node(): Node(0) {}
    explicit Node(int value) : value(value), left(nullptr), right(nullptr), d(0) {}
};

Node* merge(Node* root1, Node* root2)
{
    if (!root1 || !root2)
    {
        return root1 ? root1 : root2;
    }

    if (root1->value > root2->value)
    {
        swap(root1, root2);
    }

    Node* new_node = new Node(root1->value);
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

Node* add(Node* root, int new_value)
{
    Node* new_node = new Node(new_value);
    return merge(root, new_node);
}

int get_min(Node* root)
{
    if (root)
    {
        return root->value;
    }
    return NOT_EXIST;
}

pair<Node*, int> pop_min(Node* root)
{
    if (!root)
    {
        return {nullptr, NOT_EXIST};
    }
    return {merge(root->left, root->right), root->value};
}