#include<vector>
namespace PrimeTest {
    long long mul(long long a, long long b, long long mod){
        return (__int128) a * b % mod;
    }

    long long Pow(long long a, long long b, long long mod){
        //mod <= 10^18.
        long long res = 1;
        while(b){
            if (b&1) res = mul(res, a, mod);
            b >>= 1;
            a = mul(a, a, mod);
        }
        return res;
    }

    std::vector<long long> pr = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    bool rabin_test(long long a, long long n, long long s, long long d){
        long long u = Pow(a, d, n);
        if (u == 1 or u == n - 1) return false;

        for(long long i = 1; i < s; i++){
            u = mul(u, u, n);
            if (u == n - 1) return false;
        }
        return true;
    }

    bool rabin_miller(long long n){
        if (n < 2) return false;
        if (n % 2 == 0) return n==2;
        long long res = 1;
        long  s = 0, d = n-1;
        while(d%2==0) {
            s++;
            d>>=1;
        }

        for(long long i = 0;i<pr.size();i++){
            if (n%pr[i] == 0) {
                return n == pr[i];
            }
            if (rabin_test(pr[i], n, s, d)){
                return false;
            }
        }
        return true;
    }
}
