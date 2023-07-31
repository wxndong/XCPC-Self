/*
    jiangly's code
    单点修改，区间查询
    可以求权值树状数组的第k大
*/

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
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
    
    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int kth(T k) { // 在下标从1~n的情况下，jiangly 这个应该是求第k + 1小，注意返回的是离散化后的坐标
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

struct Info {
    int x = -1E9;
    Info &operator+=(Info b) & {
        x = std::max(x, b.x);
        return *this;
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        v.push_back(std::max(a[i], b[i]));
    }
    std::sort(v.begin(), v.end());
    
    std::vector<std::array<int, 3>> e;
    for (int i = 0; i < n; i++) {
        if (a[i] < b[i]) {
            e.push_back({a[i], b[i], 0});
        }
        if (a[i] > b[i]) {
            e.push_back({b[i], a[i], 1});
        }
    }
    
    std::sort(e.begin(), e.end(), std::greater<std::array<int, 3>>());
    
    int ans = 0;
    
    std::vector fen(2, std::vector(2, Fenwick<Info>(n)));
    for (auto [l, r, t] : e) {
        r = std::lower_bound(v.begin(), v.end(), r) - v.begin();
        ans = std::max(ans, fen[!t][0].sum(r).x);
        ans = std::max(ans, fen[!t][1].sum(n - r).x + v[r]);
        fen[t][0].add(r, Info{v[r] - l});
        fen[t][1].add(n - r - 1, Info{-l});
    }
    
    i64 sum = 0;
    for (int i = 0; i < n; i++) {
        sum += std::abs(a[i] - b[i]);
    }
    
    std::cout << sum - 2LL * ans << "\n";
    
    return 0;
}

