// url : https://loj.ac/p/10091
/*
    1、使用Tarjan找SCC（强连通分量）

*/

/*
    例题1:https://loj.ac/p/10091
*/
#include <bits/stdc++.h>
#define debug cerr << "Bug This Line\n"; exit(0);

using namespace std;
using i64 = long long;

constexpr int N = 5E4 + 10;

vector<int> edge[N];
int dfn[N], low[N], dfncnt;
int flag[N];
int res;
int vis[N];

void tarjan(int u, int fa) {
    vis[u] = 1;
    dfn[u] = low[u] = ++ dfncnt; // 注意编号从1开始
    int child = 0;
    for (auto v : edge[u]) {
        if (!vis[v]) {
            child ++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (u != fa && low[v] >= dfn[u] && !flag[u]) {
                flag[u] = 1;
                res ++;
            }
        } else if (v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u] && child >= 2 && !flag[u]) {
        flag[u] = 1;
        res ++;
    }
}   

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    while (m --) {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfncnt = 0;
            tarjan(i, i);
        }
    }

    cout << res << "\n";
    for (int i = 1; i <= n; i++) {
        if (flag[i]) {
            cout << i << " ";
        }
    }

    return 0;
}