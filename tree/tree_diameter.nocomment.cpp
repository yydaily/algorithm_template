#include <vector>
#include <tuple>
namespace TreeDiameter {
    using namespace std;
    using Graph = vector<vector<pair<int, long long>>>;
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
    tuple<int, int, long long> tree_diameter(const vector<vector<pair<int, long long>>> &g) {
        auto u = dfs(g, 0, -1).second;
        long long dist;
        int v;
        tie(dist, v) = dfs(g, u, -1);
        return make_tuple(u, v, dist);
    }
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
