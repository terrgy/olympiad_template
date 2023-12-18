struct KunsAlgorithm {
    vector< vector<int> >& first_part_graph;
    int second_part_size;
    vector<int> second_part_matching;
    vector<char> used;
    vector<char> first_part_flag;

    KunsAlgorithm(vector< vector<int> >& first_part_graph, int second_part_size) :
            first_part_graph(first_part_graph), second_part_size(second_part_size),
            second_part_matching(second_part_size, -1), first_part_flag(first_part_graph.size()) {}


    bool dfs(int v) {
        used[v] = 1;
        for (int to : first_part_graph[v]) {
            if ((second_part_matching[to] == -1) ||
                (!used[second_part_matching[to]] && dfs(second_part_matching[to]))) {
                second_part_matching[to] = v;
                return true;
            }
        }
        return false;
    }

    int make_simple_matches() {
        int matchings_found = 0;
        for (int i = 0; i < first_part_graph.size(); ++i) {
            if (first_part_flag[i]) {
                continue;
            }
            for (int to : first_part_graph[i]) {
                if (second_part_matching[to] == -1) {
                    second_part_matching[to] = i;
                    ++matchings_found;
                    first_part_flag[i] = 1;
                    break;
                }
            }
        }
        return matchings_found;
    }

    int find_matchings() {
        int matchings_found = make_simple_matches();
        for (int i = 0; i < first_part_graph.size(); ++i) {
            if (!first_part_flag[i]) {
                used.assign(first_part_graph.size(), 0);
                matchings_found += dfs(i);
            }
        }
        return matchings_found;
    }
};