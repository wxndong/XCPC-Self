#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using pii = pair<int, int>;
/*
    双哈希的板子
    从
    https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63666253
    抄的
    string 的下标需要从1开始
*/
template<typename T>
T power(T n, long long k) {
    T res = 1;
    while (k) {
        if (k & 1) res = res * n;
        n *= n;
        k /= 2;
    }
    return res;
}

template <const int M>
struct ModInt {
    int x;
    int norm(int x) {
        if (x < 0) {
            x += M;
        }
        if (x >= M) {
            x -= M;
        }
        return x;
    }
    ModInt(int x = 0) : x(norm(x % M)) {}
    int val() const {
        return x;
    }
    ModInt operator -() const {
        return ModInt(norm(M - x));
    }
    ModInt inv() const {
        assert(x != 0);
        return power(*this, M - 2);
    }
    ModInt &operator *=(const ModInt &rhs) {
        x = (long long)(x) * rhs.x % M;
        return *this;
    }
    ModInt &operator +=(const ModInt &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    ModInt &operator -=(const ModInt &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    ModInt &operator /=(const ModInt &rhs) {
        return *this *= rhs.inv();
    }
    bool operator < (const ModInt &rhs) {
        return x < rhs.x;
    }
    bool operator == (const ModInt &rhs) {
        return x == rhs.x;
    }
    bool operator != (const ModInt &rhs) {
        return x != rhs.x;
    }
    friend ModInt operator *(const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res *= rhs;
        return res;
    }
    friend ModInt operator +(const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res += rhs;
        return res;
    }
    friend ModInt operator -(const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res -= rhs;
        return res;
    }
    friend ModInt operator /(const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator >>(std::istream &is, ModInt &a) {
        long long v;
        is >> v;
        a = ModInt(v);
        return is;
    }
    friend std::ostream &operator <<(std::ostream &os, const ModInt &a) {
        return os << a.val();
    }
};

template <typename T, const int P>
struct single_hash {
    int n;
    std::vector<T> h, hi, p;
    single_hash(string s) : n(s.size() - 1), h(n + 1), hi(n + 2), p(n + 1) {
        p[0] = 1;
        for (int i = 1; i <= n; i++) {
            p[i] = p[i - 1] * P;
            h[i] = h[i - 1] * P + s[i];
        }
        for (int i = n; i >= 1; i--) {
            hi[i] = hi[i + 1] * P + s[i];
        }
    }
    T get(int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    }
    T geti(int l, int r) {
        return hi[l] - hi[r + 1] * p[r - l + 1];
    }
    bool ispalindrome(int l, int r) {
        return get(l, r) == geti(l, r);
    }
    bool same(int l1, int r1, int l2, int r2) {
        return get(l1, r1) == get(l2, r2);
    }
    T MergeFF(int l1, int r1, int l2, int r2) { // Forward and Forward
        return get(l1, r1) * p[r2 - l2 + 1] + get(l2, r2);
    }
    T MergeFR(int l1, int r1, int l2, int r2) { // Forward and reverse
        return get(l1, r1) * p[r2 - l2 + 1] + geti(l2, r2);
    }
    T MergeRF(int l1, int r1, int l2, int r2) { // reverse and Forward
        return geti(l1, r1) * p[r2 - l2 + 1] + get(l2, r2);
    }
    T MergeRR(int l1, int r1, int l2, int r2) { // reverse and reverse
        return geti(l1, r1) * p[r2 - l2 + 1] + geti(l2, r2);
    }
};
using SingleHash1 = single_hash<ModInt<(int)(1E9 + 7)>, 131>;
using SingleHash2 = single_hash<ModInt<(int)(998244353)>, 13331>;
 
struct DoubleHash : SingleHash1, SingleHash2 {
    using SingleHash1::single_hash;
    using SingleHash2::single_hash;
 
    DoubleHash(string s) : SingleHash1::single_hash(s), SingleHash2::single_hash(s) {}
 
    pair<int, int> get(int l, int r) {
        int h1 = SingleHash1::get(l, r).val();
        int h2 = SingleHash2::get(l, r).val();
        return pair<int, int> (h1, h2);
    }
    pair<int, int> geti(int l, int r) {
        int h1 = SingleHash1::geti(l, r).val();
        int h2 = SingleHash2::geti(l, r).val();
        return pair<int, int> (h1, h2);
    }
    bool ispalindrome(int l, int r) {
        return SingleHash1::get(l, r) == SingleHash1::geti(l, r);
        return SingleHash2::get(l, r) == SingleHash2::geti(l, r);
    }
    bool same(int l1, int r1, int l2, int r2) {
        return get(l1, r1) == get(l2, r2);
    }
    pair<int, int> MergeFF(int l1, int r1, int l2, int r2) { // Forward and Forward
        int h1 = SingleHash1::MergeFF(l1, r1, l2, r2).val();
        int h2 = SingleHash2::MergeFF(l1, r1, l2, r2).val();
        return pair<int, int> (h1, h2);
    }
    pair<int, int> MergeFR(int l1, int r1, int l2, int r2) { // Forward and reverse
        int h1 = SingleHash1::MergeFR(l1, r1, l2, r2).val();
        int h2 = SingleHash2::MergeFR(l1, r1, l2, r2).val();
        return pair<int, int> (h1, h2);
    }
    pair<int, int> MergeRF(int l1, int r1, int l2, int r2) { // reverse and Forward
        int h1 = SingleHash1::MergeRF(l1, r1, l2, r2).val();
        int h2 = SingleHash2::MergeRF(l1, r1, l2, r2).val();
        return pair<int, int> (h1, h2);
    }
    pair<int, int> MergeRR(int l1, int r1, int l2, int r2) { // reverse and reverse
        int h1 = SingleHash1::MergeRR(l1, r1, l2, r2).val();
        int h2 = SingleHash2::MergeRR(l1, r1, l2, r2).val();
        return pair<int, int> (h1, h2);
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

    DoubleHash s(str);

    map<pii, int> theR;
    map<pii, int> cnt;

    for (int i = 1; i + k - 1 <= n; i++) {
        auto t = s.get(i, i + k - 1);
        if (theR[t] == 0 || theR[t] < i) {
            cnt[t] ++;
            theR[t] = i + k - 1;
        }
    }

    int ans = 0;
    for (auto [_, f] : cnt) {
        if (f == m) {
            ans ++;
        }
    }
    cout << ans << "\n";

    return 0;
}