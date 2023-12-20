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

#define oo 1<<30

struct rule {
    int minx=0, maxx=oo, minm=0, maxm=oo, mina=0, maxa=oo, mins=0, maxs=oo;
    string target;
};

struct workflow {
    vector<rule> r;
    workflow() {}
    workflow(string s) {
        auto v = split(s.substr(1, s.size() - 2), ',');
        for (const string& rs : v) {
            rule nr;
            auto rsv = split(rs, ':');
            if (rsv.size() > 1)
            {
                switch (rsv[0][0]) {
                case 'x':
                    if (rsv[0][1] == '<')
                        nr.maxx = atoi(rsv[0].substr(2).c_str());
                    else
                        nr.minx = atoi(rsv[0].substr(2).c_str());
                    break;
                case 'm':
                    if (rsv[0][1] == '<')
                        nr.maxm = atoi(rsv[0].substr(2).c_str());
                    else
                        nr.minm = atoi(rsv[0].substr(2).c_str());
                    break;
                case 'a':
                    if (rsv[0][1] == '<')
                        nr.maxa = atoi(rsv[0].substr(2).c_str());
                    else
                        nr.mina = atoi(rsv[0].substr(2).c_str());
                    break;
                case 's':
                    if (rsv[0][1] == '<')
                        nr.maxs = atoi(rsv[0].substr(2).c_str());
                    else
                        nr.mins = atoi(rsv[0].substr(2).c_str());
                    break;
                }
                nr.target = rsv[1];
            }
            else
                nr.target = rsv[0];
            r.push_back(nr);
        }
    }
};

struct piece {
    int x, m, a, s;
    int rating() const{
        return x + m + a + s;
    }
};

string process(const piece &p, const unordered_map<string, workflow>& ws) {
    workflow cur;
    string target = "in";
    while (target != "A" && target != "R") {
        cur = ws.find(target)->second;
        for (const rule& r : cur.r) {
            if (p.x > r.minx && p.x < r.maxx &&
                p.m > r.minm && p.m < r.maxm &&
                p.a > r.mina && p.a < r.maxa &&
                p.s > r.mins && p.s < r.maxs) {
                target = r.target;
                break;
            }
        }
    }
    return target;
}

void sol() {

    int maxw = 14;// 591;
    int maxp = 5;// 200;
    string s;
    unordered_map<string, workflow> ws;
    vector<piece> ps;
    for (int i = 0; i < maxw; ++i) {
        cin >> s;
        int st = s.find('{'); 
        workflow w(s.substr(st));
        ws.insert({ s.substr(0, st), w });
    }
    for (int i = 0; i < maxp; ++i) {
        cin >> s;
        auto v = split(s.substr(1, s.size() - 2), ',');
        piece p;
        for (const string& vv : v) {
            auto vvv = split(vv, '=');
            switch (vvv[0][0]) {
            case 'x':
                p.x = atoi(vvv[1].c_str());
                break;
            case 'm':
                p.m = atoi(vvv[1].c_str());
                break;
            case 'a':
                p.a = atoi(vvv[1].c_str());
                break;
            case 's':
                p.s = atoi(vvv[1].c_str());
                break;
            }
        }
        ps.push_back(p);
    }
    long long ans = 0LL;
    for (const piece& p : ps) {
        if (process(p, ws) == "A") ans += p.rating();
    }
    cout << ans << endl;
}




int main()
{
	sol();
	return 0;
}

