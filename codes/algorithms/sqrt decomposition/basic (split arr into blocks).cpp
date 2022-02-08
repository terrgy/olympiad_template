// Queries:
// 1) add x to segment
// 2) ask if there is element x on segment

struct SqrtDecomposition
{
    struct Block
    {
        vector<int> items;
        vector<int> sorted_items;
        int whole_add;

        explicit Block(int size)
        {
            items.reserve(size);
            whole_add = 0;
        }

        void push_back(int elem)
        {
            items.push_back(elem);
        }

        void bake()
        {
            sorted_items.resize(len(items));
            iota(sorted_items.begin(), sorted_items.end(), 0);
            auto cmp = [&](int a, int b)
            {
                return items[a] < items[b];
            };
            sort(sorted_items.begin(), sorted_items.end(), cmp);
        }

        void update_whole(int value)
        {
            whole_add += value;
        }

        void update_segment(int left, int right, int value)
        {
            vector<int> not_changed, changed;
            not_changed.reserve(len(items) + left - right);
            changed.reserve(right - left);

            for (int i = 0; i < len(items); ++i)
            {
                if ((sorted_items[i] < left) || (sorted_items[i] >= right))
                {
                    not_changed.push_back(sorted_items[i]);
                }
                else
                {
                    changed.push_back(sorted_items[i]);
                    items[sorted_items[i]] += value;
                }
            }

            auto cmp = [&](int a, int b)
            {
                return items[a] < items[b];
            };

            merge(not_changed.begin(), not_changed.end(), changed.begin(), changed.end(), sorted_items.begin(), cmp);
        }

        bool ask_whole(int value)
        {
            auto cmp = [&](int a, int b)
            {
                return items[a] < b;
            };
            auto it = lower_bound(sorted_items.begin(), sorted_items.end(), value - whole_add, cmp);
            return (it != sorted_items.end()) && (items[*it] == value - whole_add);
        }

        bool ask_segment(int left, int right, int value)
        {
            int target = value - whole_add;
            for (int i = left; i < right; ++i)
            {
                if (items[i] == target)
                {
                    return true;
                }
            }
            return false;
        }
    };

    vector<Block> blocks;
    vector< pair<unsigned short, unsigned short> > positions;
    int block_size;
    int blocks_count;

    SqrtDecomposition(vector<int>& arr)
    {
        block_size = (int)sqrt(len(arr));
        blocks_count = (len(arr) - 1) / block_size + 1;
        blocks.resize(blocks_count, Block(block_size));
        positions.resize(len(arr));

        int cur_block, cur_pos_in_block;
        cur_block = cur_pos_in_block = 0;
        for (int i = 0; i < len(arr); ++i)
        {
            blocks[cur_block].push_back(arr[i]);
            positions[i] = {cur_block, cur_pos_in_block};
            if (++cur_pos_in_block == block_size)
            {
                ++cur_block;
                cur_pos_in_block = 0;
            }
        }

        for (int i = 0; i < blocks_count; ++i)
        {
            blocks[i].bake();
        }
    }

    void update(int left, int right, int value)
    {
        auto [left_block, left_block_position] = positions[left];
        auto [right_block, right_block_position] = positions[right];
        if (left_block == right_block)
        {
            blocks[left_block].update_segment(left_block_position, right_block_position + 1, value);
        }
        else
        {
            blocks[left_block].update_segment(left_block_position, block_size, value);
            for (int i = left_block + 1; i < right_block; ++i)
            {
                blocks[i].update_whole(value);
            }
            blocks[right_block].update_segment(0, right_block_position + 1, value);
        }
    }

    bool ask(int left, int right, int value)
    {
        auto [left_block, left_block_position] = positions[left];
        auto [right_block, right_block_position] = positions[right];
        if (left_block == right_block)
        {
            return blocks[left_block].ask_segment(left_block_position, right_block_position + 1, value);
        }
        if (blocks[left_block].ask_segment(left_block_position, block_size, value))
        {
            return true;
        }
        for (int i = left_block + 1; i < right_block; ++i)
        {
            if (blocks[i].ask_whole(value))
            {
                return true;
            }
        }
        if (blocks[right_block].ask_segment(0, right_block_position + 1, value))
        {
            return true;
        }
        return false;
    }
};