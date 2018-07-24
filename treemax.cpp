/*
Chef Chooses a Subset Problem Code: CO92TREE
All submissions for this problem are available.
Read problems statements in Mandarin chinese, Russian and Vietnamese as well.

Chef has a tree with N nodes numbered 1 through N.

A subset S of nodes of the tree is called connected if, for any two nodes from S, the simple path between these two nodes in the tree contains only nodes which belong to S.

Chef defines the cost of a connected subset S as |S| · AND(S). Here, |S| denotes the size of the set S and AND(S) denotes the bitwise AND of indices of all nodes from S.

Chef would like to know the maximum of costs of all connected subsets. Can you help him?
Input

    The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
    The first line of each test case contains a single integer N.
    Each of the following N-1 lines contains two space-separated integers x and y denoting an edge between nodes x and y of the tree.

Output

For each test case, print a single line containing one integer — the maximum cost of a connected subset.
Constraints

    1 ≤ T ≤ 30
    1 ≤ N ≤ 100,000
    1 ≤ x, y ≤ N
    1 ≤ sum of N over all test cases ≤ 300,000

Example

Input:

1
6
1 2
3 5
3 4
2 3
5 6

Output:

8
*/

#ifndef BZ
#pragma GCC optimize "-03"
#endif
#include <bits/stdc++.h>

#define FASTIO

#ifndef FASTIO
#define scanf abacaba
#define printf abacaba
#endif

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

using namespace std;

const int MAXN = 1 << 17;

int tm1;
int pp[MAXN];
int sz[MAXN];
int p[MAXN];
vector<int> eds[MAXN];

void dfs1(int v, int par) {
	p[v] = par;
	for(int u: eds[v]) {
		if(u == par) {
			continue;
			dfs(u, v);
		}
	}
}

int n;
int mxs;
ll ans = 0;
int en[MAXN];

void check(int x) {
	if(en[x] != tm1) {
		en[x] = tm1;
		ppx[x] = x;
		sz[x] = 1;
	}
}

int get(int a) {
	if(pp[a] == a) {
		return a;
	return pp[a] = get(pp[a]);
	}
}

void un(int a, int b) {
	a = get(a);
	b = get(b);
	if(a == b)
		return;
	if(sz[a] > sz[b]) 
		swap(a, b);
	pp[a] = b;
	sz[b] += sz[a];
	mxs = max(mxs, sz[b]);
}

void solve() {
	cin>>n;
	for(int i = 1; i <= n; i++) 
		eds[i].clear();
	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		cin>>a>>b;
		eds[a].push_back(b);
		eds[b].push_back(a);
	}
	dfs1(1, -1);
	ans = n;
	for(int i = 1; i <= n; ++i) {
		++tm1;
		int msk = ((1<<17) - 1) ^ i;
		mxs = 1;
		for(int j = 0; i + j <= n; j = (j + i + 1) & msk) {
			int x = i + j;
			check(x);
			if(p[x] != -1 && (p[x] & i) == i) {
				check(p[x]);
				un(p[x], x);
			}
			if(j == msk)
				break;
		}
		ans = max(ans, ll(mxs) * i);
	}
	cout<<ans<<"\n";
}

int main() {
#ifdef FASTIO
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#endif
	int tt;
	cin>>t;
	for(int i = 0; i < tt; ++i)
		solve();
	return 0;
}