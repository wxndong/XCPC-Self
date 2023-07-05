// url : https://ac.nowcoder.com/acm/contest/33195/H
#include <bits/stdc++.h>

constexpr int P = 998244353;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template<class T>
T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    Z(i64 x) : x(norm(x % P)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(P - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int A, B, tmp;
    std::cin >> A;
    for (int i = 0; i < 7; i++) {
        std::cin >> tmp;
    }
    std::cin >> B;
    for (int i = 0; i < 7; i++) {
        std::cin >> tmp;
    }
    
    A = (A + 9) / 10;
    B = (B + 9) / 10;
    
    const int N = A + B;
    
    std::vector<Z> fac(N + 1), invfac(N + 1);
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i;
    }
    invfac[N] = fac[N].inv();
    for (int i = N; i; i--) {
        invfac[i - 1] = invfac[i] * i;
    }
    
    Z ans = 0;
    Z p = power(Z(2), P - 1 - B);
    for (int i = 0; i < A; i++) {
        ans += fac[B - 1 + i] * invfac[B - 1] * invfac[i] * p;
        p *= (P + 1) / 2;
    }
    std::cout << ans << "\n";
    
    return 0;
}
