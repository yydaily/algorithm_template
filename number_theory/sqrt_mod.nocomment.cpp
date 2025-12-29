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
    
    template<typename T>
    void qpow(T a, long long b, long long mod, T& ans) {
        while (b) {
            if (b & 1) ans = ans * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
    }

    std::vector<int> sqrt_mod(int a, int p) {
        if(a<=1 || p == 2) return {a};
        long long remind = 1;
        if(qpow((long long)a, (p-1)/2, p, remind); remind != 1) {
            return {-1};
        }

        long long b, d; 
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

        Complex data_(b, 1);
        Complex power(1, 0);
        qpow(data_, (p+1)/2, p, power);

        int ans = power.a % p;
        return (ans > p-ans ? std::vector<int>{p-ans, ans} : std::vector<int>({ans, p-ans}));
    }
}
