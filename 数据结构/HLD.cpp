#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int N = 6E4 + 10;
int dep[N], fa[N], son[N], siz[N];
int top[N], dfn[N], rnk[N];
int cnt;
vector<int> adj[N];

// dfs1 求出dep fa son siz
void dfs1(int u) {
    siz[u] = 1;
    son[u] = -1;
    for (auto v : adj[u]) {
        if (v == fa[u]) {
            continue;
        }
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs1(v);
        siz[u] += siz[v];
        if (son[u] == -1 || siz[v] > siz[son[u]]) {
            son[u] = v;
        }
    }
}
// dfs2求出top dfn rnk
void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++ cnt;
    rnk[cnt] = u;
    if (son[u] == -1) {
        return;
    }
    dfs2(son[u], t);
    for (auto v : adj[u]) {
        // cerr << u << " " << v << endl;
        if (v != son[u] && v != fa[u]) {
            dfs2(v, v);
        }
    }
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    
    int n;
    cin >> n;

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs1(1);
    dfs2(1, 1);

    
    return 0;
}