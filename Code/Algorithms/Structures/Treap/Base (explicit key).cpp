struct Node
{
    int key;
    int priority;
    Node* left;
    Node* right;

    Node() : Node(-INF, -INF) {}
    Node(int key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr) {}
};

const int MAX_SIZE = (int)1e6;
Node nodes[MAX_SIZE];
int last_id = 0;

Node* get_new_node(int key = -INF, int priority = -INF)
{
    nodes[last_id].key = key;
    nodes[last_id].priority = priority;
    return &(nodes[last_id++]);
}

void split(Node* root, Node*& left, Node*& right, int key)
{
    if (!root)
    {
        left = right = nullptr;
        return;
    }

    if (root->key < key)
    {
        split(root->right, root->right, right, key);
        left = root;
    }
    else
    {
        split(root->left, left, root->left, key);
        right = root;
    }
}

void merge(Node*& root, Node* left, Node* right)
{
    if (!left || !right)
    {
        root = left ? left : right;
        return;
    }

    if (left->priority < right->priority)
    {
        merge(left->right, left->right, right);
        root = left;
    }
    else
    {
        merge(right->left, left, right->left);
        root = right;
    }
}

void insert(Node*& root, Node* new_node)
{
    if (!root)
    {
        root = new_node;
        return;
    }
    if (root->priority > new_node->priority)
    {
        split(root, new_node->left, new_node->right, new_node->key);
        root = new_node;
    }
    else
    {
        insert(root->key < new_node->key ? root->right : root->left, new_node);
    }
}