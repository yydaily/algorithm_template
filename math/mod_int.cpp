#include <cstdint>
#include <iostream>
template < uint32_t mod >
struct ModInt {
    /*
     * 膜意义下的整数
     * 支持加减乘除，并且用了 Montgomery modular multiplication 加速，把膜运算干掉了，转为膜运算。
     * 限制：
     *      - mod < 2 ^ 30
     *      - mod 需要是奇数
     * 在朴素的n^3矩阵乘法场景下，比直接取模快的多（矩阵大小为800 ～ 2000时，矩阵纯随机，只需要1/3时间）
     */
    using mint = ModInt;
    using i32 = int32_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    static constexpr u32 get_r() {
        u32 ret = mod;
        for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
        return ret;
    }

    static constexpr u32 r = get_r(); // mod在 膜2^32 意义下的逆元
    static constexpr u32 n2 = -u64(mod) % mod;
    static_assert(r * mod == 1, "invalid, r * mod != 1");
    static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
    static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");

    u32 a;

    constexpr ModInt(): a(0) {}
    constexpr ModInt(const int64_t & b): a(reduce(u64(b % mod + mod) * n2)) {};

    static constexpr u32 reduce(const u64 & b) { // 转成 %mod 意义的整数
        return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
    }

    constexpr mint & operator += (const mint & b) {
        if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
        return * this;
    }
    constexpr mint & operator -= (const mint & b) {
        if (i32(a -= b.a) < 0) a += 2 * mod;
        return * this;
    }
    constexpr mint & operator *= (const mint & b) {
        a = reduce(u64(a) * b.a);
        return * this;
    }
    constexpr mint & operator /= (const mint & b) {
        * this *= b.inverse();
        return * this;
    }

    constexpr mint operator + (const mint & b) const { return mint( * this) += b; }
    constexpr mint operator - (const mint & b) const { return mint( * this) -= b; }
    constexpr mint operator * (const mint & b) const { return mint( * this) *= b; }
    constexpr mint operator / (const mint & b) const { return mint( * this) /= b; }
    constexpr bool operator == (const mint & b) const {
        return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
    }
    constexpr bool operator != (const mint & b) const {
        return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
    }
    constexpr mint operator - () const {
        return mint() - mint( * this);
    }

    constexpr mint pow(u64 n) const {
        mint ret(1), mul( * this);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    constexpr mint inverse() const {
        return pow(mod - 2);
    }

    friend std::ostream & operator << (std::ostream & os, const mint & b) {
        return os << b.get();
    }

    friend std::istream & operator >> (std::istream & is, mint & b) {
        int64_t t;
        is >> t;
        b = ModInt < mod > (t);
        return (is);
    }

    constexpr u32 get() const {
        u32 ret = reduce(a);
        return ret >= mod ? ret - mod : ret;
    }

    static constexpr u32 get_mod() {
        return mod;
    }
};
