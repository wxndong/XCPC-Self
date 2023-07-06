// Lowest Common Ancestor (LCA)
// problem url : https://www.luogu.com.cn/problem/P3379
/*
    1、倍增方法
    建立O(nlogn) 单次查询O(logn)
*/
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int N = 5E5 + 10;
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

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    dfs(s, 0);

    while (m --) {
        int u, v;
        cin >> u >> v;
        cout << LCA(u, v) << "\n";
    }

    return 0;
}
/*
    2、Tarjan方法
    建立O(n) m次查询共 ~ O(n + m)
*/
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int N = 5E5 + 10;

vector<int> edge[N];
vector<pair<int, int> > query[N];
int fa[N], ans[N], vis[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]); 
}

void Tarjan(int u) {
    vis[u] = 1;
    for (auto v : edge[u]) {
        if (!vis[v]) {
            Tarjan(v);
            fa[v] = u;
        }
    }

    for (auto [v, i] : query[u]) {
        if (vis[v]) {
            ans[i] = find(v);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, s;
    cin >> n >> m >> s;

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        query[u].push_back({v, i});
        query[v].push_back({u, i});
    }

    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }

    Tarjan(s);

    for (int i = 1; i <= m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
