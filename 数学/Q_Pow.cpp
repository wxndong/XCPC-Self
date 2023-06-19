#include <bits/stdc++.h>

using namespace std;

// get a ^ b  
template <typename T>
T q_pow(T a, T k) {
    T ans = 1;
    while (k) {
        if (k & 1) ans = ans * a;
        k >>= 1;
        a = a * a;
    }
    return ans;
}

// get a ^ b % p
template <typename T>
T q_mod(T a, T k, T p) {
    T ans = 1;
    while (k) {
        if (k & 1) ans = ans * a % p;
        k >>= 1;
        a = a * a % p;
    }   
    return ans % p;
}

// get matrix ^ m % MOD
using ll = long long;
constexpr int N = 105; // N不能1e3以上，会爆...
constexpr int MOD = 1e9 + 7;
ll n, k;

struct matrix {
    ll x[N][N];
    matrix() {memset(x, 0, sizeof (x));} // 构建矩阵的同时设置成全0
};

matrix multiply(matrix &a, matrix &b) { // c[i][j] = a[i][k] * b[k][j];
    matrix c;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++) 
            for (int k = 1; k <= n; k++) 
                c.x[i][j] = (c.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD; // 记得取模
    return c;
}   

matrix m_pow(matrix &a, ll k) {
    matrix ans;
    for (int i = 1; i <= n; i++) ans.x[i][i] = 1; // 构建一个单位矩阵
    while (k) { // 和普通的快速幂一样
        if (k & 1) ans = multiply(ans, a);
        a = multiply(a, a);
        k >>= 1;
    }
    return ans;
}

int main() {


    return 0;
}
