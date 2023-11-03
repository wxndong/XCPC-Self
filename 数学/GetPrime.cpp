/*
    欧拉筛O(n)
*/
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int N = 1E8 + 10;
 
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> sieve;
    bitset<N> isPrime;
    isPrime.set();
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i <= N; i++) {
        if (isPrime[i]) {
            sieve.emplace_back(i);
        }
        for (int j = 0; j < sieve.size() && i * sieve[j] <= N; j++) {
            isPrime[i * sieve[j]] = false;
            if (i % sieve[j] == 0) {
                break;
            }
        }
    }

    int n, q;
    cin >> n >> q;

    while (q --) {
        int k;
        cin >> k;
        cout << sieve[k - 1] << "\n";
    }

    return 0;
}

/*
    埃筛O(nloglogn)
*/
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int N = 1E8 + 10;
 
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> sieve;
    bitset<N> isPrime;
    isPrime.set();
    isPrime[0] = isPrime[1] = false;

    for (i64 i = 2; i * i <= N; i++) {
        if (isPrime[i]) {
            for (i64 j = i * i; j <= N; j += i) {
                isPrime[j] = false;
            }
        }
    }
    for (int i = 2; i <= N; i++) {
        if (isPrime[i]) {
            sieve.emplace_back(i);
        }
    }
    
    int n, q;
    cin >> n >> q;

    while (q --) {
        int k;
        cin >> k;
        cout << sieve[k - 1] << "\n";
    }

    return 0;
}