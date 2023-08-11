/**
 * 这个是线段树标记永久化的板子
*/

// problem url : https://www.luogu.com.cn/problem/P3372
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template<class Info>
struct LazySegmentTree {
    int n;
    vector<Info> info, mark;
    template<class T>
    LazySegmentTree(vector<T> init_) {
        init(init_);
    }
    template<class T>
    void init(vector<T> init_) {
        n = init_.size() - 1; // 这个模板我设置成下标从1开始, 传进来是n + 1, 第0位也算一个, 所以n需要-1
        // 这里n的赋值需要注意下，以后改一下板子，否则感觉容易出现传入数组为0的情况
        assert(n >= 0);
        info.assign(4 << __lg(n), Info());
        mark.assign(4 << __lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (l == r) {
                info[p] = init_[l];
                return; // don't forget return here
            }
            int mid = (l + r) / 2;
            build(2 * p, l, mid);
            build(2 * p + 1, mid + 1, r);
            info[p] = info[2 * p] + info[2 * p + 1];
        };
        build(1, 1, n);
    }
    void modify(int p, int l, int r, int x, int y, const Info &v) {
        if (x <= l && r <= y) {
            mark[p] = mark[p] + v; // 记录永久化标记
            info[p] = info[p] + (r - l + 1) * v;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid) {
            modify(2 * p, l, mid, x, y, v);
        }
        if (y > mid) {
            modify(2 * p + 1, mid + 1, r, x, y, v);
        }
        info[p] = info[2 * p] + info[2 * p + 1] + (r - l + 1) * mark[p]; // pull 回来永久化标记
    }
    Info rangeQuery(int p, int l, int r, int x, int y, Info ad) {
        if (r < x || y < l) {
            return Info();
        }
        if (x <= l && r <= y) {
            return info[p] + (r - l + 1) * ad; // 加上永久化的标记
        }
        int mid = (l + r) / 2;
        return rangeQuery(2 * p, l, mid, x, y, ad + mark[p]) + rangeQuery(2 * p + 1, mid + 1, r, x, y, ad + mark[p]); // 永久化标记传下去
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
   
    int n, m;
    cin >> n >> m;

    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];    
    }

    LazySegmentTree<i64> seg(a);
        
    while (m --) {
        int op, x, y;
        i64 v;
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> v;
            seg.modify(1, 1, n, x, y, v);
        } else {
            cin >> x >> y;
            cout << seg.rangeQuery(1, 1, n, x, y, 0) << "\n";
        }
    }

    return 0;
}
