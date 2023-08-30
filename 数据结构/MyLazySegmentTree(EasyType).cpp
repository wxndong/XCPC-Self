/**
 * 关于这个模板的注释 last update : 2023/7/25 19:26
 * 
 * 1) 变量解释 : 
 * info : 所维护的信息 | tag : lazy tag懒标记 
 * l, r : 线段树左右端点 | x, y : 每次操作的左右端点
 * p : 每个块的编号  
 *     
 * 2) 函数解释 : 
 * build 递归建树, 需要开4n + 5空间
 * push : 下传lazy tag | pull : 拉回子节点的值来更新自己
 * modify : 区间修改
 * rangeQuery : 区间查询
 * 
 * 3) 模板缺陷 : 
 * 未能够实现维护指定类型如tuple, pair等的高效可移植性模板, 待更新
 * 
 * 4) 小声bb : 
 * 大佬们的码力都tql, 看到一个题目就能想到如何维护, 我等菜b只能抄板子
*/

// problem url : https://www.luogu.com.cn/problem/P3372
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template<class Info>
struct LazySegmentTree {
    int n;
    vector<Info> info, tag;
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
        tag.assign(4 << __lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (l == r) {
                info[p] = init_[l];
                return; // don't forget return here
            }
            int mid = (l + r) / 2;
            build(2 * p, l, mid);
            build(2 * p + 1, mid + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, int l, int r, const Info &v) {
        tag[p] = tag[p] + v;
        info[p] = info[p] + v * (r - l + 1);
    }
    void push(int p, int l, int r) {
        int mid = (l + r) / 2;
        apply(2 * p, l, mid, tag[p]);
        apply(2 * p + 1, mid + 1, r, tag[p]);
        tag[p] = Info();
    }
    void modify(int p, int l, int r, int x, int y, const Info &v) { // 这个是区间修改
        if (x <= l && r <= y) {
            apply(p, l, r, v);
            return;
        }
        push(p, l, r);
        int mid = (l + r) / 2;
        if (x <= mid) {
            modify(2 * p, l, mid, x, y, v);
        }
        if (y > mid) {
            modify(2 * p + 1, mid + 1, r, x, y, v);
        }
        pull(p);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (r < x || y < l) {
            return Info();
        }
        if (x <= l && r <= y) {
            return info[p];
        }
        int mid = (l + r) / 2;
        push(p, l, r);
        return rangeQuery(2 * p, l, mid, x, y) + rangeQuery(2 * p + 1, mid + 1, r, x, y);
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
            cout << seg.rangeQuery(1, 1, n, x, y) << "\n";
        }
    }

    return 0;
}
