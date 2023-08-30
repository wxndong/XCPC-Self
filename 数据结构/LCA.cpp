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
    lambda表达式写法
    >= cpp14 only
    // problem url : https://www.luogu.com.cn/problem/P3258

*/
    
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr i64 inf = 1E18;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    vector<vector<int> > adj(n + 1);

    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }
    
    vector<array<int, 33> > f(n + 1);
    vector<int> dep(n + 1, 0);
    auto dfs = [&](auto self, int u, int fa) -> void {
        f[u][0] = fa;
        dep[u] = dep[fa] + 1;
        for (int i = 1; i < 32; i++) {
            f[u][i] = f[f[u][i - 1]][i - 1];
        }
        for (auto v : adj[u]) {
            if (v == fa) {
                continue;
            }
            self(self, v, u);
            // cout << u << " " << v << endl;
        }
    };
    dfs(dfs, 1, 0);

    auto LCA = [&](int u, int v) -> int {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }   
        int gap = dep[u] - dep[v];
        for (int i = 0; gap > 0; gap >>= 1, i++) {
            if (gap & 1) {
                u = f[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = 30; i >= 0; i--) {
            if (f[u][i] != f[v][i]) {
                u = f[u][i];
                v = f[v][i];
            }
        }
        return f[u][0];
    };

    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= n - 1; i++) {
        int fa = LCA(a[i], a[i + 1]);
        ans[a[i]] ++;
        ans[a[i + 1]] ++;
        ans[fa] --;
        ans[f[fa][0]] --;
    }

    auto treeSum = [&](auto self, int u, int fa) -> void {
        for (auto v : adj[u]) {
            if (v == fa) {
                continue;
            }
            self(self, v, u);
            ans[u] += ans[v];
        }
    };
    treeSum(treeSum, 1, 0);

    for (int i = 2; i <= n; i++) {
        ans[a[i]] --;
    }
  
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
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
