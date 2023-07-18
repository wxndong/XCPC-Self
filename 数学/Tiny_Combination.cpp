#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr i64 MOD = 998244353;
constexpr int N = 1E6 + 10;

struct Comb {
    vector<i64> fac;
    Comb(int n) : fac(n + 1) {
        fac[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i % MOD;
        }
    }

    i64 power(i64 a, i64 n, i64 p) { // 快速幂 a^n % p
        i64 ans = 1;
        while (n) {
            if (n & 1) ans = ans * a % p;
            a = a * a % p;
            n >>= 1;
        }
        return ans;
    }

    i64 Inv(i64 a, i64 b) { // 费马小定理求逆元
        return power(a, b - 2, b);
    }

    i64 C(i64 a, i64 b) { // 计算C(a, b)
        return fac[a] * Inv(fac[b], MOD) % MOD * Inv(fac[a - b], MOD) % MOD;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    Comb Z(N + 1);

    cout << Z.C(m, 2) * 2 % MOD<< "\n";

    return 0;
}