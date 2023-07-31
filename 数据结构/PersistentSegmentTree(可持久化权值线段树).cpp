/*
    problem url : https://www.luogu.com.cn/problem/P3834
    求区间第k小
    注意返回值的接收，以及初始化build的root[0]
*/

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template<class Info>
struct PersistentSegmentTree {
    int n, idx = 0;
    vector<Info> root, ls, rs, sum;
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
        sum.assign(n * 32, Info());
        // 这里n的赋值需要注意下，以后改一下板子，否则感觉容易出现传入数组为0的情况
        assert(n >= 0);
        std::function <int(int, int, int)> build = [&](int p, int l, int r) {
            p = ++ idx;
            if (l == r) {
                return p;
            }
            int mid = l + r >> 1;
            ls[p] = build(ls[p], l, mid);
            rs[p] = build(rs[p], mid + 1, r);
            return p;
        };
        root[0] = build(0, 1, n);
    }
    int modify(int p, int pre, int l, int r, int v) {
        p = ++ idx;
        ls[p] = ls[pre];
        rs[p] = rs[pre];
        sum[p] = sum[pre] + 1;
        if (l == r) {
            return p;
        }
        int mid = l + r >> 1;
        if (v <= mid) {
            ls[p] = modify(p, ls[pre], l, mid, v);
        } else {
            rs[p] = modify(p, rs[pre], mid + 1, r, v);
        }
        return p;
    }
    int rangeQuery(int l, int r, int x, int y, int k) {
        if (l != r) {
            // 1~y左子树的sum - 1~(x - 1)左子树的sum，注意传入时x为x - 1故这里不需要处理
            int num = sum[ls[y]] - sum[ls[x]];
            int mid = l + r >> 1;
            if (num >= k) { // 若左子树大于k，则一定在左子树中否则去右子树寻找k - num
                return rangeQuery(l, mid, ls[x], ls[y], k);
            } else {
                return rangeQuery(mid + 1, r, rs[x], rs[y], k - num);
            }
        }
        return l;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector b = a;
    sort(b.begin() + 1, b.begin() + 1 + n);
    int m = unique(b.begin() + 1, b.begin() + 1 + n) - b.begin() - 1;

    auto get = [&](i64 x) -> i64 {
        return lower_bound(b.begin() + 1, b.begin() + 1 + m, x) - b.begin();
    };

    PersistentSegmentTree<int> seg(b);

    for (int i = 1; i <= n; i++) {
        seg.root[i] = seg.modify(seg.root[i], seg.root[i - 1], 1, m, get(a[i]));
    }
    for (int i = 1; i <= q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << b[seg.rangeQuery(1, m, seg.root[l - 1], seg.root[r], k)] << "\n";
    }
    return 0;
}