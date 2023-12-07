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
using namespace std;


void sol() {
	long long ans = 1LL;
	const int maxn = 4;
	char s[20];
	long long t = 0LL, d = 0LL;
	int x;
	cin >> s;
	for (int i = 0; i < maxn; ++i) {
		cin >> x;
		int p = 1 + int(log10(x));
		while (p--)t *= 10;
		t += x;
	}
	cin >> s;
	for (int i = 0; i < maxn; ++i) {
		cin >> x;
		int p = 1 + int(log10(x));
		while (p--)d *= 10;
		d += x;
	}
		
	
	long long D = t * t - 4 * d;
	double ds = sqrt(1.0 * D);
	double dk1 = 0.5 * (t + ds);
	int k1 = int(dk1);
	if (abs(dk1 - k1) < eps)--k1;
	int k2 = int(0.5 * (t - ds));
	
	
	cout << k1 - k2;;
}

int main()
{
	sol();
	return 0;
}

