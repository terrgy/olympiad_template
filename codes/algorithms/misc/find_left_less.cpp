void find_histogram_max_area(vector<int>& arr, vector<int>& pos)
{
    vector< pair<int, int> > st;
    pos.resize(len(arr));
    st.emplace_back(-INF, -1);
    for (int i = 0; i < len(arr); ++i)
    {
        while (st.back().first >= arr[i])
        {
            st.pop_back();
        }
        pos[i] = st.back().second;
        st.emplace_back(arr[i], i);
    }
}