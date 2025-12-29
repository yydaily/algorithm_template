#include<vector>
#include<algorithm>
namespace Factorize {
    /*
     * 可以分解不超过 LONG_LONG_MAX 的合数的所有因子，期望复杂度为 O(n^{1/4})
     */
    using namespace PrimeTest;

    /*
     * 牛逼plus的gcd
     * 由于不用做除法和取模，只用了二进制命令和减法，所以速度非常快
     * 这里不是朴素的更相减损术，而是用了一些优雅的性质
     */
    long long gcd(long long _a, long long _b) {
        unsigned long long a = abs(_a), b = abs(_b);
        if (a == 0) return b;
        if (b == 0) return a;
        int shift = __builtin_ctzll(a|b); // 拿到了最多有多少个2
        a >>= __builtin_ctzll(a); // 这里保证了a是奇数
        do {
            b >>= __builtin_ctzll(b); // 这里保证了b是奇数
            if (a > b) std::swap(a, b);
            b -= a; // 这里两个奇数相减，一定是偶数，在下一个循环中至少二进制会少一位
        } while (b);
        return (a << shift);
    }

    /*
     * 返回n的任意一个素因子
     * 用一个优雅的近似随机数来判断是否是素数
     * 如果随机过程均匀，期望复杂度是 O(n^{1/4} * log(n))
     */
    long long pollard_single(long long n) {
        if (rabin_miller(n)) return n;
        if (n%2==0) return 2;
        long long st = 0;
        auto f = [&](long long x) { return (__int128(x) * x + st) % n; };
        while (true) {
            st++;
            long long x = st, y = f(x);
            while (true) {
                long long p = gcd((y - x + n), n);
                if (p == 0 or p == n) break;
                if (p != 1) return p;
                x = f(x);
                y = f(f(y));
            }
        }
    }

    /*
     * 返回n的所有素因子
     * n的因子越多，该算法越快
     * 近似复杂度可以用 O(n^{1/4}) 估计
     */
    std::vector<long long> pollard(long long n) {
        if(n==1) return {};
        auto x = pollard_single(n);
        if (x==n) return {x};
        auto l = pollard(x);
        auto r = pollard(n/x);
        l.insert(l.end(), r.begin(), r.end());
        return l;
    }
}
