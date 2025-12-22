#include<vector>
#include<map>
#include<algorithm>
namespace TreeIsomorphism {
    /*
     * 判断有根树是否同构，限制：
     * 1. root只能为0或者1
     * 2. 复杂度 O(n*log(n))
     */
    using namespace std;
    class Tree {
    private:
        int n_, root_;
        vector<vector<int>> son;
        map<vector<int>, int> mp;
        vector<int> t;
        /*
         * 建树过程
         * 每次会从root开始遍历，记录每个子节点的编号，并从map中判断是否已经存在同构结构
         * 为了保证同构，所以需要一个sort来保证子节点编号不影响结果
         */
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

        /*
         * 添加边
         * 这里只要是无向边就行了，不需要保证u是v的父亲
         */
        void add_edge(int u, int v) {
            son[u].push_back(v);
            son[v].push_back(u);
        }

        /*
         * 构建树
         * 这里会计算出每个节点的结构，并给一个编号，保证编号相同的节点对应的子树是同构的
         */
        void build() {
            dfs(root_, -1);
        }

        /*
         * 返回有多少个不同构的子树
         */
        int get_size() {
            return mp.size();
        }

        /*
         * 返回每个子树的编号
         * Input: 每个节点的编号
         * Output: 每个子树的结构编号
         * 仅保证相同结构的子树返回的编号一致，不保证节点更多的子树编号更大
         */
        int get_mask(int i) {
            return t[i];
        }
    };
}
