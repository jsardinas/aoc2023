// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#define eps 1e-9

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cstdio>
#include <numeric>
#include <cmath>
#include <unordered_map>
using namespace std;


void sol() {
	const int maxn = 21;
	const int maxt = 200;
	int v[maxn][maxn];
	long long ans = 0LL;
	for (int t = 0; t < maxt; ++t) {
		for (int i = 0; i < maxn; ++i)
			cin >> v[0][i];
		bool z = false;
		int i = 1;
		while (!z) {
			z = true;
			for (int j = 0; j < maxn - i; ++j) {
				v[i][j] = v[i - 1][j + 1] - v[i - 1][j];
				if (v[i][j] != 0) z = false;
			}
			++i;
		}
		i -= 2;
		int prev = v[i][0];
		while (--i >= 0) {
			prev = v[i][0] - prev;
		}
		ans += prev;
	}
	cout << ans;
}

int main()
{
	sol();
	return 0;
}

