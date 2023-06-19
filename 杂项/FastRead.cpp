#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

/***
 * fast read
 * readi和readu分别读取有符号和无符号整数，需要头文件 cctype。
 ***/
template<class _Ty> inline void readi(_Ty& x) {
	static _Ty c, s; x = 0, s = 1;
	c = getchar();
	if (c == '-')s = -1;
	else x = x * 10 + c - '0';
	for (;;) {
		c = getchar();
		if (!isdigit(c))break;
		x = x * 10 + c - '0';
	}
	x *= s;
}
template<class _Ty> inline void readu(_Ty& x) {
	static _Ty c; x = 0;
	for (;;) {
		c = getchar();
		if (!isdigit(c))return;
		x = x * 10 + c - '0';
	}
}

/***
 * fast write
 * writei，writeu，writep分别输出整数、无符号整数和正整数，delim表示分隔符。
 ***/
template<class _Ty> inline void writei(_Ty x) {
	static int c[64];
	unsigned p = 0;
	if (x < 0) { putchar('-'), x = -x; }
	if (x == 0) { putchar('0'); return; }
	while (x) { c[++p] = x % 10 + '0', x /= 10; }
	while (p) { putchar(c[p]); --p; }
}
template<class _Ty> inline void writeu(_Ty x) {
	static int c[64];
	unsigned p = 0;
	if (x == 0) { putchar('0'); return; }
	while (x) { c[++p] = x % 10 + '0', x /= 10; }
	while (p) { putchar(c[p]); --p; }
}
template<class _Ty> inline void writep(_Ty x) {
	static int c[64];
	unsigned p = 0;
	while (x) { c[++p] = x % 10 + '0', x /= 10; }
	while (p) { putchar(c[p]); --p; }
}
template<class _Ty> inline void writei(_Ty x, const int& delim) {
	static int c[64];
	unsigned p = 0;
	if (x < 0) { putchar('-'), x = -x; }
	if (x == 0) { printf("0%c", delim); return; }
	while (x) { c[++p] = x % 10 + '0', x /= 10; }
	while (p) { putchar(c[p]); --p; }
	putchar(delim);
}
template<class _Ty> inline void writeu(_Ty x, const int& delim) {
	static int c[64];
	unsigned p = 0;
	if (x == 0) { printf("0%c", delim); return; }
	while (x) { c[++p] = x % 10 + '0', x /= 10; }
	while (p) { putchar(c[p]); --p; }
	putchar(delim);
}
template<class _Ty> inline void writep(_Ty x, const int& delim) {
	static int c[64];
	unsigned p = 0;
	while (x) { c[++p] = x % 10 + '0', x /= 10; }
	while (p) { putchar(c[p]); --p; }
	putchar(delim);
}

int main() {
    writei(1000);
    return 0;
}