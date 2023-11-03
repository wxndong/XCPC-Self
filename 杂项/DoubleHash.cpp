/*
    精简版基础功能的双哈希板子,
    优点是方便更改, 缺点是常数比较大，
    注意: 使用时string下标需要从1开始
    problem url : https://ac.nowcoder.com/acm/contest/64384/D
*/
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using pii = pair<int, int>;

constexpr int MOD[] = {int(1E9 + 7), int(998244353)};
constexpr int BASE[] = {131, 13331};

template<typename T>
struct MyDoubleHash {
    int n;
    std::vector<std::array<T, 2> > h, p;
    MyDoubleHash(string s) {
        n = s.size() - 1;
        h.resize(n + 1);
        p.resize(n + 1);
        p[0] = {1, 1};
        for (int i = 1; i <= n; i++) {
            for (auto z : {0, 1}) {
                p[i][z] = 1LL * p[i - 1][z] * BASE[z] % MOD[z];
                h[i][z] = (1LL * h[i - 1][z] * BASE[z] + s[i]) % MOD[z];
            }
        }
    }
    pii get(int l, int r) {
        array<T, 2> t;
        for (auto z : {0, 1}) {
            t[z] = (h[r][z] - 1LL * h[l - 1][z] * p[r - l + 1][z]) % MOD[z];
            if (t[z] < 0) {
                t[z] = t[z] + MOD[z];
            }
        }
        return make_pair(t[0], t[1]);
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, m;
    cin >> n >> k >> m;

    string str;
    cin >> str;
    str = " " + str;

    MyDoubleHash<int> s(str);
    map<pii, pii> f;

    for (int i = 1; i + k - 1 <= n; i++) {
        auto t = s.get(i, i + k - 1);
        if (f[t].first == 0 || f[t].first < i) {
            f[t].second ++;
            f[t].first = i + k - 1;
        }
    }

    int ans = 0;
    for (auto [_, g] : f) {
        if (g.second == m) {
            ans ++;
        }
    }
    cout << ans << "\n";

    return 0;
}