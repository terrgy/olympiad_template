template<class T>
struct SplayTree
{
    struct Node
    {
        T value;
        Node* left;
        Node* right;
        Node* parent;

        Node() : Node(0) {}
        explicit Node(const T& value) : value(value)
        {
            left = right = parent = nullptr;
        }
    };

    Node* root;
    SplayTree() : SplayTree(nullptr) {}
    explicit SplayTree(Node* root) : root(root) {}

    // rotate edge (v, v->right)
    void rotate_left(Node* v)
    {
        Node* child = v->right;
        Node* parent = v->parent;
        if (parent)
        {
            if (v == parent->left)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }
        v->right = child->left;
        if (child->left)
        {
            child->left->parent = v;
        }
        child->left = v;
        v->parent = child;
        child->parent = parent;
    }

    // rotate edge (v, v->left)
    void rotate_right(Node* v)
    {
        Node* child = v->left;
        Node* parent = v->parent;
        if (parent)
        {
            if (v == parent->left)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }
        v->left = child->right;
        if (child->right)
        {
            child->right->parent = v;
        }
        child->right = v;
        v->parent = child;
        child->parent= parent;
    }

    void splay(Node* v)
    {
        if (!v)
        {
            return;
        }
        while (v->parent)
        {
            if (v == v->parent->left)
            {
                if (!v->parent->parent)
                {
                    rotate_right(v->parent);
                }
                else if (v->parent == v->parent->parent->left)
                {
                    rotate_right(v->parent->parent);
                    rotate_right(v->parent);
                }
                else
                {
                    rotate_right(v->parent);
                    rotate_left(v->parent);
                }
            }
            else
            {
                if (!v->parent->parent)
                {
                    rotate_left(v->parent);
                }
                else if (v->parent == v->parent->parent->right)
                {
                    rotate_left(v->parent->parent);
                    rotate_left(v->parent);
                }
                else
                {
                    rotate_left(v->parent);
                    rotate_right(v->parent);
                }
            }
        }
        root = v;
    }

    Node* lower_bound(const T& x)
    {
        Node* node = root;
        Node* last_suitable = nullptr;
        while (node)
        {
            if (node->value < x)
            {
                node = node->right;
            }
            else
            {
                last_suitable = node;
                node = node->left;
            }
        }
        if (!last_suitable)
        {
            return nullptr;
        }
        splay(last_suitable);
        return root;
    }

    Node* find(const T& x)
    {
        lower_bound(x);
        if (!root || (root->value != x))
        {
            return nullptr;
        }
        return root;
    }

    bool contains(const T& x)
    {
        lower_bound(x);
        return root && (root->value == x);
    }

    pair<SplayTree, SplayTree> split(const T& x)
    {
        Node* res = lower_bound(x);
        if (!res)
        {
            SplayTree tree1(root);
            root = nullptr;
            return {tree1, SplayTree()};
        }
        Node* left = root->left;
        if (left)
        {
            left->parent = root->left = nullptr;
        }
        SplayTree tree1(left);
        SplayTree tree2(root);
        root = nullptr;
        return {tree1, tree2};
    }

    void add(const T& x)
    {
        auto [tree1, tree2] = split(x);
        root = new Node(x);
        root->left = tree1.root;
        root->right = tree2.root;
        tree1.root = tree2.root = nullptr;
        if (root->left)
        {
            root->left->parent = root;
        }
        if (root->right)
        {
            root->right->parent = root;
        }
    }

    Node* find_max()
    {
        if (!root)
        {
            return nullptr;
        }
        Node* node = root;
        while (node->right)
        {
            node = node->right;
        }
        if (!node)
        {
            return nullptr;
        }
        splay(node);
        return root;
    }

    static SplayTree merge(SplayTree& tree1, SplayTree& tree2)
    {
        if (!tree1.root)
        {
            SplayTree tree = tree2;
            tree2.root = nullptr;
            return tree;
        }
        if (!tree2.root)
        {
            SplayTree tree = tree1;
            tree1.root = nullptr;
            return tree;
        }
        tree1.find_max();
        SplayTree tree(tree1.root);
        tree.root->right = tree2.root;
        if (tree.root->right)
        {
            tree.root->right->parent = tree.root;
        }
        tree1.root = tree2.root = nullptr;
        return tree;
    }

    void remove(Node* node)
    {
        if (!node)
        {
            return;
        }
        splay(node);
        Node* left = root->left;
        Node* right = root->right;
        if (left)
        {
            root->left = left->parent = nullptr;
        }
        if (right)
        {
            root->right = right->parent = nullptr;
        }
        SplayTree tree1(left);
        SplayTree tree2(right);
        SplayTree tree = merge(tree1, tree2);
        root = tree.root;
        tree.root = nullptr;
        delete node;
    }
};