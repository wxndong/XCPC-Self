#include <bits/stdc++.h>

using i64 = long long;
template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Info {
    int x = -1E9;
};

Info operator+(Info a, Info b) {
    return {std::max(a.x, b.x)};
}

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
    
    std::vector seg(2, std::vector(2, SegmentTree<Info>(n)));
    for (auto [l, r, t] : e) {
        r = std::lower_bound(v.begin(), v.end(), r) - v.begin();
        ans = std::max(ans, seg[!t][0].rangeQuery(0, r).x);
        ans = std::max(ans, seg[!t][1].rangeQuery(r, n).x + v[r]);
        seg[t][0].modify(r, Info{v[r] - l} + seg[t][0].rangeQuery(r, r + 1));
        seg[t][1].modify(r, Info{-l} + seg[t][1].rangeQuery(r, r + 1));
    }
    
    i64 sum = 0;
    for (int i = 0; i < n; i++) {
        sum += std::abs(a[i] - b[i]);
    }
    
    std::cout << sum - 2LL * ans << "\n";
    
    return 0;
}
