#include<vector>
#include<numeric>
#include<algorithm>
namespace ConvexHull {
    std::vector<int> argsort(const std::vector<std::pair<long long, long long>> &points) {
        std::vector<int> ids(points.size());
        std::iota(ids.begin(), ids.end(), 0);
        std::sort(ids.begin(), ids.end(), [&](int i, int j) { return (points[i] == points[j] ? i < j : points[i] < points[j]); });
        return ids;
    }
    std::vector<int> ConvexHull(const std::vector<std::pair<long long, long long>> &points, bool inclusize=false) {
        long long N = points.size();
        if(N==0) return {};
        if(N==1) return {0};
        if(N==2) {
            if(points[0]<points[1]) return {0, 1};
            if(points[1]<points[0]) return {1, 0};
            if(inclusize) return {0, 1};
            return {0};
        }
        auto idx = argsort(points);

        auto check = [&](long long i, long long j, long long k) -> bool {
            auto xi = points[i].first, yi = points[i].second;
            auto xj = points[j].first, yj = points[j].second;
            auto xk = points[k].first, yk = points[k].second;
            auto dx1 = xj - xi, dy1 = yj - yi;
            auto dx2 = xk - xj, dy2 = yk - yj;
            auto det = dx1 * dy2 - dy1 * dx2;
            return (inclusize ? det >= 0 : det > 0);
        };

        auto calc = [&]() {
            std::vector<int> P;
            for(auto &&k: idx) {
                if(P.size() && points[P.back()] == points[k]) continue;
                while(P.size()>1) {
                    auto i = P[P.size()-2];
                    auto j = P[P.size()-1];
                    if(check(i, j, k)) break;
                    P.pop_back();
                }
                P.emplace_back(k);
            }
            return P;
        };

        auto P = calc();
        if(!P.empty()) P.pop_back();
        std::reverse(idx.begin(), idx.end());
        auto Q = calc();
        P.insert(P.end(), Q.begin(), Q.end());
        if(P.size()>=2 && points[P[0]] == points[P.back()]) P.pop_back();
        return P;
    }
}
