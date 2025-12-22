#include <vector>
#include <tuple>
namespace TreeDiameter {
    /* 
     * 无向正权树的最大直径，限制：
     * 1. 直径需要<= LONG_LONG_MAX
     * 2. 单颗树，而非森林
     */
    using namespace std;
    using Graph = vector<vector<pair<int, long long>>>; // 起点对应的边(终点 & 权值)

    /*
     * Input: 树, 起始点
     * Output: 离起始点最大的距离, 对应的点
     * 复杂度: O(边数)
     */
    pair<long long, int> dfs(const vector<vector<pair<int, long long>>> &g, int cur, int par = -1) {
        pair<long long, int> ret(0, cur);
        for (auto e : g[cur]) {
            if (e.first == par) continue;
            auto cost = dfs(g, e.first, cur);
            cost.first += e.second;
            ret = max(ret, cost);
        }
        return ret;
    }
    /*
     * Input: 树
     * Output: 直径起点，直径终点，直径长度
     */
    tuple<int, int, long long> tree_diameter(const vector<vector<pair<int, long long>>> &g) {
        auto u = dfs(g, 0, -1).second;
        long long dist;
        int v;
        tie(dist, v) = dfs(g, u, -1);
        return make_tuple(u, v, dist);
    }

    /*
     * 会搜索出一条从cur到goal的路径，结果会放在path里面
     * Input: 树
     * Output: 路径
     * 复杂度：O(边数)
     */
    void path_restoration(const vector<vector<pair<int, long long>>> &g, vector<int> &path, int cur, int par, int &goal) {
        path.push_back(cur);
        if (cur == goal) {
            goal = -1;
            return;
        }

        for (auto e : g[cur]) {
            int nxt = e.first;
            if (nxt == par) continue;
            path_restoration(g, path, nxt, cur, goal);
            if (goal == -1) return;
        }

        if (goal == -1) {
            return;
        }
        path.pop_back();
    }
}

