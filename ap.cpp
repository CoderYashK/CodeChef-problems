 /*You are given three integers A, B and C. You may perform the following operation an arbitrary number of times: choose one of the numbers A, B, C and either add 1 to it or subtract 1 from it.

Find the minimum number of operations required to make the sequence A, B, C an arithmetic progression, i.e. a sequence which satisfies B - A = C - B.
Input

    The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
    The first and only line of each test case contains three space-separated integers A, B and C.

Output

For each test case, print a single line containing one integer — the minimum required number of operations.
Constraints

    1 ≤ T ≤ 10,000
    -109 ≤ A, B, C ≤ 109

Subtasks

Subtask #1 (35 points): -102 ≤ A, B, C ≤ 102

Subtask #2 (65 points): original constraints
Example

Input:

5
-5 0 5
-5 7 6
-10 -100 20
1 -1 1
51 23 10

Output:

0
7
105
2
8

Explanation

Example case 1: No operations are needed because 0-(-5) = 5-0.

Example case 2: We can obtain an arithmetic progression in seven operations by adding 1 to A = -5 and subtracting 1 six times from B = 7.

Example case 3: We should add 1 to B 105 times.
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		ll a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		ll avg1, avg2;
		avg1 = (a + c) / 2;
		if(abs(a + c) % 2 == 1) {
			if(a + c < 0) {
				avg2 = avg1 - 1;
			} else {
				avg2 = avg1 + 1;
			}
		} else {
			avg2 = avg1;
		}
		if(avg1 != avg2) {
			if(abs(b - avg1) < abs(b - avg2)) {
				printf("%lld\n", abs(b - avg2));
			} else {
				printf("%lld\n", abs(b - avg1));
			}
		} else {
			printf("%lld\n", abs(b - avg1));
		}
	}
}