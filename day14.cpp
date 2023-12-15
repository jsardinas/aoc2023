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

void north(vector<string > & m) {
	const int maxn = m.size();
	const int maxm = m[0].size();
	vector<int> v(maxm, 0);
	for (int i = 0; i < maxn; ++i) {
		for (int j = 0; j < maxm; ++j) {
			if (m[i][j] == '#')v[j] = i + 1;
			else if (m[i][j] == 'O') {
				m[i][j] = m[v[j]][j];
				m[v[j]][j] = 'O';
				v[j]++;
			}
		}
	}
}

void west(vector<string > & m) {
	const int maxn = m.size();
	const int maxm = m[0].size();
	int v;
	for (int i = 0; i < maxn; ++i) {
		v = 0;
		for (int j = 0; j < maxm; ++j) {
			if (m[i][j] == '#')v = j + 1;
			else if (m[i][j] == 'O') {
				m[i][j] = m[i][v];
				m[i][v] = 'O';
				v++;
			}
		}
	}
}

void south(vector<string > & m) {
	const int maxn = m.size();
	const int maxm = m[0].size();
	vector<int> v(maxm, maxn-1);
	for (int i = maxn-1; i >= 0; --i) {
		for (int j = 0; j < maxm; ++j) {
			if (m[i][j] == '#')v[j] = i - 1;
			else if (m[i][j] == 'O') {
				m[i][j] = m[v[j]][j];
				m[v[j]][j] = 'O';
				v[j]--;
			}
		}
	}
}

void east(vector<string > & m) {
	const int maxn = m.size();
	const int maxm = m[0].size();
	int v;
	for (int i = 0; i < maxn; ++i) {
		v = maxm-1;
		for (int j = maxm-1; j >= 0; --j) {
			if (m[i][j] == '#')v = j - 1;
			else if (m[i][j] == 'O') {
				m[i][j] = m[i][v];
				m[i][v] = 'O';
				v--;
			}
		}
	}
}

void spin(vector<string> & m) {
	north(m);
	west(m);
	south(m);
	east(m);
}

bool cmp(const vector<string>& a, const vector<string>& b) {
	if (a.size() != b.size())
		return false;
	if (a[0].size() != b[0].size())
		return false;
	for (int i = 0; i < a.size(); ++i)
		if (a[i] != b[i])
			return false;
	return true;
}

void sol(){
	int maxn = 100;
	vector<string> m(maxn);
	vector<string> prev(maxn);
	unordered_map<string, int> kv;
	int c;
	for (int i = 0; i < maxn; ++i)
		cin >> m[i];
	string key = "";
	for (int i = 0; i < maxn; ++i)key += m[i];
	//kv[key] = 0;
	long long i = 0;
	do {
		for (int i = 0; i < maxn; ++i)
			prev[i] = m[i];
		spin(m);
		++i;
		key = "";
		for (int i = 0; i < maxn; ++i)key += m[i];
		auto it = kv.find(key);
		if (it == kv.end())
			kv[key] = i;
		else {
			c = i - it->second;
			break;
		}
	} while (!cmp(prev, m) || i < 1000000000L);

	int r = (1000000000 - i) % c;
	while (r--)
		spin(m);

	int ans = 0;
	for (int i = 0; i < maxn; ++i)
		for (int j = 0; j < m[i].size(); ++j)
			if (m[i][j] == 'O')
				ans += (maxn - i);
	cout << ans << endl;
}

int main()
{
	sol();
	return 0;
}

