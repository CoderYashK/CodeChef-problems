/*
    The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
    The first and only line of each test case contains four space-separated integers a, b, c and d.

Output

For each test case, print a single line containing one string "YES" or "NO".
Constraints

    1 ≤ T ≤ 1,000
    1 ≤ a, b, c, d ≤ 10,000

Subtasks

Subtask #1 (100 points): original constraints
Example

Input:

3
1 1 2 2
3 2 2 3
1 2 2 2

Output:

YES
YES
NO */

#include<iostream>

using namespace std;

int main() {
	int a, b, c, d, t;
	int i;
	cin>>t;
	int s[t];
	for(i = 0; i < t; i++) {
		cin>>a>>b>>c>>d;
		if(a == b) {
			if(c == d) {
				s[i] = 1;	
			} else {
				s[i] = 0;
			}
		} else if(a == c) {
			if(b == d) {
				s[i] = 1;
			} else {
				s[i] = 0;
			}
		} else if(a == d) {
			if(b == c) {
				s[i] = 1;
			} else {
				s[i] = 0;
			}
		} else {
			s[i] = 0;
		}
	}

	for(i = 0; i < t; i++) {
		if(s[i] == 1) 
			cout<<"Yes"<<endl;
		else 
			cout<<"NO"<<endl;
	}
}