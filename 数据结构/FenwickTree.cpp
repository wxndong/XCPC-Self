/*
    Fenwick Tree 船新版本，目前主要用这个
    
    2023.7.28 modify2: 再次重构了下Fenwick板子
    这次板子纯纯滴缝合怪哈哈哈哈，但是实现了兼容区间查询和第k大的功能
    不过两种功能似乎需要开两棵树状数组，分别只能使用单点和区间
    
    维护第k大的代码如下
    注意下，如果要在其他地方调用fen的vector的a，记得写成fen.a，否则会调用错误
    贴个测试链接：https://www.luogu.com.cn/problem/P1908
*/
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <typename T>
struct Fenwick {
    int n;
    vector<T> a, b, origin;
    Fenwick (int _n = 0) {
        init(_n);
    }
    void init(int _n) {
        this->n = _n;
        a.assign(_n + 1, T()), b.assign(_n + 1, T()), origin.assign(_n + 1, T());
    }
    void add(int x, T v) {
        T v_1 = x * v;
        for (int i = x; i <= n; i += i & -i) {
            // 更新了一下，v_1只能是x * v,不能每次随着x更新
            a[i] += v; b[i] += v_1; origin[i] += v;
        }
    }
    T sum(const vector<T> &c, int x) {
        T ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += c[i]; 
        }
        return ans;
    }
    void rangeAdd(int l, int r, T v) {
        add(l, v);
        add(r + 1, -v);
    }
    T rangeSum(int l, int r) {
        // 这里更新了下，之前用的是(1 + r) * sum(tr1, r) - l * sum(tr1, l - 1)
        // 而实际上右侧是1 + l - 1，这次写开了方便以后理解
        T L = (1 + r) * sum(a, r) - (1 + l - 1) * sum(a, l - 1);
        T R = sum(b, r) - sum(b, l - 1);
        return L - R;
    }
    int kth(T k) { // 在下标从1~n的情况下，权值树状数组查询第 k 小
        int sum = 0, x = 0;
        for (int i = __lg(n); i >= 0; i--) {
            x += 1 << i;
            if (x >= n || sum + origin[x] >= k) {
                x -= 1 << i;
            } else {
                sum += origin[x];
            }
        }
        return x + 1;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    cin >> n;

    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector b = a;    
    sort(b.begin() + 1, b.begin() + 1 + n);
    int m = unique(b.begin() + 1, b.begin() + 1 + n) - b.begin() - 1;

    auto get = [&](i64 x) -> i64 {
        return lower_bound(b.begin() + 1, b.begin() + 1 + m, x) - b.begin();
    };

    Fenwick<i64> fen(m);
    i64 ans = 0;
    // 逆序枚举保证每次的i小于之前的j
    for (int j = n; j >= 1; j--) {
        // 查询之前插入到权值树状数组的是否存在小于当前a[i]的
        ans += fen.sum(fen.a, get(a[j]));
        // 把当前的a[i]插入权值树状数组
        fen.add(get(a[j]), 1);
    }
    for (int i = 1 ;i <= m; i++) {
        int kk = fen.kth(i);
        cerr << kk << " " << b[kk] << endl;
    }
    cout << ans << "\n";

    return 0;
}