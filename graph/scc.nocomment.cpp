#include<cassert>
#include<vector>
namespace SCC {
    class Graph{
    private:
        int N;
        bool start_from_one;
        std::vector<std::vector<int>> g;
        std::vector<std::vector<int>> g2;
        std::vector<int> s;
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
        std::vector<std::vector<int>> sccs;

        Graph(int n, int start_from_one = false) : N(n), start_from_one(start_from_one) {
            g.resize(n+start_from_one);
            g2.resize(n+start_from_one);
            vis = std::vector<bool>(n+start_from_one, false);
            s = std::vector<int>(0);
            sccs = std::vector<std::vector<int>>(0);
        }
        void add_edge(int s, int t) {
            g[s].push_back(t);
            g2[t].push_back(s);
        }
        void build() {
            for(int i = start_from_one;i<N+start_from_one;i++) {
                if(!vis[i]) dfs(i);
            }
            vis = std::vector<bool>(N+start_from_one, false);
            for(int i = s.size()-1;i>=0;i--) {
                if(!vis[s[i]]) {
                    sccs.push_back(std::vector<int>());
                    dfs2(s[i], sccs.size()-1);
                }
            }
        }
    };
}

