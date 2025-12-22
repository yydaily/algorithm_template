#include<vector>
#include<map>
#include<algorithm>
namespace TreeIsomorphism {
    using namespace std;
    class Tree {
    private:
        int n_, root_;
        vector<vector<int>> son;
        map<vector<int>, int> mp;
        vector<int> t;
        void dfs(int root, int pre) {
            vector<int> v(1, 0);
            for(auto i : son[root]) {
                if(i==pre) continue;
                dfs(i, root);
                v.push_back(t[i]);
            }
            sort(v.begin(), v.end());
            if(mp.find(v) == mp.end()) {
                mp[v] = mp.size();
            }
            t[root] = mp[v];
        }

    public:
        Tree(int n, int root) {
            n_ = n;
            root_ = root;
            t = vector<int>(n+(root==1), 0);
            son.resize(n+(root==1));
        }
        void add_edge(int u, int v) {
            son[u].push_back(v);
            son[v].push_back(u);
        }
        void build() {
            dfs(root_, -1);
        }
        int get_size() {
            return mp.size();
        }
        int get_mask(int i) {
            return t[i];
        }
    };
}