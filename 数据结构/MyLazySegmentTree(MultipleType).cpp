/**
 * 这个题同时维护了加法和乘法两种运算
 * 同时定义了两种tag, addtag and multag需要考虑优先级问题
*/

// problem url : https://www.luogu.com.cn/problem/P3373
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template<class Info>
struct LazySegmentTree {
    int n, MOD;
    vector<Info> info, addtag, multag;
    template<class T>
    LazySegmentTree(vector<T> init_, int MOD_) {
        MOD = MOD_;
        init(init_);
    }
    template<class T>
    void init(vector<T> init_) {
        n = init_.size() - 1; // 这个模板我设置成下标从1开始, 传进来是n + 1, 第0位也算一个, 所以n需要-1
        info.assign(4 << __lg(n), Info());
        addtag.assign(4 << __lg(n), Info());
        multag.assign(4 << __lg(n), 1);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (l == r) {
                info[p] = init_[l];
                return; // don't forget return here
            }
            int mid = (l + r) / 2;
            build(2 * p, l, mid);
            build(2 * p + 1, mid + 1, r);
            pull(p);
            info[p] = info[p] % MOD;
        };
        build(1, 1, n);
    }
    void pull(int p) {
        info[p] = (info[2 * p] + info[2 * p + 1]) % MOD;
    }
    void push(int p, int l, int r) {
        int mid = (l + r) / 2;
        // 维护子节点的值
        info[2 * p] = (info[2 * p] * multag[p] + addtag[p] * (mid - l + 1) ) % MOD;
        info[2 * p + 1] = (info[2 * p + 1] * multag[p] + addtag[p] * (r - mid) ) % MOD;
        // 维护乘法tag
        multag[2 * p] = (multag[2 * p] * multag[p]) % MOD;
        multag[2 * p + 1] = (multag[2 * p + 1] * multag[p]) % MOD;
        // 维护加法tag
        addtag[2 * p] = (addtag[2 * p] * multag[p] + addtag[p]) % MOD;
        addtag[2 * p + 1] = (addtag[2 * p + 1] * multag[p] + addtag[p]) % MOD;
        // 恢复父节点tag为初始值
        multag[p] = 1;
        addtag[p] = 0;
    }
    void mul(int p, int l, int r, int x, int y, const Info &v) {
        if (l >= x && r <= y) {
            info[p] = (info[p] * v) % MOD;
            multag[p] = (multag[p] * v) % MOD;
            addtag[p] = (addtag[p] * v) % MOD;
            return;
        }
        push(p, l, r);
        int mid = (l + r) / 2;
        if (x <= mid) {
            mul(2 * p, l, mid, x, y, v);
        }
        if (y > mid) {
            mul(2 * p + 1, mid + 1, r, x, y, v);
        }
        pull(p);
    }
    void add(int p, int l, int r, int x, int y, const Info &v) {
        if (l >= x && r <= y) {
            addtag[p] = (addtag[p] + v) % MOD;
            info[p] = (info[p] + v * (r - l + 1)) % MOD;
            return;
        }
        push(p, l, r);
        int mid = (l + r) / 2;
        if (x <= mid) {
            add(2 * p, l, mid, x, y, v);
        }
        if (y > mid) {
            add(2 * p + 1, mid + 1, r, x, y, v);
        }
        pull(p);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (r < x || l > y) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p] % MOD;
        }
        int mid = (l + r) / 2;
        push(p, l, r);
        return (rangeQuery(2 * p, l, mid, x, y) + rangeQuery(2 * p + 1, mid + 1, r, x, y) ) % MOD;
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
   
    int n, m, p;
    cin >> n >> m >> p;

    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];    
    }

    LazySegmentTree<i64> seg(a, p);
    
    while (m --) {
        int op, x, y;
        i64 k;
        cin >> op >> x >> y;
        if (op == 1) {
            cin >> k;
            seg.mul(1, 1, n, x, y, k);
        } else if (op == 2) {
            cin >> k;
            seg.add(1, 1, n, x, y, k);
        } else {
            cout << seg.rangeQuery(1, 1, n, x, y) << "\n";
        }
    }

    return 0;
}
