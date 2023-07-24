/*
    双dfs法
    优点:可以记录直径的起点，重点，再配合一个dfs可以求出直径上的每一个点
    缺点:遇到副边权的树就GG
*/

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s;
    cin >> n >> s;

    vector<vector<pair<int, int> > > edge(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
    }

    // 2次dfs找到树的直径
    int c = 0;
    vector<int> p(n + 1, 0);
    vector<int> dep(n + 1, 0);
    vector<bool> vis(n + 1, false);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        p[u] = fa;
        for (auto to : edge[u]) {
            auto [v, w] = to;
            if (v == fa || vis[v]) {
                continue;
            }
            dep[v] = dep[u] + w;
            if (dep[v] > dep[c]) {
                c = v;
            }
            self(self, v, u);
        }
    };

    int cnt = 0;
    vector<int> dia(n + 1, 0);
    vector<int> pres(n + 1, 0);
    auto get_diameter = [&]() -> void {
        dfs(dfs, 1, 0);
        dep[c] = 0;
        dfs(dfs, c, 0);
        for (int u = c; u; u = p[u]) {
            dia[++ cnt] = u;
            pres[cnt] = dep[u];
        }
        reverse(dia.begin() + 1, dia.begin() + cnt + 1);
        reverse(pres.begin() + 1, pres.begin() + cnt + 1);
    };

    get_diameter();

    return 0;
}

/***
 * 二者区别是向下dfs的时机
 * 
 * **/


/*
    树形dp 求树的直径
    优点:可以处理负边权的树
    缺点:真的只能求一个树的直径的长度，其他的求不出
    记得赋dep初值 0 
*/

    int diameter = 0;
    vector<int> dep(n + 1, 0);
    auto tree_dp = [&](auto &&self, int u, int fa) -> void {
        for (auto &[v, cost] : adj[u]) { // PS(3)注意使用&才能更改auto调用的值
            if (v == fa) continue;
            self(self, v, u);
            diameter = max(LB, dep[u] + dep[v] + cost);
            dep[u] = max(dep[u], dep[v] + cost);
        }
    };

    dep.assign(n + 1, 0); // 别忘了dep赋初值PS(1)
    tree_dp(tree_dp, 1, 0);
