/*
Minions and Voting Problem Code: MINVOTE
All submissions for this problem are available.
Read problems statements in Mandarin chinese, Russian and Vietnamese as well.

There are N minions who are competing in an election of the president of the ACM (Association of Cute Minions). They are standing in a line in the order from minion 1 to minion N. For each i (1 ≤ i ≤ N), the i-th minion has an influence level of Si.

A single minion may cast any number of votes. Minion j will vote for minion i (i ≠ j) if and only if the influence level of the j-th minion is greater than or equal to the sum of influence levels of all the minions standing between them (excluding the i-th and j-th minion).

Your task is to find the number of votes received by each minion.
Input

    The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
    The first line of each test case contains a single integer N denoting the number of minions.
    The second line contains N space-separated integers S1, S2, ..., SN.

Output

For each test case, print a single line containing N space-separated integers. For each valid i, the i-th of these integers should denote the number of votes the i-th minion will get.
Constraints

    1 ≤ T ≤ 105
    1 ≤ N ≤ 105
    1 ≤ Si ≤ 109 for each valid i
    sum of N over all test cases won't exceed 106

Subtasks

Subtask #1 (30 points):

    1 ≤ N ≤ 500
    sum of N over all test cases won't exceed 10,000

Subtask #2 (70 points): original constraints
Example

Input:

2
4
4 3 2 1
5
1 2 2 3 1

Output:

1 2 3 2
2 3 2 3 1

Explanation

Example case 1:

    The first minion will get only a vote of the second minion.
    The second minion will get votes of the first and third minion.
    The third minion will get votes of the first, second and fourth minion.
    The fourth minion will get votes of the second and third minion.
*/

# include<bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[]) {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        int n;
        scanf("%d", &n);
        int arr[n], pref[n] = {0}, stuff[n] = {0};
        for(i = 0; i < n; i++)
            scanf("%d", &arr[i]);
       /* for(i = 1; i < (n - 1); i++) {
            pref[i] = pref[i - 1] + arr[i];
        } //Takes the numbers between the desired ones.
        for(i = n - 2; i > 0; i--) {
            stuff[i] = stuff[i + 1] + arr[i];
        }*/
        int ans[n] = {0};
        for(i = 0; i < n; i++) {
            int sum = 0;
            for(j = i + 1; j < n; j++) {
                if(arr[i] >= sum) {
                    ++ans[j];
                    sum += arr[j];
                } else {
                    break;
                }
            }
            sum = 0;
            for(j = i - 1; j >= 0; j--) {
                if(arr[i] >= sum) {
                    ++ans[j];
                    sum += arr[j];
                } else 
                    break;
            }
        }
        for(i = 0; i < n; i++)
            printf("%d ", ans[i]);
        printf("\n");
    }
    return 0;
}






