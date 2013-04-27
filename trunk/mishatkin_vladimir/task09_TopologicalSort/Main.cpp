#pragma comment (linker, "/STACK:214721677")
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <bitset>
#include <string>
using namespace std;
#define REP(i,n) for (int i=0, _n=(n)-1; i <= _n; ++i)
#define FOR(i,a,b) for (int i=(a), _b=(b); i <= _b; ++i)
#define X first
#define Y second
#define pb push_back
#define mp make_pair
#define sz(a) ((int) ((a).size()))
const double Pi = acos(-1.0);
const double eps = 1e-10;
const double phi = 0.5 + sqrt(1.25);
const int INF = 1000*1000*1000 + 7;
typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef pair <double, double> pdd;
typedef bool BOOL;
template < typename T > T sqr (T a) { return (a) * (a); }
template < typename T > T abs (T a) { return (a < 0) ? -(a) : (a); }
template < typename T > T gcd (T a, T b) { return (b) ? gcd(b, a % b) : a; }

#define YES 1
#define NO 0

const int maxn = 100010;

bitset<maxn> used;
vector<int> order;
vector< vector<int> > G;

void dfs1(int v)
{
    used[v] = 1;
    for (int i = 0; i < sz(G[v]); ++i)
        if (!used[ G[v][i] ])
            dfs1( G[v][i] );
    order.push_back(v);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n, m;
    scanf("%d%d\n", &n, &m);
    G.resize(n);
    for (int i = 0; i < m; ++i)
	{
        int a, b;
        scanf("%d%d\n", &a, &b);
        --a, --b;
        G[a].pb(b);
    }
    used.reset();
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs1(i);

    for (int i = 0; i < order.size() / 2; ++i)
        swap(order[i], order[ order.size()-1 - i]);

    for (int i = 0; i < order.size(); ++i)
	{
        if (i)
            printf(" ");
        printf("%d", order[i] + 1);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
