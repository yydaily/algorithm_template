#include<vector>
#include<numeric>
#include<algorithm>
namespace ConvexHull {
    /*
     * 计算凸包
     * 限制：
     *      - 点的范围必须要INT_MIN ~ INT_MAX范围内
     *      - 复杂度: O(nlogn) // 因为有一次排序逻辑
     *      - 可以有重复点，可以有斜率为0的点
     * 常见用法：
     *      - 平面最远点对（找出凸包后旋转卡壳一下，需要注意，一些极端case下（点全部相同）inclusize需要改为true）
     */
    template<typename T>
    std::vector<int> argsort(const std::vector<T> &points) {
        std::vector<int> ids(points.size());
        std::iota(ids.begin(), ids.end(), 0);
        std::sort(ids.begin(), ids.end(), [&](int i, int j) { return (points[i] == points[j] ? i < j : points[i] < points[j]); });
        return ids;
    }
    /*
     * 凸包实际的逻辑
     * 输入：
     *      - points: 点集，下标从0开始
     *      - inclusize: 是否包含重复点 / 是否包含多点共边的情况下的中间点
     * 输出：
     *      - 表示哪些点是凸包上的点的下标
     */
    template<typename T>
    std::vector<int> ConvexHull(const std::vector<T> &points, bool inclusize=false) {
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
            auto xi = points[i].x, yi = points[i].y;
            auto xj = points[j].x, yj = points[j].y;
            auto xk = points[k].x, yk = points[k].y;
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
