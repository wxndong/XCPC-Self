#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
 
using Real = i64;
using Point = complex<Real>;
// 叉乘
Real cross(const Point &a, const Point &b) {
    return (conj(a) * b).imag();
}
// 点乘
Real dot(const Point &a, const Point &b) {
    return (conj(a) * b).real();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(12);
    
    // For Example: define a point
    // Point TEST(x, y);

    return 0;
}
