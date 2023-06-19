// url:https://www.luogu.com.cn/problem/P3865
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

template <typename T>
struct SparseTable {
	vector<vector<T> > ST;
	using func_type = function<T(const T &, const T &)>;
	static T default_func(const T &t1, const T &t2) {
		return max(t1, t2);
	}
	func_type op;

	SparseTable(const vector<T> &v, func_type _func = default_func) {
		op = _func;
		int len = v.size(), l1 = ceil(log2(len)) + 1;
		ST.assign(len, vector<T>(l1, 0));

		for (int i = 0; i < len; i++) {
			ST[i][0] = v[i];
		}
		for (int j = 1; j < l1; j++) {
			int pj = (1 << (j - 1));
			for (int i = 0; i + pj < len; i++) {
				ST[i][j] = op(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
			}
		}
    }
	// 1) check here! from 0 ~ n - 1 && 2) remember in cpp log(0) is illegal
	T query(int l, int r) { 
		if (l == r) {
			return ST[l][0];
		}
		int q = ceil(log2(r - l + 1)) - 1;
		return op(ST[l][q], ST[r - (1 << q) + 1][q]);
	}
};


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<i64> vec(n);
	for (int i = 0; i < n; i++) {
		cin >> vec[i];
	}

	SparseTable<i64> Z(vec);

	while (m --) {
		int l, r;
		cin >> l >> r;
		l --, r --;
		cout << Z.query(l, r) << "\n";
	}
	
    return 0;
}