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

#define KEY(x,y,d,s) 100000*x+100*y+10*d+s

pair<int, int> mv[4] = { {0,1},{1,0},{0,-1},{-1, 0} };


struct State {
    int heatLoss;
    int x;
    int y;
    int dir;
    int steps;
};

class Compare
{
public:
    bool operator() (const State& a, const State &b)
    {
        if (a.heatLoss > b.heatLoss)
            return true;
        if (a.heatLoss < b.heatLoss)
            return false;
        if (a.x + a.y < b.x + b.y)
            return true;
        if (a.x + a.y > b.x + b.y)
            return false;
        return a.dir > b.dir;
    }
};

void sol() {
    const int maxn = 141;
    const int maxsteps = 10;
    const int minsteps = 4;
    vector<string> v(maxn);
    unordered_map<int, int> vis;

    for (int i = 0; i < maxn; ++i)
        cin >> v[i];
    const int maxm = v[0].size();
    priority_queue<State, vector<State>, Compare> q;
    State st = {0,0,0,-1,0};
    q.push(st);
    while (!q.empty()) {
        //cout << vis.size() << endl;
        st = q.top();
        q.pop();
        if (st.x == maxn - 1 && st.y == maxm - 1 && st.steps >= minsteps) {
            cout << st.heatLoss + v[st.x][st.y]-'0' << endl;
            return;
        }
        int key = KEY(st.x, st.y, st.dir, st.steps);
        auto it = vis.find(key);
        if (it == vis.end())
            vis[key] = st.heatLoss;
        else{
            if (st.heatLoss < it->second)
                it->second = st.heatLoss;
            else
                continue;
        }
            
        for (int i = 0; i < 4; ++i) {
            if (st.x + mv[i].first >= 0 && st.x + mv[i].first < maxn &&
                st.y + mv[i].second >= 0 && st.y + mv[i].second < maxm &&
                (st.dir == -1 || abs(i - st.dir) != 2) && 
                (st.dir == -1 || (i == st.dir && st.steps < maxsteps) || (i != st.dir && st.steps >= minsteps))
            )
                q.push({ 
                    st.heatLoss + (st.dir == -1 ? 0 : v[st.x][st.y] - '0'), 
                    st.x + mv[i].first,
                    st.y + mv[i].second,
                    i,
                    (i == st.dir ? st.steps + 1 : 1) 
                });
        }
    }
}




int main()
{
	sol();
	return 0;
}

