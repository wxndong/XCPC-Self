// problem url : https://ac.nowcoder.com/acm/contest/57355/M
#include <bits/stdc++.h>

using i64 = long long;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

void solve() {
    i64 A, B, x;
    std::cin >> A >> B >> x;
    
    if (A > B) {
        std::swap(A, B);
    }
    
    i64 u, v;
    i64 g = exgcd(A, B, u, v);
    A /= g, B /= g;
    if (x % g != 0) {
        std::cout << -1 << "\n";
        return;
    }
    x /= g;
    
    u = (u * x % B + B) % B;
    v = (x - u * A) / B;
    
    i64 ans = 1E18;
    if (v >= 0) {
        ans = std::min(ans, 2 * (u + v));
    }
    u -= B;
    v += A;
    
    ans = std::min(ans, 2 * (-u + v) - 1);
    
    v = (v % A + A) % A;
    u = (x - v * B) / A;
    if (u >= 0) {
        ans = std::min(ans, 2 * (u + v));
    }
    v -= A;
    u += B;
    
    ans = std::min(ans, 2 * (u - v) - 1);
    
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
