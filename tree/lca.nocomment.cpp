#include <vector>

namespace LCA {
#define V vector
    using namespace std;
    class Tree {
    private:
        int n_;
        int root_;
        int lg;
        V<int> depth;
        V<V<int>> father;
        V<V<int>> son;
        void dfs(int now, int pre = -1, int dep = 1) {
            depth[now] = dep;
            father[0][now] = pre;
            for(auto s : son[now]) {
                if(s==pre) continue;
                dfs(s, now, dep+1);
            }
        }
        void build_father() {
            for(int i = 1; i < lg; i++) {
                for(int j = root_; j < n_ + (root_==1); j++) {
                    father[i][j] = (father[i-1][j] == -1) ? -1 : father[i-1][father[i-1][j]];
                }
            }
        }
    public:
        Tree(int root, int n) {
            root_ = root;
            n_ = n;
            lg = 1;
            while((1<<lg) < n) lg++;
            depth.resize(n+(root==1));
            father = V<V<int>>(lg, V<int>(n+(root==1), -1));
            son = V<V<int>>(n+(root==1), V<int>(0));
        }
        void add(int pre, int now) {
            son[pre].push_back(now);
            son[now].push_back(pre);
        }
        void build() {
            this->dfs(root_);
            this->build_father();
        }
        int query_lca(int u, int v) {
            if(depth[u] > depth[v]) {
                swap(u, v);
            }
            int depth_diff = depth[v] - depth[u];
            for(int i = 0; i < lg; i++) {
                if(depth_diff & (1<<i)) {
                    v = father[i][v];
                }
            }
            if(u == v) {
                return u;
            }
            for(int i = lg - 1; i >= 0; i--) {
                if(father[i][u] != father[i][v]) {
                    u = father[i][u];
                    v = father[i][v];
                }
            }
            return father[0][u];
        }
    };
}