#include<cassert>
#include<vector>
namespace SCC {
    /*
     * 找出有向图的强连通分量
     * 限制：
     *      - 点的标号从0开始
     *      - 复杂度 O(N+M)
     */
    class Graph{
    private:
        int N;
        std::vector<std::vector<int>> g; // 有向图
        std::vector<std::vector<int>> g2; // 反向图
        std::vector<int> s; // 第一次dfs的时候记录dfs序，然后反向dfs
        std::vector<bool> vis;
        
        void dfs(int u) {
            vis[u] = true;
            for(auto v : g[u]) {
                if(!vis[v]) dfs(v);
            }
            s.push_back(u);
        }
        void dfs2(int a, int c) {
            vis[a] = true;
            sccs[c].push_back(a);
            for(auto v : g2[a]) {
                if(!vis[v]) dfs2(v, c);
            }
        }
    public:
        std::vector<std::vector<int>> sccs; // 保存了有哪些强连通分量，每个list是一个强连通分量

        Graph(int n) : N(n) {
            g.resize(n);
            g2.resize(n);
            vis = std::vector<bool>(n, false);
            s = std::vector<int>(0);
            sccs = std::vector<std::vector<int>>(0);
        }
        void add_edge(int s, int t) {
            g[s].push_back(t);
            g2[t].push_back(s);
        }
        void build() {
            for(int i = 0;i<N;i++) {
                if(!vis[i]) dfs(i);
            }
            vis = std::vector<bool>(N, false);
            for(int i = s.size()-1;i>=0;i--) {
                if(!vis[s[i]]) {
                    sccs.push_back(std::vector<int>());
                    dfs2(s[i], sccs.size()-1);
                }
            }
        }
    };
}
