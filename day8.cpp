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

 long long gcd( long long a,  long long b) {
	return b == 0 ? a : gcd(b, a % b);
}

 long long mcm( long long a,  long long b) {
	return a * b / gcd(a, b);
}

void sol() {
	const int maxn = 774;
	const int maxs = 5;
	string ins, node, left, right;
	vector<string> nodes;
	cin >> ins;

	unordered_map<string, pair<string, string>> m;

	for (int i = 0; i < maxn; ++i) {
		cin >> node;
		cin >> left;
		cin >> left >> right;
		left = left.substr(1, 3);
		right = right.substr(0, 3);
		m[node] = { left, right };
	}
	int i = 0, n = ins.size();
	for (const pair<string, pair<string, string>> &p : m) {
		if (p.first[2] == 'A')
			nodes.push_back(p.first);
	}
	vector<long long> v(nodes.size());
	for (int k = 0; k < nodes.size(); ++k) {
		string start = nodes[k];
		node = start;
		int i = 0;
		long long steps = 0;
		do {
			if (ins[i] == 'L')
				node = m[node].first;
			else
				node = m[node].second;
			i = (i + 1) % n;
			++steps;
			if (node[2] == 'Z')
				v[k] = steps;
		} while (node != start && v[k]==0);
	}
	long long ans = 1LL*v[0];
	for (int i = 1; i < v.size(); ++i)
		ans = mcm(ans, 1LL*v[i]);
	cout << ans;
}

int main()
{
	sol();
	return 0;
}

