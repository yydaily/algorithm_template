#include<vector>
#include<set>
#include<algorithm>
namespace ShortestPath {
    class Graph {
    private:
        int N, M;
        std::vector<std::vector<std::pair<long long, int>>> sons;
        std::vector<long long> distance;
        std::set<std::pair<long long, int>> q;
        std::vector<int> per;
        
    public:
        Graph(int n, int m) : N(n), M(m) {
            sons = std::vector<std::vector<std::pair<long long, int>>>(N);
        }
        
        void add_edge(int s, int t, long long v) {
            sons[s].push_back({v, t});
        }

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

        std::pair<long long, std::vector<int>> shortest_path(int s, int t) {
            std::pair<long long, std::vector<int>> ret;
            ret.first = distance[t];
            if(ret.first == 1e18) return ret;
            ret.second.push_back(t);
            while(ret.second[ret.second.size()-1] != s) {
                ret.second.push_back(per[ret.second[ret.second.size()-1]]);
            }
            std::reverse(ret.second.begin(), ret.second.end());
            return ret;
        }
    };
}
