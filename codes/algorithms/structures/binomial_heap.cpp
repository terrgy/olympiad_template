struct BinomialHeap
{
    struct Node
    {
        int key;
        Node* parent;
        Node* child;
        Node* sibling;
        int degree;
        BinomialHeap* parental_heap;

        Node() : Node(0) {}
        explicit Node(int key) : key(key), parent(nullptr), child(nullptr), sibling(nullptr), degree(0), parental_heap(
                nullptr) {}
    };

    Node* node_before_min;
    Node* head;

    BinomialHeap() : BinomialHeap(nullptr) {}
    explicit BinomialHeap(Node* head) : head(head), node_before_min(nullptr)
    {
        validate_min();
    }

    Node* get_min_p() const
    {
        if (!head)
        {
            return nullptr;
        }
        if (!node_before_min)
        {
            return head;
        }
        return node_before_min->sibling;
    }

    int get_min() const
    {
        Node* temp = get_min_p();
        if (!temp)
        {
            return INF;
        }
        return temp->key;
    }

    void validate_min()
    {
        Node* current_node, *prev_node;
        current_node = head;
        prev_node = nullptr;
        node_before_min = nullptr;
        while (current_node)
        {
            if (current_node->key < get_min())
            {
                node_before_min = prev_node;
            }
            prev_node = current_node;
            current_node = current_node->sibling;
        }
    }

    void check_node_before_min_update(Node* current_node, Node* new_min, Node* prev_node)
    {
        if (new_min == current_node)
        {
            node_before_min = prev_node;
        }
    }

    void merge_add(Node*& current_node, Node*& merged_current, Node* new_min, Node* prev_node)
    {
        check_node_before_min_update(current_node, new_min, prev_node);
        merged_current->sibling = current_node;
        merged_current = current_node;
        current_node = current_node->sibling;
    }

    void merge_heads(BinomialHeap& other, Node* new_min)
    {
        if (!head || !other.head)
        {
            if (other.head)
            {
                head = other.head;
                node_before_min = other.node_before_min;
                other.head = other.node_before_min = nullptr;
            }
            return;
        }

        Node* merged_root, *merged_prev, *merged_current;
        if (head->degree < other.head->degree)
        {
            check_node_before_min_update(head, new_min, nullptr);
            merged_root = head;
            head = head->sibling;
        }
        else
        {
            check_node_before_min_update(other.head, new_min, nullptr);
            merged_root = other.head;
            other.head = other.head->sibling;
        }
        merged_current = merged_root;
        merged_prev = merged_current;

        while (head && other.head)
        {
            if (head->degree < other.head->degree)
            {
                merge_add(head, merged_current, new_min, merged_prev);
            }
            else
            {
                merge_add(other.head, merged_current, new_min, merged_prev);
            }
            merged_prev = merged_current;
        }
        while (head)
        {
            merge_add(head, merged_current, new_min, merged_prev);
            merged_prev = merged_current;
        }
        while (other.head)
        {
            merge_add(other.head, merged_current, new_min, merged_prev);
            merged_prev = merged_current;
        }
        head = merged_root;
        other.node_before_min = nullptr;
    }

    Node* merge_nodes(Node* first, Node* second)
    {
        if (!first || !second)
        {
            return first ? first : second;
        }
        if (first->key > second->key)
        {
            return merge_nodes(second, first);
        }
        second->parent = first;
        second->sibling = first->child;
        first->child = second;
        ++first->degree;
        return first;
    }

    void unite_by_degrees(Node* new_min)
    {
        if (!head)
        {
            return;
        }
        Node* prev_node = nullptr;
        Node* current_node = head;
        while (current_node->sibling)
        {
            if (current_node->degree == current_node->sibling->degree) {
                Node *next = current_node->sibling->sibling;
                bool update_node_before_min = false;
                if ((current_node == node_before_min) || (current_node == new_min))
                {
                    node_before_min = prev_node;
                } else if (current_node->sibling == node_before_min)
                {
                    update_node_before_min = true;
                }
                current_node = merge_nodes(current_node, current_node->sibling);
                if (update_node_before_min)
                {
                    node_before_min = current_node;
                }
                current_node->sibling = next;
                if (prev_node)
                {
                    prev_node->sibling = current_node;
                }
                else
                {
                    head = current_node;
                }
                continue;
            }
            prev_node = current_node;
            current_node = current_node->sibling;
        }
        current_node->parental_heap = this;
    }

    Node* get_new_min(BinomialHeap& other) const
    {
        if (other.get_min() <= get_min())
        {
            return other.get_min_p();
        }
        return get_min_p();
    }

    void merge(BinomialHeap& other)
    {
        Node* new_min = get_new_min(other);
        merge_heads(other, new_min);
        unite_by_degrees(new_min);
    }

    void insert(int key)
    {
        BinomialHeap new_heap(new Node(key));
        merge(new_heap);
    }

    void insert(Node* node)
    {
        BinomialHeap new_heap(node);
        merge(new_heap);
    }

    static Node* reverse_row(Node* current_node)
    {
        Node* prev_node;
        prev_node = nullptr;
        while (current_node)
        {
            Node* next = current_node->sibling;
            current_node->sibling = prev_node;
            current_node->parent = nullptr;

            prev_node = current_node;
            current_node = next;
        }
        return prev_node;
    }

    Node* pop()
    {
        if (!head)
        {
            return nullptr;
        }
        Node* popped_node = get_min_p();
        if (node_before_min)
        {
            node_before_min->sibling = popped_node->sibling;
        }
        else
        {
            head = popped_node->sibling;
        }
        validate_min();
        popped_node->sibling = nullptr;

        Node* child_head = reverse_row(popped_node->child);
        popped_node->child = nullptr;

        BinomialHeap new_heap(child_head);
        merge(new_heap);

        popped_node->degree = 0;
        return popped_node;
    }

    void swap_node_with_parent(Node* node)
    {
        Node* parent = node->parent;
        swap(*node, *parent);
    }

    void decrease_value(Node* node, int new_value)
    {
        if (new_value > node->key)
        {
            throw -1;
        }
        node->key = new_value;
        while (node->parent)
        {
            if (node->parent->key <= node->key)
            {
                break;
            }
            swap_node_with_parent(node);
            swap(node->parent->key, node->key);
            node = node->parent;
        }
        validate_min();
        return node;
    }

    Node* erase(Node* node)
    {
        decrease_value(node, -INF);
        return pop();
    }

    void change_value(Node* node, int new_value)
    {
        node = erase(node);
        node->key = new_value;
        insert(node);
    }

    bool empty() const
    {
        return !head;
    }

    static BinomialHeap* get_heap(Node* node)
    {
        while (node->parent)
        {
            node = node->parent;
        }
        while (node->sibling)
        {
            node = node->sibling;
        }
        return node->parental_heap;
    }
};