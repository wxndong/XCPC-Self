// 很好的讲解 : https://www.bilibili.com/video/BV1D5411E7nZ/?spm_id_from=333.337.search-card.all.click&vd_source=862d3e2d6f184ff18a41da7b7d03ef97

/*
    1、点差分
    // 在树上求前缀和
    int dfs_tree(int root, int fno) {
        for (auto son : edge[root]) {
            if (son != fno) {
                dif[root] += dfs_tree(son, root);
            }
        }
        ans = max(ans, dif[root]); // 用来求每个点的最大值，洛谷那个树上差分（点）板子题 url : https://www.luogu.com.cn/problem/P3128
        return dif[root];
    }
    // 树上差分
    dif[u] ++, dif[v] ++, dif[lca] --, dif[fa[lca][0]] --;
*/ 


// Lowest Common Ancestor (LCA)
// problem url : https://www.luogu.com.cn/problem/P3379

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int N = 5E5 + 10;
int dif[N], ans = -1;
int dep[N], fa[N][31];
vector<int> edge[N];

void dfs(int root, int fno) {
    fa[root][0] = fno;
    dep[root] = dep[fa[root][0]] + 1;
    // 想要求2^i级祖先，我们可以利用求出2^(i-1)级祖先，然后再求2^(i-1)级祖先的2^(i-1)级祖先来达到目的
    for (int i = 1; i < 31; i++) {
        fa[root][i] = fa[fa[root][i - 1]][i - 1];
    }
    
    for (int i = 0; i < int(edge[root].size()); i++) {
        // 注意判掉父结点
        if (edge[root][i] != fno) {
            dfs(edge[root][i], root);
        }
    }
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    // 把二者的深度调整一致
    int gap = dep[u] - dep[v];
    for (int i = 0; gap >= 1; i ++, gap >>= 1) {
        if (gap & 1) {
            u = fa[u][i];
        }
    }

    if (u == v) {
        return u;
    }
    // u, v 同时上跳，直到他们的父亲结点相同，那么我们返回这个父结点即可
    for (int i = 30; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i], v = fa[v][i];
        }
    }
    return fa[u][0];
}

int dfs_tree(int root, int fno) {
    for (auto son : edge[root]) {
        if (son != fno) {
            dif[root] += dfs_tree(son, root);
        }
    }
    ans = max(ans, dif[root]);
    return dif[root];
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    dfs(1, 0);

    while (m --) {
        int u, v;
        cin >> u >> v;
        int lca = LCA(u, v);
        dif[u] ++, dif[v] ++, dif[lca] --, dif[fa[lca][0]] --;
    }

    dfs_tree(1, 0);
    cout << ans;

    return 0;
}

/*
    2、边差分
    权值下放，因此每个节点的权值就是它子树的和
    预处理时需要开个数组记录每个点对应的边，一般来说记录其通向直接父节点的边

    1) 需要读入的时候使用idx，记录每两个点相连的边的编号i，为下一步做准备
    2) 需要在dfs时候构造出每个点（root）和他父亲节点相连的边的编号edge_ver[root]

    // 差分操作
    dif[i - 1] ++, dif[i] ++; 
    dif[LCA(i - 1, i)] -= 2;
*/ 



// Lowest Common Ancestor (LCA)
// problem url : https://www.luogu.com.cn/problem/P3379

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int N = 2E5 + 10;
int dif[N];
int dep[N], fa[N][31], c[N][3], edge_ver[N], cnt[N]; // edge_ver[root] 连接root和它的父节点的边的编号， 设置edge_ver[0] = -1;
vector<int> edge[N], idx[N]; // edge -> 点点集合 idx -> 两点之间的边的编号

void dfs(int root, int fno) {
    fa[root][0] = fno;
    dep[root] = dep[fa[root][0]] + 1;
    // 想要求2^i级祖先，我们可以利用求出2^(i-1)级祖先，然后再求2^(i-1)级祖先的2^(i-1)级祖先来达到目的
    for (int i = 1; i < 31; i++) {
        fa[root][i] = fa[fa[root][i - 1]][i - 1];
    }
    
    edge_ver[root] = -1;
    for (int i = 0; i < int(edge[root].size()); i++) {
        // 注意判掉父结点
        if (edge[root][i] != fno) {
            dfs(edge[root][i], root);
        } else {
        // edge_ver记录的是连接root和它的父节点的边的编号
            edge_ver[root] = idx[root][i];
        }
    }
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    // 把二者的深度调整一致
    int gap = dep[u] - dep[v];
    for (int i = 0; gap >= 1; i ++, gap >>= 1) {
        if (gap & 1) {
            u = fa[u][i];
        }
    }

    if (u == v) {
        return u;
    }
    // u, v 同时上跳，直到他们的父亲结点相同，那么我们返回这个父结点即可
    for (int i = 30; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i], v = fa[v][i];
        }
    }
    return fa[u][0];
}

int dfs_tree(int root) {
    for (auto son : edge[root]) {
        if (son != fa[root][0]) {
            dif[root] += dfs_tree(son);
        }
    }
    if (edge_ver[root] != -1) cnt[edge_ver[root]] = dif[root];
    return dif[root];
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v >> c[i][1] >> c[i][2];
        edge[u].push_back(v); edge[v].push_back(u);
        idx[u].push_back(i); idx[v].push_back(i);
    }

    dfs(1, 0);

    // make tree dif
    for (int i = 2; i <= n; i++) {
        dif[i - 1] ++, dif[i] ++; 
        dif[LCA(i - 1, i)] -= 2;
    }

    // get tree sum
    dfs_tree(1);

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += min(1LL * cnt[i] * c[i][1], 1LL * c[i][2]);
    }
    cout << ans;

    return 0;
}