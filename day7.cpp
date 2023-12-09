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
using namespace std;

struct hand {
	char h[6];
	int b;
};

map<char, int> m = { {'J', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6',5}, {'7', 6}, {'8', 7}, {'9', 8}, {'T', 9}, {'Q', 10}, {'K', 11}, {'A', 12} };

int getrank( char* hh) {
	char h[5];
	strncpy(h, hh, 5);
	int dup[13] = { 0 };
	sort(h, h + 5);
	for (int i = 0; i < 5; ++i)
		dup[m[h[i]]]++;

	int j = dup[0];
	dup[0] = 0;
	std::sort(dup, dup + 13, std::greater<int>());
	dup[0] += j;
	if (dup[0] > 3)return dup[0]+1;
	if (dup[0] == 3)return dup[1] + 2;
	if (dup[0] == 2)return dup[1];
	return 0;
}

bool cmp(hand& h, hand& g) {
	int rh = getrank(h.h);
	int rg = getrank(g.h);
	if(rh < rg)	return true;
	if (rh > rg) return false;
	for (int i = 0; i < 5; ++i) {
		if (m[h.h[i]] < m[g.h[i]]) return true;
		if (m[h.h[i]] > m[g.h[i]]) return false;
	}
	return true;
}

void sol() {
	const int maxn = 1000;
	hand h[maxn];
	for (int i = 0; i < maxn; ++i) {
		scanf("%s %d", h[i].h, &h[i].b);
	}
	std::sort(h, h + maxn, cmp);
	long long ans = 0LL;
	for (int i = 0; i < maxn; ++i)
		ans += (i + 1) * h[i].b;
	printf("%I64d", ans);
}

int main()
{
	sol();
	return 0;
}

