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

vector<string> split(string str, char separator) {
    int startIndex = 0, endIndex = 0;
    vector<string> res;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            res.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return res;
}

bool check(const string &s, int start, int len) {
    for (; len > 0; start++, len--)
        if (s[start] == '.') return false;
    return s[start] != '#';
}

unordered_map<int, long long> m;

long long cm(const string& s, int i, const vector<int>& g, int j) {
    if (j >= g.size()) {
        for (; i < s.size(); ++i)
            if (s[i] == '#')
                return 0;
        return 1;
    }

    long long ans = 0, tmp;
    int start = i;
    while (start + g[j] < s.size() && (start == 0 || s[start - 1] != '#')) {
        if (check(s, start, g[j])) {
            const auto key = 1000 * (start + g[j] + 1) + (j + 1);
            auto it = m.find(key);
            if (it != m.end())
                tmp = it->second;
            else {
                tmp = cm(s, start + g[j] + 1, g, j + 1);
                m[key] = tmp;
            }
            ans += tmp;
        }
        ++start;
    }

    return ans;
}

void sol(){

	const int maxn = 1000;
	string s, n;
	long long ans = 0;
    vector<int> g, tmp;
	for (int t = 0; t < maxn; ++t) {
		cin >> s >> n;
        auto v = split(n, ',');
        tmp.clear();
        for (const string& i : v)
            tmp.push_back(atoi(i.c_str()));

        s = s + "?" + s + "?" + s + "?" + s + "?" + s + ".";
        g.clear();
        for(int i = 0; i < 5; ++i)
            g.insert(g.end(), tmp.begin(), tmp.end());
        m.clear();
        ans += cm(s, 0, g, 0);
	}

	cout << ans;
}

int main()
{
	sol();
	return 0;
}

