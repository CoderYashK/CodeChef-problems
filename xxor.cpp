/*You are given a sequence A1, A2, ..., AN and Q queries. In each query, you are given two parameters L and R; you have to find the smallest integer X such that 0 ≤ X < 231 and the value of (AL xor X) + (AL+1 xor X) + ... + (AR xor X) is maximum possible.

Note: xor denotes the bitwise xor operation.
Input

    The first line of the input contains two space-separated integers N and Q denoting the number of elements in A and the number of queries respectively.
    The second line contains N space-separated integers A1, A2, ..., AN.
    Each of the next Q lines contains two space-separated integers L and R describing one query.

Output

For each query, print a single line containing one integer — the minimum value of X.
Constraints

    1 ≤ N ≤ 105
    1 ≤ Q ≤ 105
    0 ≤ Ai < 231 for each valid i

Subtasks

Subtask #1 (18 points):

    1 ≤ N ≤ 103
    1 ≤ Q ≤ 103
    0 ≤ Ai < 210 for each valid i

Subtask #2 (82 points): original constraints
Example

Input:

5 3
20 11 18 2 13
1 3
3 5
2 4

Output:

2147483629
2147483645
2147483645
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100005];
int tree[31][200010];

int n;
void build() {
	for(int j = 0; j < 31; j++) {
		for(int i = n - 1; i > 0; --i) {
			tree[j][i] = tree[j][i << 1] + tree[j][i << 1|1];
		}
	}
}

ll query(int l, int r) {
	int sl = l, sr = r;
	int res = 0, ans = 0;
	for(int i = 0; i < 31; i++) {
		res = 0; 
		l = sl;
		r = sr;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if(l & 1)
				res += tree[i][l++];
			if(r & 1)
				res += tree[i][--r];
		}
		if((sr - sl) % 2 == 1 && res <= (sr - sl) / 2){
			ans += pow(2, i);
		} else if((sr - sl) % 2 == 0 && res < (sr - sl) / 2) {
			ans += pow(2, i);
		}
	}
	return ans;
}
int main() {
	int q;
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
		ll num = a[i];
		for(int j = 0; j < 31; j++) {
			tree[j][n + 1] = num & 1;
			num >>= 1;
		}
	}
	build();
	for(int i = 0; i < q; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%lld5\n", query(l - 1, r));
	}
}