#include<vector>
#include<set>
#include<algorithm>
namespace ShortestPath {
    /*
     * 单源最短路
     * 限制：
     *      - 复杂度O（N+M）
     *      - 无负权
     *      - 最长路径不超过1e18
     *      - 有向图 / 无向图都可以
     *      - 点的标号从0开始
     */
    class Graph {
    private:
        int N, M; // n point, m edge
        std::vector<std::vector<std::pair<long long, int>>> sons; // first = value，second = to
        std::vector<long long> distance; // 记录每个点的最近距离
        std::set<std::pair<long long, int>> q; // 一个临时的queue
        std::vector<int> per; // 记录从s开始到当前位置的最短路径中，当前节点的前一个节点是什么
        
    public:
        Graph(int n, int m) : N(n), M(m) {
            sons = std::vector<std::vector<std::pair<long long, int>>>(N);
        }
        
        void add_edge(int s, int t, long long v) {
            sons[s].push_back({v, t});
        }

        /*
         * 单源最短路，复杂度O(N+M)
         * 会从s开始建图，构建每个从s可达的点的距离 & 路径
         */
        void build(int s) {
            per = std::vector<int>(N, -1);
            distance = std::vector<long long>(N, (long long) 1e18);
            q.clear();

            distance[s] = 0;
            q.insert({0, s});
            while(!q.empty()) {
                auto [v, p] = *q.begin();
                q.erase(q.begin());
                if(distance[p] < v) continue;

                for(auto [v2, p2] : sons[p]) {
                    if(distance[p2] > distance[p] + v2) {
                        q.erase({distance[p2], p2});
                        per[p2] = p;
                        distance[p2] = distance[p] + v2;
                        q.insert({distance[p2], p2});
                    }
                }
            }
        }

        /*
         * build完成后才可以调用，并且二者s需要相同，纯找路径
         * 复杂度O(path_length)
         */
        std::pair<long long, std::vector<int>> shortest_path(int s, int t) {
            std::pair<long long, std::vector<int>> ret;
            ret.first = distance[t];
            if(ret.first == 1e18) return ret; // 不存在最短路
            ret.second.push_back(t);
            while(ret.second[ret.second.size()-1] != s) {
                ret.second.push_back(per[ret.second[ret.second.size()-1]]);
            }
            std::reverse(ret.second.begin(), ret.second.end());
            return ret;
        }
    };
}
