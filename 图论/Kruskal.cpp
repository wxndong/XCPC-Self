// problem url : https://www.luogu.com.cn/problem/P3366
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int N = 2E5 + 10;
int n, m;

// 并查集
struct DSU {
    std::vector<int> p, siz;
    DSU(int n) : p(n + 1), siz(n + 1, 1) {
        std::iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        p[y] = x;
        return true;
    }
    int size(int x) {
        return siz[find(x)];
    }
};

// 存储Kruskal使用的图
struct Edge {
    int u, v, w;
}Kedge[N << 1];

void Kruskal() {
    DSU dsu(n);
    int ans = 0, cnt = 0;
    sort(Kedge + 1, Kedge + 1 + m, [](const Edge &x, const Edge &y) {
        return x.w < y.w;
    });

    for (int i = 1; i <= m; i++) {
        int u = dsu.find(Kedge[i].u), v = dsu.find(Kedge[i].v);
        if (dsu.same(u, v)) {
            continue;
        }

        dsu.merge(u, v);
        ans += Kedge[i].w;
        cnt ++;
        if (cnt == n - 1) {
            break;
        }
    }
    if (cnt == n - 1) {
        // 连通图
        cout << ans << "\n";
    } else {
        // 非连通图
        cout << "orz\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        cin >> Kedge[i].u >> Kedge[i].v >> Kedge[i].w;
    }

    Kruskal();

    return 0;
}