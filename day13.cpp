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

int wildcard = 0;

bool sameh(const vector<string>& m, int lb, int ub) {
    int diff = 0;
    for (int i = 0; i < m[0].size(); ++i)
        if (m[lb][i] != m[ub][i]) {
            ++diff;
            if (diff > 1 || (diff == 1 && wildcard))
                return false;
        }
    if(!wildcard)
        wildcard = diff;
    return true;
}

bool samev(const vector<string>& m, int lb, int ub) {
    int diff = 0;
    for (int i = 0; i < m.size(); ++i)
        if (m[i][lb] != m[i][ub]) {
            ++diff;
            if (diff > 1 || (diff == 1 && wildcard))
                return false;
        }
    if(!wildcard)
        wildcard = diff;
    return true;
}

bool checkh(const vector<string> &m, int i) {
    int lb = i - 1, ub = i;
    while (lb >= 0 && ub < m.size()) {
        if (!sameh(m, lb, ub))
            return false;
        --lb, ++ub;
    }
    return wildcard;
}

bool checkv(const vector<string> &m, int i) {
    int lb = i - 1, ub = i;
    while (lb >= 0 && ub < m[0].size()) {
        if (!samev(m, lb, ub))
            return false;
        --lb, ++ub;
    }
    return wildcard;
}

void sol(){
    vector<string> m;
    string s;
    char tmp[30];
    const int maxn = 100;
    long long ans = 0;

    for (int t = 0; t < maxn; ++t) {
        m.clear();
        cin.getline(tmp, 30);
        while (*tmp) {
            m.push_back(tmp);
            cin.getline(tmp, 30);
        }

        bool f = true;
        for (int i = 1; f && i < m.size(); ++i) {
            wildcard = 0;
            if (checkh(m, i)) {
                ans += 100 * i;
                f = false;
            }
        }
        for (int i = 1; f && i < m[0].size(); ++i) {
            wildcard = 0;
            if (checkv(m, i)) {
                ans += i;
                f = false;
            }
        }
    }

    cout << ans;
}

int main()
{
	sol();
	return 0;
}

