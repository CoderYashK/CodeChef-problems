/*Minion Chef likes to eat bananas a lot. There are N piles of bananas in front of Chef; for each i (1 ≤ i ≤ N), the i-th pile contains Ai bananas.

Chef's mother wants her to eat the bananas and be healthy. She has gone to the office right now and will come back in H hours. Chef would like to make sure that she can finish eating all bananas by that time.

Suppose Chef has an eating speed of K bananas per hour. Each hour, she will choose some pile of bananas. If this pile contains at least K bananas, then she will eat K bananas from it. Otherwise, she will simply eat the whole pile (and won't eat any more bananas during this hour).

Chef likes to eat slowly, but still wants to finish eating all the bananas on time. Therefore, she would like to choose the minimum K such that she is able to eat all the bananas in H hours. Help Chef find that value of K.
Input

    The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
    The first line of each test case contains two space-separated integers N and H denoting the number of piles and the number of hours after which Chef's mom will come home.
    The second line contains N space-separated integers A1, A2, ..., AN.

Output

For each test case, print a single line containing one integer — the minimum possible value of K.
Constraints

    1 ≤ T ≤ 10
    1 ≤ N ≤ 105
    N ≤ H ≤ 109
    1 ≤ Ai ≤ 109 for each valid i

Subtasks

Subtask #1 (30 points):

    1 ≤ N ≤ 100
    Ai ≤ 103 for each valid i

Subtask #2 (70 points): original constraints
Example

Input:

3
3 3
1 2 3
3 4
1 2 3
4 5
4 3 2 7

Output:

3
2
4

Explanation

Example case 1: With a speed of K = 3 bananas per hour,
 Chef can finish eating all the bananas in 3 hours. 
 It's the minimum possible speed with which she can eat 
 all the bananas in 3 hours. With a speed of 2 bananas per 
 hour, she would take at least 4 hours and with a speed 
 of 1 banana per hour, she would take at least 6 hours.
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, h;
void binary(ll start, ll end, ll *a, ll prev) {
	if(start > end) {
		printf("%lld\n", prev);
		return;
	}
	ll i = (start + end) / 2;
	ll cnt = 0, j;
	for(j = n - 1; i != 0 && j >= 0; j--) {
		cnt += a[j] / i;
		if(a[j] % i)
			cnt++;
		if(cnt > h)
			break;
	}
	if(cnt > h) {
		binary(i + 1, end, a, prev);
	} else if(cnt != 0 && cnt <= h) {
		binary(start, i - 1, a, i);
	}
}
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld%lld", &n, &h);
		ll a[n];
		for(int i = 0; i < n; i++) {
			scanf("%lld", &a[i]);
		}
		sort(a, a + n);
		ll num = h / n;
		ll start = a[0] / num;
		ll end = ceil((float)(a[n - 1] / (float)num));
		if(start == end && !start) {
			printf("1\n");
		} else {
			if(n >= 1 && n <= 100) {
				for(ll i = start; i <= end; i++) {
					ll cnt = 0, j;
					for(j = n - 1; i != 0 && j >= 0; j--) {
						cnt += a[j] / i;
						if(a[j] % i)
							cnt++;
						if(cnt > h)
							break;	
					}
					if(cnt != 0 && cnt <= h) {
						printf("%lld\n", i);
					}
				}
			} else {
				binary(start, end, a, -1);
			}
		}
	}
}