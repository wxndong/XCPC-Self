#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int> > > edge(n + 1);
    while (m --) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].push_back({w, v}); // 有向图加单边 无向图再加一条反向
    }

    vector<int> dist(n + 1, -1);    
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    q.push({dist[1] = 0, 1});
    while (not q.empty()) {
        auto t = q.top();
        q.pop();
        auto u = t.second;
        if (dist[u] != t.first) { // 这句话的意思其实是，没经过松弛的那些点不会再次进入
            continue;
        }
        for (auto [val, v] : edge[u]) {
            if (dist[v] == -1 || dist[v] > dist[u] + val) {
                q.push({dist[v] = dist[u] + val, v});
            }
        }
    }    
    cout << dist[n] << "\n";
    
    return 0;
}