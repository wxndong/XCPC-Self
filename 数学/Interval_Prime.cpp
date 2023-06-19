#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

// [模板] 区间筛素数
// get interval_prime of [L, R]
const int N = 1e6 + 10;
vector<i64> interval_prime(i64 L, i64 R) {
    vector<i64> prime;
    bitset<N> used(0), rused(0);
    
    int len = sqrt(R);
    for (int i = 2; i <= len; ++i) {
        if (!used[i]) {
            i64 x = i, y = max(x, x * (L / x));
            
            while (y <= R) {
                if (y - L >= 0 && y != x) {
                    rused[y - L] = true;
                }
                y = y + x;
            }
            
            for (int j = i + i; j <= len; j += i) {
                used[j] = true;
            }
        }
    }
    
    for (int i = 0; i <= R - L; ++i) {
        if (i + L >= 2 && !rused[i]) {
            prime.push_back(i + L);
        }
    }

    return prime;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int L, R;
    while (cin >> L >> R) {
        vector<i64> prime = interval_prime(L, R);

        i64 mi = 1E9, mx = -1E9, a, b, c, d;
        for (int i = 1; i < int(prime.size()); i++) {
            if (prime[i] - prime[i - 1] < mi) {
                mi = prime[i] - prime[i - 1], a = prime[i - 1], b = prime[i];
            }
            if (prime[i] - prime[i - 1] > mx) {
                mx = prime[i] - prime[i - 1], c = prime[i - 1], d = prime[i];
            }
        }
        if (mi == 1E9) {
            cout << "There are no adjacent primes.\n";
        } else {
            cout << a << "," << b << " are closest, " << c << "," << d << " are most distant.\n";
        }
    }

    return 0;
}