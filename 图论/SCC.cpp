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

/*
    例题2:https://vjudge.net/problem/POJ-1236
*/
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 100 + 10;

vector<int> edge[N];
int dfn[N], low[N], dfncnt;
int stk[N], in_stk[N], tp;
int scc[N], sc;
int sz[N];
int in[N], out[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++ dfncnt;
    stk[++ tp] = u, in_stk[u] = 1;

    for (int i = 0; i < int(edge[u].size()); i++) {
        if (!dfn[edge[u][i]]) {
            tarjan(edge[u][i]);
            low[u] = min(low[u], low[edge[u][i]]);
        } 
        else if (in_stk[edge[u][i]]) {
            low[u] = min(low[u], dfn[edge[u][i]]);
        }
    }

    if (low[u] == dfn[u]) {
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
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int to;
        while (cin >> to && to != 0) {
            edge[i].push_back(to);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < int(edge[i].size()); j++) {
            if (scc[i] != scc[edge[i][j]]) {
                in[scc[edge[i][j]]] ++;
                out[scc[i]] ++;
            }
        }
    }

    int res1 = 0, res2 = 0;
    for (int i = 1; i <= sc; i++) {
        if (in[i] == 0) res1 ++;
        if (out[i] == 0) res2 ++;
    }

    if (sc == 1) {
        cout << sc << "\n" << 0;
    } else {
        cout << res1 << "\n" << max(res1, res2); // 入读为0的联通分量的个数即为SubA的答案，SubB若让所有的联通，即需要让所有的连通分量都联通，取入度和出度为0的max
    }
    
    
    return 0;
}

/*
    2、使用Kosaraju找SCC（强连通分量）
    这个似乎是useless? 先贴个只能计算联通分量个数的板子，以后真碰到了再来写
    
*/#include <bits/stdc++.h>
#define debug cerr << "Bug This Line\n"; exit(0);

using namespace std;
using i64 = long long;

constexpr int N = 5E4 + 10;

vector<int> g[N], rg[N];
vector<int> vs;
int used[N], comp[N], belong[N]; // comp 表示强联通分量的编号
int n, m;

void add_edge (int from, int to) {
    g[from].push_back(to);
    rg[to].push_back(from);
}
 
void dfs (int u) {
    used[u] = 1;
    for (auto v : g[u]) {
        if (!used[v]) {
            dfs(v);
        }
    }
    vs.push_back(u);
}
 
void rdfs (int u, int k) {
    used[u] = 1;
    belong[u] = k;
    for (auto v : rg[u]) {
        if (!used[v]) {
            rdfs(v, k);
        }
    }
}
 
int scc() {
    memset(used, 0, sizeof(used));
    vs.clear();
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }

    memset(used, 0, sizeof(used));
    int k = 0;
    for (int i = int(vs.size()) - 1; i >= 0; i--) {
        if (!used[vs[i]]) {
            rdfs(vs[i], k ++);
        }
    }

    return k;
}
 

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    while (m --) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    int ans = scc();
    int source = 1, sum = 0;
    for (int i = 1; i <= n; i++) {
        if (belong[i] == ans - 1) { // 找到最后一个联通分量，1)为什么是最后一个联通分量？zhelibuhui2)为什么是ans - 1？ 因为k从0开始统计联通分量的个数
            source = i;
            sum ++;
        }
    }

    memset(used, 0, sizeof(used));
    rdfs(source, 1);

    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            cout << 0; return 0;
        }
    }
    cout << sum;

    return 0;
}