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
#include <queue>
using namespace std;


void sol() {

	const int maxn = 140;
	const int maxm = 140;
	char u[maxn][maxm];
	int h[maxn], v[maxm];
	vector<pair<int, int>> g;
	for (int i = 0; i < maxn; ++i) 
		cin >> u[i];
	
	h[0] = v[0] = 0;
	for (int i = 1; i < maxn; ++i) {
		bool b = true;
		h[i] = h[i - 1];
		for (int j = 0; b && j < maxm; ++j)
			if (u[i][j] == '#')
				b = false;
		if (b)
			++h[i];
	}
	for (int j = 1; j < maxm; ++j) {
		v[j] = v[j - 1];
		bool b = true;
		for (int i = 0; b && i < maxn; ++i)
			if (u[i][j] == '#')
				b = false;
		if (b)
			++v[j];
	}
	for (int i = 0; i < maxn; ++i)
		for (int j = 0; j < maxm; ++j)
			if (u[i][j] == '#')
				g.push_back({ i,j });
	long long ans = 0LL;
	int mult = 999999;
	for(int i = 0; i < g.size(); ++i)
		for (int j = i + 1; j < g.size(); ++j) {
			int d = abs(g[i].first - g[j].first) + abs(g[i].second - g[j].second);
			d += abs(h[g[i].first] - h[g[j].first])*mult;
			d += abs(v[g[i].second] - v[g[j].second])*mult;
			ans += d;
		}
	cout << ans << endl;

}

int main()
{
	sol();
	return 0;
}

