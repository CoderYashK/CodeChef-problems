/*
Chef and Subarrays Problem Code: CHEFARRB
All submissions for this problem are available.
Read problems statements in Mandarin Chinese, Russian and Vietnamese as well.

Chef has array A consisting of N integers. He calls a sub-array of the array good if the bitwise OR of all the elements in it is greater or equal than number K. Please help him to find out how many sub-arrays of array A are good!
Input

The first line of input contains T - number of test cases. T test cases follow.

For each test case, first line contains an integer N - number of elements in array, and integer K.

Second line contains N space separated non-negative integers denoting array A.
Output

For each test case, output an integer corresponding to the number of good sub-arrays of A in separate line.
Constraints
1 ≤ T, N, ≤ 100,000
0 ≤ Ai, K ≤ 109
1 ≤ Sum over all values of N in the input in a single test file ≤ 100,000
Example

Input:
2
3 3
1 2 3
3 6
3 4 5

Output:
4
2
*/

# include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<int>, vi;
typedef pair<int, int> pii;
const int M = 100010;
int a[M];

class node {
public:
	int l, r;
	int val;
};

const int MAXN = 1e5;
node st[4 * MAXN + 4];

node merge(node a, node b) {
	node res; 
	res.l = a.l;
	res.r = b.r;
	res.val = a.val | b.val;
	return res;
}

void makest(int j, int lx, int rx) {
	st[j].l = lx, st[j].r = rx;
	if(lx == rx) {
		st[j].val = a[lx];
	return;	
	}
	int mid = (lx + rx) / 2;
	makest(2 * j, lx, mid);
	makest(2 * j + 1, mid + 1, rx);
	st[j] = merge(st[2 *j], st[2 * j + 1]);
}

int query(int j, int lx, int rx) {
	if(st[j].l == lx, st[j].r == rx)
		return s[j].val;
	if(rx <= st[2 * j].r)
		return query(2 * j, lx, rx);
	if(lx >= st[2 * j + 1].l)
		return query(2 * j + 1, lx, rx);
	return (query(2 * j, lx, st[2 * j].r) | query(2 * j + 1, st[2 * j + 1].l, rx));
}
const int N = 100010;
int main() {
	int test;
	cin>>test;
	for(z = 1; z <= test; z++) {
		int n, k;
		cin>>n>>k;
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		makest(1, 1, n);
		ll res = 0;
		int i = 1, j = 1;
		while(i <= n and j <= n) {
			if(query(1, i, j) >= k) {
				res += (n + 1 - j);
				i++;
				j = max(j, i);
				continue;
			} else {
				j++;
			}
		}
		printf("%lld\n", res);
	}
}
