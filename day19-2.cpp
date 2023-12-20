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

#define oo 4000

struct rule {
    int minx=1, maxx=oo, minm=1, maxm=oo, mina=1, maxa=oo, mins=1, maxs=oo;
    string target;
    rule(int _min, int _max) :
        minx(_min), maxx(_max), minm(_min), maxm(_max), mina(_min), maxa(_max), mins(_min), maxs(_max) {}
    rule() {};
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
                        nr.maxx = atoi(rsv[0].substr(2).c_str())-1;
                    else
                        nr.minx = atoi(rsv[0].substr(2).c_str())+1;
                    break;
                case 'm':
                    if (rsv[0][1] == '<')
                        nr.maxm = atoi(rsv[0].substr(2).c_str())-1;
                    else
                        nr.minm = atoi(rsv[0].substr(2).c_str())+1;
                    break;
                case 'a':
                    if (rsv[0][1] == '<')
                        nr.maxa = atoi(rsv[0].substr(2).c_str())-1;
                    else
                        nr.mina = atoi(rsv[0].substr(2).c_str())+1;
                    break;
                case 's':
                    if (rsv[0][1] == '<')
                        nr.maxs = atoi(rsv[0].substr(2).c_str())-1;
                    else
                        nr.mins = atoi(rsv[0].substr(2).c_str())+1;
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
            if (p.x >= r.minx && p.x <= r.maxx &&
                p.m >= r.minm && p.m <= r.maxm &&
                p.a >= r.mina && p.a <= r.maxa &&
                p.s >= r.mins && p.s <= r.maxs) {
                target = r.target;
                break;
            }
        }
    }
    return target;
}

rule complement(const rule& r) {
    rule c;
    c.minx = r.minx == 1 ? (r.maxx == oo ? 1 : r.maxx+1) : 1;
    c.maxx = r.minx == 1 ? oo : r.minx-1;

    c.minm = r.minm == 1 ? (r.maxm == oo ? 1 : r.maxm+1) : 1;
    c.maxm = r.minm == 1 ? oo : r.minm-1;

    c.mina = r.mina == 1 ? (r.maxa == oo ? 1 : r.maxa+1) : 1;
    c.maxa = r.mina == 1 ? oo : r.mina-1;

    c.mins = r.mins == 1 ? (r.maxs == oo ? 1 : r.maxs+1) : 1;
    c.maxs = r.mins == 1 ? oo : r.mins-1;

    return c;
}

void sol() {

    int maxw = 591;
    int maxp = 5;// 200;
    string s;
    unordered_map<string, workflow> ws;
    unordered_map<string, vector<rule>> res;
    for (int i = 0; i < maxw; ++i) {
        cin >> s;
        int st = s.find('{'); 
        workflow w(s.substr(st));
        ws.insert({ s.substr(0, st), w });
    }
    for (int i = 0; i < maxp; ++i)
        cin >> s;//ignore

    rule r(1,4000);
    res["in"] = vector<rule>(1,r);
    queue<string> q;
    q.push("in");
    while (!q.empty()) {
        string key = q.front();
        q.pop();
        auto it = res.find(key);
        if (it == res.end())
            continue;
        auto rv = it->second;
        res.erase(key);
        workflow wf = ws[key];
        for(const rule& curr : rv){
            rule targetr = curr, restr = curr;
            for (const rule& ir : wf.r) {
                rule ic = complement(ir);
                targetr.minx = max(targetr.minx, ir.minx);
                targetr.maxx = min(targetr.maxx, ir.maxx);
                restr.minx = max(restr.minx, ic.minx);
                restr.maxx = min(restr.maxx, ic.maxx);

                targetr.minm = max(targetr.minm, ir.minm);
                targetr.maxm = min(targetr.maxm, ir.maxm);
                restr.minm = max(restr.minm, ic.minm);
                restr.maxm = min(restr.maxm, ic.maxm);

                targetr.mina = max(targetr.mina, ir.mina);
                targetr.maxa = min(targetr.maxa, ir.maxa);
                restr.mina = max(restr.mina, ic.mina);
                restr.maxa = min(restr.maxa, ic.maxa);

                targetr.mins = max(targetr.mins, ir.mins);
                targetr.maxs = min(targetr.maxs, ir.maxs);
                restr.mins = max(restr.mins, ic.mins);
                restr.maxs = min(restr.maxs, ic.maxs);

                auto it = res.find(ir.target);
                if (it == res.end())
                    res[ir.target] = vector<rule>(1, targetr);
                else
                    it->second.push_back(targetr);
                if (ir.target != "A" && ir.target != "R")
                    q.push(ir.target);
                targetr = restr;
            }
        }

    }

    long long ans = 0LL;
    for (const rule& r : res["A"])
        ans += 1LL * (r.maxx - r.minx + 1) * (r.maxm - r.minm + 1) * (r.maxa - r.mina + 1) * (r.maxs - r.mins + 1);
    cout << ans << endl;
}




int main()
{
	sol();
	return 0;
}

