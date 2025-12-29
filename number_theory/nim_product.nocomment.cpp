#include <cstring>
namespace NimProd {
    using ull = unsigned long long;
    ull cache[257][257];
    ull solve(ull x, ull y, int p = 32) {
        if (x <= 1 || y <= 1) return x * y;
        if (p < 8 && cache[x][y]) return cache[x][y];

        ull a = x >> p;
        ull b = ((1ull << p) - 1) & x;
        ull c = y >> p;
        ull d = ((1ull << p) - 1) & y;

        ull bd = solve(b, d, p >> 1);
        ull ac = solve(solve(a, c, p >> 1), 1ull << p >> 1, p >> 1);

        ull ans = ((solve(a ^ b, c ^ d, p >> 1) ^ bd) << p) ^ ac ^ bd;
        if (p < 8) cache[x][y] = cache[y][x] = ans;
        return ans;
    }
    void init() {
        memset(cache, 0, sizeof(cache));
        for(int i = 0;i<256;i++) {
            for(int j = 0;j<256;j++) {
                solve(i, j);
            }
        }
    }
}

