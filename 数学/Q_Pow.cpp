#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using d64 = long double;

/*
    矩阵快速幂模板
    注意区分k和n，一般为读入时的想要得到的第k项，而这里为了防止出现歧义一般不用n
    注意N需要自己根据题目设置，即N为你设置的矩阵大小，需要根据不同的题目来更改
    每次检查N，k，MOD，以及传入时k需要减少多少(求base的多少次幂)
    change 2023-7-14 为了安全，删除掉了所有函数中的& 
*/
constexpr int N = 2; // N不能1e3以上，会爆... 矩阵的大小，一般稍微开大一些
constexpr int MOD = 1E9 + 7; // 模数

struct matrix {
    i64 x[N + 5][N + 5]; // 注意这里要稍微开大一些防止越界
    matrix() {memset(x, 0, sizeof (x) ); } // 构建矩阵的同时设置成全0
};

matrix multiply(matrix a, matrix b, i64 mod) { // c[i][j] = a[i][k] * b[k][j];
    matrix c;
    for (int i = 1; i <= N; i++) 
        for (int j = 1; j <= N; j++) 
            for (int k = 1; k <= N; k++) 
                c.x[i][j] = (c.x[i][j] + a.x[i][k] * b.x[k][j]) % mod; // 记得取模
    return c;
}   

matrix m_pow(matrix a, i64 k, i64 mod) {
    matrix ans;
    for (int i = 1; i <= N; i++) ans.x[i][i] = 1; // 构建一个单位矩阵 其中N为你设置的矩阵大小
    while (k) { // 和普通的快速幂一样
        if (k & 1) ans = multiply(ans, a, mod);
        a = multiply(a, a, mod);
        k >>= 1;
    }
    return ans;
}

signed main() {
    i64 k; 

    matrix base, ans;
    // 构造base 和 ans
    ans.x[1][1] = 1, ans.x[2][1] = 1;
    base.x[1][1] = 1, base.x[1][2] = 1;
    base.x[2][1] = 1, base.x[2][2] = 0;
    // 这个k - 2是因为一般给你f[1] 和 f[2] 故求f[3] 只需要base^(3-2) = base 矩阵
    // 然后将 base * ans, 一般base在左边
    base = m_pow(base, k - 2, MOD); 
    ans = multiply(base, ans, MOD);
    
    return 0;
}

/*
    下面是正常快速幂模板
*/
#include <bits/stdc++.h>

using namespace std;

// get a ^ k 
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

// get a ^ k % p
template <typename T>
T q_mod(T a, T k, T p) {
    // a %= p // 注意若a大于p, 则应该先对a%p
    T ans = 1;
    while (k) {
        if (k & 1) ans = ans * a % p;
        k >>= 1;
        a = a * a % p;
    }   
    return ans % p;
}
