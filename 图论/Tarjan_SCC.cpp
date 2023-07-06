// url : https://loj.ac/p/10091

#include <bits/stdc++.h>
#define debug cerr << "Bug This Line\n"; exit(0);

using namespace std;
using i64 = long long;

constexpr int N = 5E4 + 10;

vector<int> edge[N];
int dfn[N], low[N], dfncnt;
int stk[N], in_stk[N], tp;
int scc[N], sc; // 记录每个节点i属于的scc的编号，sc代表scc的个数
int sz[N]; // 记录每个强连通分量的大小
int out[N]; // 出度

void tarjan(int u) {
    dfn[u] = low[u] = ++ dfncnt; // 注意编号从1开始
    stk[++ tp] = u, in_stk[u] = 1;

    for (int i = 0; i < int(edge[u].size()); i++) {
        auto v = edge[u][i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        sc ++;
        while (stk[tp] != u) {
            scc[stk[tp]] = sc;
            sz[sc] ++;
            in_stk[stk[tp]] = 0;
            tp --;
        }
        scc[stk[tp]] = sc;
        sz[sc] ++;
        in_stk[stk[tp]] = 0;
        tp --;
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
    }
    // 缩点形成强连通
    for (int i = 1; i <= n; i++) {
        if (!scc[i]) {
            tarjan(i);
        }
    }
    // 统计每个强连通分量的出度
    for (int i = 1; i <= n; i++) {
        for (auto v : edge[i]) {
            if (i != v && scc[i] != scc[v]) { // 不在一个强连通分量中
                out[scc[i]] ++;
            }
        }
    }
    // 统计出度为0的强连通分量的个数即为答案，注意处理多个强联通分量的出度为0的情况
    int cnt = 0, ans = 0;
    for (int i = 1; i <= sc; i++) {
        if (out[i] == 0) {
            cnt ++;
            ans = sz[i];
        }
        if (cnt > 1) {
            ans = 0;
            break;
        }
    }
    cout << ans;

    return 0;
}
