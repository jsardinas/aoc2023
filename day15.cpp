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

int hashx(const string& s) {
    int h = 0;
    for (const char& c : s)
        h = (17 * (h + (int)c)) % 256;
    return h;
}

void sol(){
	long long ans = 0;

	string s;
	cin >> s;
    auto v = split(s, ',');
    vector<pair<string, int>> boxes[256];
    string label;
    char op;
    int n;
    for (const string& w : v) {
        label = "";
        int i = 0;
        while (w[i] >= 'a' && w[i] <= 'z')
            label += w[i++];
        op = w[i++];
        if (op == '=')
            n = w[i] - '0';
        int h = hashx(label);
        if (op == '-') {
            for (i = 0; i < boxes[h].size() && boxes[h][i].first != label; ++i);
            if (i < boxes[h].size()) {
                while (i < boxes[h].size() - 1) {
                    boxes[h][i] = boxes[h][i + 1];
                    ++i;
                }
                boxes[h].pop_back();
            }
        }
        else {//op=='='
            for (i = 0; i < boxes[h].size() && boxes[h][i].first != label; ++i);
            if (i < boxes[h].size())
                boxes[h][i].second = n;
            else
                boxes[h].push_back({label, n});
        }
    }
    for (int h = 0; h < 256; ++h)
        for (int i = 0; i < boxes[h].size(); ++i)
            ans += (h + 1) * (i + 1) * boxes[h][i].second;
    cout << ans << endl;
}

int main()
{
	sol();
	return 0;
}

