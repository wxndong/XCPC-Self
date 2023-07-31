// problem url : https://www.luogu.com.cn/problem/P3919

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int N = 1E6 * 32;

template<class Info>
struct PersistentSegmentTree {
    int n, idx = 0;
    vector<Info> root, ls, rs, val;
    template<class T>
    PersistentSegmentTree(vector<T> _info) {
        init(_info);
    }
    template<class T>
    void init(vector<T> _info) {
        // 空间不能开太小 32 * n 似乎可以
        this->n = _info.size() - 1;
        root.assign(n * 32, Info());
        ls.assign(n * 32, Info());
        rs.assign(n * 32, Info());
        val.assign(n * 32, Info());
        // 这里n的赋值需要注意下，以后改一下板子，否则感觉容易出现传入数组为0的情况
        assert(n >= 0);
        std::function <int(int, int, int)> build = [&](int p, int l, int r) {
            p = ++ idx;
            if (l == r) {
                val[p] = _info[l];
                return idx;
            }
            int mid = l + r >> 1;
            ls[p] = build(ls[p], l, mid);
            rs[p] = build(rs[p], mid + 1, r);
            return p;
        };
        root[0] = build(0, 1, n);
    }
    int clone(int p) {
        idx ++;
        ls[idx] = ls[p];
        rs[idx] = rs[p];
        val[idx] = val[p];
        return idx;
    }
    int modify(int p, int l, int r, int x, int v) {
        p = clone(p);
        if (l == r) {
            val[p] = v;
            return p;
        }
        int mid = l + r >> 1;
        if (x <= mid) {
            ls[p] = modify(ls[p], l, mid, x, v);
        } else {
            rs[p] = modify(rs[p], mid + 1, r, x, v);
        }
        return p;
    }
    int query(int p, int l, int r, int x) {
        if (l == r) {
            return val[p];
        }
        int mid = l + r >> 1;
        if (x <= mid) {
            return query(ls[p], l, mid, x);
        } else {
            return query(rs[p], mid + 1, r, x);
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    PersistentSegmentTree<int> seg(a);

    for (int i = 1; i <= m; i++) {
        int id, op, x, val;
        cin >> id >> op >> x;
        if (op == 1) {
            cin >> val;
            seg.root[i] = seg.modify(seg.root[id], 1, n, x, val);
        } else {
            cout << seg.query(seg.root[id], 1, n, x) << "\n";
            seg.root[i] = seg.root[id];
        }
    }
    return 0;
}