// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cstdio>
#include <numeric>

using namespace std;

vector<string> split(char* arr) {
    int i = 0;
    vector<string> v;
    string s;
    while (arr[i] != '\0') {
        if (arr[i] != ' ') {
            s += arr[i];
        }
        else {
            v.push_back(s);
            s.clear();
        }
        i++;
    }
    v.push_back(s);
    return v;
}

pair<long long, long long> intersect(pair<long long, long long> p, pair<long long, long long> q) {
    pair<long long, long long> r = {max(p.first, q.first), min(p.second, q.second)};
    if (r.first >= r.second)  return { -1,-1 };
    else return r;
}

vector<pair<long long, long long>> split(pair<long long, long long> p, pair<long long, long long> q) {
    return { {p.first, q.first}, q, {q.second, p.second} };
}

vector<pair<long long, long long>> intersectAndSplit(pair<long long, long long> p, pair<long long, long long> q) {
    return split(p, intersect(p, q));
}

vector<pair<long long, long long>> apply(vector<pair<long long, long long>> seeds, vector<pair<pair<long long, long long>, long long>> m) {
    
    vector<pair<long long, long long>> nextseeds;

    for (auto seed : seeds) {
        for (int i = 0; i < m.size(); ++i) {
            if (m[i].first.first >= seed.second) {
                nextseeds.push_back(seed);
                break;
            }
            if (m[i].first.second <= seed.first)continue;
            
            auto v = intersectAndSplit(seed, m[i].first);
            if (v[0].first < v[0].second)
                nextseeds.push_back(v[0]);
            nextseeds.push_back({ v[1].first + m[i].second, v[1].second + m[i].second });
            seed = v[2];
            if (seed.first >= seed.second) break;
        }
        if (seed.first < seed.second)
            nextseeds.push_back(seed);
    }
    std::sort(nextseeds.begin(), nextseeds.end());
    return nextseeds;
}

void sol1() {
    vector<pair<pair<long long, long long>, long long>> ss, sf, fw, wl, lt, th, hl;
    vector<pair<long long, long long>> seeds, nextseeds;
    char line[260];
    string s;
    cin.getline(line, 260);
    cout << line<<endl;
    auto v = split(line);
    for (int i = 1; i < v.size(); i += 2) {
        long long a = atoll(v[i].c_str()), b = atoll(v[i + 1].c_str());
        seeds.push_back({ a, a + b });
    }
    
    cin.getline(line, 260);//ss map
    for (;;) {
        cin.getline(line, 260);
        auto v = split(line);
        if (v.size() < 3)break;
        long long a = atoll(v[0].c_str()), b = atoll(v[1].c_str()), c = atoll(v[2].c_str());
        ss.push_back({ {b, b + c}, a - b });
    }

    for (;;) {// sf map
        cin.getline(line, 260);
        auto v = split(line);
        if (v.size() < 3)break;
        long long a = atoll(v[0].c_str()), b = atoll(v[1].c_str()), c = atoll(v[2].c_str());
        sf.push_back({ {b, b + c}, a - b });
    }

    for (;;) {// fw map
        cin.getline(line, 260);
        auto v = split(line);
        if (v.size() < 3)break;
        long long a = atoll(v[0].c_str()), b = atoll(v[1].c_str()), c = atoll(v[2].c_str());
        fw.push_back({ {b, b + c}, a - b });
    }

    for (;;) {// wl map
        cin.getline(line, 260);
        auto v = split(line);
        if (v.size() < 3)break;
        long long a = atoll(v[0].c_str()), b = atoll(v[1].c_str()), c = atoll(v[2].c_str());
        wl.push_back({ {b, b + c}, a - b });
    }

    for (;;) {// lt map
        cin.getline(line, 260);
        auto v = split(line);
        if (v.size() < 3)break;
        long long a = atoll(v[0].c_str()), b = atoll(v[1].c_str()), c = atoll(v[2].c_str());
        lt.push_back({ {b, b + c}, a - b });
    }

    for (;;) {// th map
        cin.getline(line, 260);
        auto v = split(line);
        if (v.size() < 3)break;
        long long a = atoll(v[0].c_str()), b = atoll(v[1].c_str()), c = atoll(v[2].c_str());
        th.push_back({ {b, b + c}, a - b });
    }

    for (;;) {// hl map
        cin.getline(line, 260);
        auto v = split(line);
        if (v.size() < 3)break;
        long long a = atoll(v[0].c_str()), b = atoll(v[1].c_str()), c = atoll(v[2].c_str());
        hl.push_back({ {b, b + c}, a - b });
    }
    
    std::sort(ss.begin(), ss.end());
    std::sort(sf.begin(), sf.end());
    std::sort(fw.begin(), fw.end());
    std::sort(wl.begin(), wl.end());
    std::sort(lt.begin(), lt.end());
    std::sort(th.begin(), th.end());
    std::sort(hl.begin(), hl.end());
    
    seeds = apply(seeds, ss);
    cout << seeds.size() << endl;
    seeds = apply(seeds, sf);
    cout << seeds.size() << endl;
    seeds = apply(seeds, fw);
    cout << seeds.size() << endl;
    seeds = apply(seeds, wl);
    cout << seeds.size() << endl;
    seeds = apply(seeds, lt);
    cout << seeds.size() << endl;
    seeds = apply(seeds, th);
    cout << seeds.size() << endl;
    seeds = apply(seeds, hl);
    cout << seeds.size() << endl;
    cout << seeds.begin()->first;
}

int main()
{
    sol1();
    return 0;
}

