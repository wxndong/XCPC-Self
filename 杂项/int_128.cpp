#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128_t;

inline void read(i128 &n){
    i128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    n = x * f;
}
inline void print(i128 n){
    if (n < 0) {
        putchar('-');
        n *= -1;
    }
    if (n > 9) print(n / 10);
    putchar(n % 10 + '0');
}

signed main() {

    return 0;
}