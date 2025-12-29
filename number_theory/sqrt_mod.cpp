#include<vector>
namespace SqrtMod {
    long long mod, i2;
    struct Complex {
        long long a, b;
        Complex(long long _a, long long _b) : a(_a), b(_b) {}
        Complex operator*(const Complex& other) {
            return Complex((a*other.a + i2*b%mod*other.b%mod)%mod, (a*other.b + b*other.a)%mod);
        }
        Complex operator%(long long _mod) {
            return *this;
        }
    };

    // long long的快速幂和Complex的放一起了
    template<typename T>
    void qpow(T a, long long b, long long mod, T& ans) {
        while (b) {
            if (b & 1) ans = ans * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
    }

    /* 
     * 膜意义下的开方（二次剩余）: 找到 x 使得 x^2 \equiv a (mod p)
     * 复杂度：O(log p)
     * 限制：
     *   - a < 2^31
     *   - p < 2^31
     *   - p 是 素数
     * 返回：p范围内的所有满足条件的x
     */
    std::vector<int> sqrt_mod(int a, int p) {
        if(a<=1 || p == 2) return {a};
        // 判断a是否是二次剩余
        long long remind = 1;
        if(qpow((long long)a, (p-1)/2, p, remind); remind != 1) {
            return {-1};
        }

        long long b, d; // d = b*b-a 是二次非剩余
        while(true) {
            b = rand() % p;
            d = (b*b - a) % p;
            if(d < 0) d += p;
            remind = 1;
            qpow(d, (p-1)/2, p, remind);
            if(remind != 1) break;
        }
        mod = p;
        i2 = d;

        // 计算(a+i)^{(p+1)/2}
        Complex data_(b, 1);
        Complex power(1, 0);
        qpow(data_, (p+1)/2, p, power);

        int ans = power.a % p;
        return (ans > p-ans ? std::vector<int>{p-ans, ans} : std::vector<int>({ans, p-ans}));
    }
}

