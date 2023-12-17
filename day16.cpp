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
#include <unordered_set>
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

#define KEY(x,y,d) 10000*x+10*y+d 

int conf(const vector<string> & v, const int maxn, const int maxm, const pair<pair<int, int>, int> first) {
    unordered_set<int> visited;
    vector<vector<int>> c(maxn, vector<int>(maxm, 0));
    queue<pair<pair<int, int>, int>> q;
    q.push(first);
    int x, y, d;
    while (!q.empty()) {
        auto p = q.front();
        x = p.first.first, y = p.first.second, d = p.second;
        q.pop();
        if (visited.find(KEY(x, y, d)) != visited.end())
            continue;
        visited.insert(KEY(x, y, d));
        c[x][y] = 1;
        switch (d) {
        case 0: //right
            switch (v[x][y]) {
            case '|':
                if (x - 1 >= 0)
                    q.push({ {x - 1, y}, 3 });
                if (x + 1 < maxn)
                    q.push({ {x + 1, y}, 1 });
                break;
            case '/':
                if (x - 1 >= 0)
                    q.push({ {x - 1, y}, 3 });
                break;
            case '\\':
                if (x + 1 < maxn)
                    q.push({ {x + 1, y}, 1 });
                break;
            default:
                if (y + 1 < maxm)
                    q.push({ {x, y + 1}, 0 });
                break;
            }
            break;
        case 1: //down
            switch (v[x][y]) {
            case '-':
                if (y - 1 >= 0)
                    q.push({ {x, y - 1}, 2 });
                if (y + 1 < maxm)
                    q.push({ {x, y + 1}, 0 });
                break;
            case '/':
                if (y - 1 >= 0)
                    q.push({ {x, y - 1}, 2 });
                break;
            case '\\':
                if (y + 1 < maxm)
                    q.push({ {x, y + 1}, 0 });
                break;
            default:
                if (x + 1 < maxn)
                    q.push({ {x + 1, y}, 1 });
                break;
            }
            break;
        case 2: //left
            switch (v[x][y]) {
            case '|':
                if (x - 1 >= 0)
                    q.push({ {x - 1, y}, 3 });
                if (x + 1 < maxn)
                    q.push({ {x + 1, y}, 1 });
                break;
            case '/':
                if (x + 1 < maxn)
                    q.push({ {x + 1, y}, 1 });
                break;
            case '\\':
                if (x - 1 >= 0)
                    q.push({ {x - 1, y}, 3 });
                break;
            default:
                if (y - 1 >= 0)
                    q.push({ {x, y - 1}, 2 });
                break;
            }
            break;
        case 3: //up
            switch (v[x][y]) {
            case '-':
                if (y - 1 >= 0)
                    q.push({ {x, y - 1}, 2 });
                if (y + 1 < maxm)
                    q.push({ {x, y + 1}, 0 });
                break;
            case '/':
                if (y + 1 < maxn)
                    q.push({ {x, y + 1}, 0 });
                break;
            case '\\':
                if (y - 1 >= 0)
                    q.push({ {x, y - 1}, 2 });
                break;
            default:
                if (x - 1 >= 0)
                    q.push({ {x - 1, y}, 3 });
                break;
            }
            break;
        }
    }
    int ans = 0LL;
    for (int i = 0; i < maxn; ++i)
        for (int j = 0; j < maxm; ++j)
            ans += c[i][j];
    return ans;
}

void sol(){
	
    const int maxn = 110;
    vector<string> v(maxn);

    for (int i = 0; i < maxn; ++i)
        cin >> v[i];
    const int maxm = v[0].size();

    int ans = 0;
    for (int j = 0; j < maxm; ++j) {
        ans = max(ans, conf(v, maxn, maxm, { {0, j,}, 1 }));
        ans = max(ans, conf(v, maxn, maxm, { {maxn-1, j,}, 3 }));
    }
    for (int i = 0; i < maxn; ++i) {
        ans = max(ans, conf(v, maxn, maxm, { {i, 0}, 0 }));
        ans = max(ans, conf(v, maxn, maxm, { {i, maxm-1}, 2 }));
    }
    cout << ans << endl;
}




int main()
{
	sol();
	return 0;
}

