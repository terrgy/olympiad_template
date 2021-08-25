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
    root1->right = merge(root1->right, root2);

    if (!root1->left || (root1->left->d < root1->right->d))
    {
        swap(root1->left, root1->right);
    }
    root1->d = 1;
    if (root1->right)
    {
        root1->d += root1->right->d;
    }
    return root1;
}

void add(Node*& root, int new_value)
{
    Node* new_node = new Node(new_value);
    root = merge(root, new_node);
}

int get_min(Node* root)
{
    if (root)
    {
        return root->value;
    }
    return NOT_EXIST;
}

int pop_min(Node*& root)
{
    int min_elem = get_min(root);
    if (root)
    {
        Node* temp_node = root;
        root = merge(root->left, root->right);
        delete temp_node;
    }
    return min_elem;
}