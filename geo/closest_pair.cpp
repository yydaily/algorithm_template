#include<vector>
namespace ClosestPair {
    /*
     * 平面最近点对
     * 复杂度：O(n log n)
     * 限制:
     *      - 坐标需要是整数，范围 INT_MIN ~ INT_MAX
     */
    struct Point {
        long long x, y;
        Point() : x(0), y(0) {}
        Point(long long x, long long y) : x(x), y(y) {}
        Point(std::pair<long long, long long> p) : x(p.first), y(p.second) {}
        Point operator+(Point p) const { return {x + p.x, y + p.y}; }
        Point operator-(Point p) const { return {x - p.x, y - p.y}; }
        bool operator==(Point p) const { return x == p.x && y == p.y; }
        bool operator!=(Point p) const { return x != p.x || y != p.y; }
        Point operator-() const { return {-x, -y}; }
        Point operator*(long long t) const { return {x * t, y * t}; }
        Point operator/(long long t) const { return {x / t, y / t}; }
        bool operator<(Point p) const {
            if (x != p.x) return x < p.x;
            return y < p.y;
        }
        long long dot(const Point& other) { return x * other.x + y * other.y; }
        long long det(const Point& other) { return x * other.y - y * other.x; }
    };
    

    std::pair<int, int> closest_pair_dc(std::vector<Point> point) {
        int N = point.size();

        auto I = Rerange::argsort(point); // 按照x,y排序
        point = Rerange::rearrange(point, I); // 重排后的point列表

        long long best = -1; // 记录最佳距离
        std::pair<int, int> best_pair = {-1, -1}; // 记录最近点对
        auto upd = [&](int i, int j) -> void { // 无脑更新函数
            Point p = point[i] - point[j];
            long long d = p.dot(p);
            if (best == -1 || best > d) { best = d, best_pair = {I[i], I[j]}; }
        };

        upd(0, 1); // 用(0,1)这两个点来初始化答案

        auto dfs = [&](auto &dfs, int L, int R) -> std::vector<int> { // 分治
            if (R == L + 1) return {L};
            int M = (L + R) / 2;
            auto I0 = dfs(dfs, L, M);
            auto I1 = dfs(dfs, M, R);
            std::vector<int> I;
            std::vector<int> near;
            int a = 0, b = 0;
            for (int i = 0; i < R-L; i++) {
                auto idx = [&]() -> int {
                    if (a == I0.size()) return I1[b++];
                    if (b == I1.size()) return I0[a++];
                    int i = I0[a], j = I1[b];
                    if (point[i].y < point[j].y) {
                        ++a;
                        return i;
                    }
                    ++b;
                    return j;
                }();
                I.emplace_back(idx);
                auto dx = point[M].x - point[idx].x;
                if (dx * dx > best) { continue; }
                for (int k = near.size()-1; k >= 0; k--) {
                    int j = near[k];
                    long long dy = point[idx].y - point[j].y;
                    if (best == 0 || dy * dy > best) break;
                    upd(idx, j);
                }
                near.emplace_back(idx);
            }
            return I;
        };

        dfs(dfs, 0, N);
        return best_pair;
    }
}

