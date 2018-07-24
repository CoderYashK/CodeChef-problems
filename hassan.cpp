/*Hussain is very bored, and has a lot of exams lined up next week. But he doesn't want to study. As usual, he decided to fail his exams and play with Hasan instead (who has already failed). Hussain invented this new game to play with Hasan.

Hussain shows Hasan a multiset of integers. (A multiset is a collection of elements where there can be duplicates). In every move Hussain removes a maximum number from this multiset and divides it by 2 (integer division, which is rounded down).

If after dividing, the number is still positive (greater than 0) he re-inserts it back into the multiset.

Before the start of the game, Hussain shows Hasan the numbers in his multiset.

Hussain asks Hasan, M questions. The i-th question will be denoted by Q[i], and Hasan must find the value of the number Hussain will be dividing (before he performs the division) after Q[i]-1 moves. That is, what is the value of the number on which the Q[i]-th division is performed?

Can you help Hasan and answer the queries?
Input

    The first line contains 2 space separated integers N, M denoting the initial size of the multiset and the number of questions respectively.
    The next line contains N space separated integers, the initial elements of the multiset.
    Of the next M lines, the i-th line will contain Q[i].

Output

    Output M lines, the i-th of which contains the answer for the i-th query.

Constraints

    1 ≤ N, M ≤ 106
    The queries are given in chronological order. That is, Q[i] > Q[i-1]
    Every element of the multiset will be a positive integer less than 263
    It's guaranteed that the set will contain at least one element at the time of any query.

Example

Input:
4 6
8 5 3 1
1
2
3
4
6
8

Output:
8
5
4
3
2
1
Explanation

We show the multiset sorted at each step, for convenience.

    Before any move, the multiset is (8, 5, 3, 1).
    In the first move, 8 is removed, dived by 2, and thus becomes 4, and then re-inserted. So, the multiset, after the first move is (5, 4, 3, 1).
    In the second move, 5 is removed and after division, it become 2, which is re-inserted. The multiset becomes (4, 3, 2, 1).
    After the third move, the multiset becomes (3, 2, 2, 1).
    After the fourth move, it becomes (2, 2, 1, 1).
    After the fifth move, it becomes (2, 1, 1, 1).
    After the sixth move, it becomes (1, 1, 1, 1).
    In the seventh move, 1 is removed, and on division, it no longer is greater than 0. Hence, it is not re-inserted. So, after the seventh move, the multiset becomes (1, 1, 1).
    After the eight move, the multiset becomes (1, 1).

The value being divided on the first move is 8. Hence the first output is 8.

The value being divided on the first move is 5. Hence the first output is 5.

The value being divided on the eight move is 1. Hence the last output is 1.

Author: Master Yash Kshatriya

Tester: 6★kingofnumbers

Editorial: https://discuss.codechef.com/problems/COOK82C

Tags: cook82, deadwing97, easy-medium, queue

Date Added: 20-05-2017

Time Limit: 2 secs

Source Limit: 50000 Bytes

Languages: C, CPP14, JAVA, PYTH, PYTH 3.5, PYPY, CS2, PAS fpc, PAS gpc, RUBY, PHP, GO, NODEJS, HASK, SCALA, D, PERL, FORT, WSPC, ADA, CAML, ICK, BF, ASM, CLPS, PRLG, ICON, SCM qobi, PIKE, ST, NICE, LUA, BASH, NEM, LISP sbcl, LISP clisp, SCM guile, JS, ERL, TCL, PERL6, TEXT, SCM chicken, CLOJ, FS
Submit
My Submissions
All Submissions
Successful Submissions */

#include<bits/stdc++.h>
using namespace std;

#define fl(a, b) for (int i = a; i < b; ++i)

int main() {
	int n, q;
	cin>>n>>q;

	long long tempArr[n];

	queue<long, long> num1, num2;

	fl(0, n) {
		cin>>tempArr[i];
	}

	sort(tempArr, tempArr+n);
	for(int i = n -1; i >= 0; --i) {
		num1.push(tempArr[i]);
	}
	num2.push(num1.front());
	num1.pop();
	long long temp1;
	int counter = 1; k;

	while(q--) {
		scanf("%d", &k);
		for(;counter <= k; counter++) {
			if(num1.front() > num2.front()) {
				temp1 = num1.front();
				num1.pop();
			} else {
				temp1 = num2.front();
				num2.pop();
			}
			num2.push(temp1 / 2);
		}
		cout<<temp1<<endl;
	} 

}
