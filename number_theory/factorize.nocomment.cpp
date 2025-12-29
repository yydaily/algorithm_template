#include<vector>
#include<algorithm>
namespace Factorize {
    using namespace PrimeTest;
    long long gcd(long long _a, long long _b) {
        unsigned long long a = abs(_a), b = abs(_b);
        if (a == 0) return b;
        if (b == 0) return a;
        int shift = __builtin_ctzll(a|b);
        a >>= __builtin_ctzll(a);
        do {
            b >>= __builtin_ctzll(b);
            if (a > b) std::swap(a, b);
            b -= a;
        } while (b);
        return (a << shift);
    }
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
