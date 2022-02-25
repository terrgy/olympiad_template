const int HASH_BASE1 = 197;
const int HASH_BASE2 = 211;
const int HASH_MOD1 = (int)1e9 + 7;
const int HASH_MOD2 = (int)1e9 + 9;

void prepare_pows(vector<int>& pows, int max_size, int hash_base, int hash_mod)
{
    pows.resize(max_size + 1);
    pows[0] = 1;
    for (int i = 1; i <= max_size; ++i)
    {
        pows[i] = (int)((ll)pows[i - 1] * hash_base % hash_mod);
    }
}

void build_hash(string& str, vector<int>& hash, int hash_base, int hash_mod)
{
    hash.resize(len(str) + 1);
    for (int i = 1; i <= len(str); ++i)
    {
        hash[i] = (int)(((ll)hash[i - 1] * hash_base + (str[i - 1] - 'a' + 1)) % hash_mod);
    }
}

int get_hash(int left, int right, vector<int>& hash, vector<int>& pows, int hash_mod)
{
    return (int)((hash_mod + hash[right] - (int)((ll)hash[left] * pows[right - left] % hash_mod)) % hash_mod);
}