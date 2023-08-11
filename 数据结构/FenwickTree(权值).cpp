/*
    FenwickTree(权值)版本，主要用作权值树状数组
    与常规的稍有不同，因为需要考虑出现值为0的，整体向左偏移一位
    这样可以避免离散化，节省一些代码量
    1) sum求0~(x-1)的和，若想要求0~x，则需要+a[x]
    2) rangeSum求l~(r-1)的和，若想要求l~r，则需要+a[r]
    3) kth求的是第k+1小
*/
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <typename T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) { // 0 ~ (x - 1)
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) { // l ~ (r - 1)
        return sum(r) - sum(l);
    }
    int kth(T k) { // 返回第k + 1小
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};

constexpr int N = 1 << 20; // 1E6

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    Fenwick<int> fen(N);

    return 0;
}