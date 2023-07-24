#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> p(n + 1, 0);
    vector<int> val(n + 1, 0);
    std::function<i64(i64)> find = [&](i64 x) -> i64 {
        if (x == p[x]) {
            return x;
        }
        i64 fa = p[x]; // 找到父亲节点
        p[x] = find(p[x]); // 让父亲节点指向祖先节点
        val[x] = (val[x] + val[fa] + 3) % 3; // 当前节点的值 = x到父亲节点的 + 父亲节点到祖先的
        return p[x];
    };


    return 0;
}