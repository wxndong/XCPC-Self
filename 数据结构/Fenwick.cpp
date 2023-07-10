/*
    此版本为不带O(n)建树的版本
    学习的巨佬的 https://loj.ac/s/1815705
*/
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

struct FenwickTree {
    int n;
    vector<i64> tr1, tr2;
    FenwickTree (int _n) : n(_n + 1) {
        tr1.assign(_n + 1, 0), tr2.assign(_n + 1, 0);
    }
    i64 lowbit(i64 x) {
        return x & -x;
    }
    void modify(int idx, i64 val) {
        i64 val_1 = idx * val;
        while (idx <= n) {
            tr1[idx] += val; tr2[idx] += val_1;
            idx += lowbit(idx);
        }
    }
    i64 query(const vector<i64> &tr, i64 idx) {
        i64 sum = 0;
        while (idx) {
            sum += tr[idx];
            idx -= lowbit(idx);
        }
        return sum;
    }
    void modify1(int l, int r, i64 val) {
        modify(l, val);
        modify(r + 1, -val);
    }
    i64 query1(int l, int r) {
        i64 sum1 = (1 + r) * query(tr1, r) - l * query(tr1, l - 1);
        i64 sum2 = query(tr2, r) - query(tr2, l - 1);
        return sum1 - sum2;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    return 0;
}