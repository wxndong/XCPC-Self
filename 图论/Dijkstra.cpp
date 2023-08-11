/*
    我的习惯是为了优先队列方便，先放边再放点
*/
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr i64 inf = 1E18;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<i64, int> > > adj(n + 1);
    while (m --) {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v}); // 有向图加单边 无向图再加一条反向
    }

    vector<i64> dist(n + 1, inf);  

    auto dijkstra = [&](int source) -> void {
        // 千万注意边权放在pair的first!!!
        priority_queue<pair<i64, int>, vector<pair<i64, int> >, greater<pair<i64, int> > > pq; 
        vector<bool> vis(n + 1, false);
        pq.push({dist[source] = 0LL, source});
        while (!pq.empty()) {
            // auto [dis, u] = pq.top(); // cpp17 only
            int u = pq.top().second;
            pq.pop();
            if (vis[u] == true) {
                continue;
            }
            vis[u] = true;
            // for (auto [val, v] : adj[u]) { // cpp17 only
            for (auto t : adj[u]) {
                int v = t.second;
                i64 val = t.first;
                if (dist[v] > dist[u] + val) {
                    pq.push({dist[v] = dist[u] + val, v});
                }
            }
        }    
    };
    dijkstra(1);

    cout << dist[n] << "\n";
    
    return 0;
}