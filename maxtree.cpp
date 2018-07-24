/*
Chef and Average on a Tree Problem Code: L56AVG
Tweet
All submissions for this problem are available.
Read problems statements in Mandarin chinese, Russian and Vietnamese as well.

Chef has a tree with N nodes. Each node of the tree has an integer weight associated with it.

Let's define the cost of a sequence of numbers as the arithmetic mean of all elements of the sequence.

Next, let's define the cost of a path in the tree as the cost of the sequence of weights of all nodes belonging to the path. (It's possible for a path to contain only one node.)

A set of paths in the tree is called a correct path decomposition if each node of the tree belongs to exactly one of the paths from this set. The cost of a correct decomposition is defined as the minimum of costs of all paths in this decomposition.

Chef would like to find the maximum cost of a correct decomposition. Can you help him?
Input

    The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
    The first line of each test case contains a single integer N.
    The second line contains N space-separated integers A1, A2, ..., AN denoting the weights of nodes of the tree.
    Each of the following N-1 lines contains two space-separated integers x and y denoting an edge between nodes x and y.

Output

For each test case, print the maximum possible cost among all correct decompositions. You answer will be considered correct if its absolute error does not exceed 10-6.
Constraints

    1 ≤ T ≤ 20
    1 ≤ N ≤ 100,000
    1 ≤ sum of N over all test cases ≤ 200,000
    1 ≤ Ai ≤ 100,000

Subtasks

Subtask #1 (15 points, time limit 1 second):

    1 ≤ N ≤ 200
    1 ≤ sum of N over all testcases ≤ 400
    for each i (1 < i ≤ N), there is an edge connecting nodes i and i-1

Subtask #2 (35 points, time limit 1 second):

    1 ≤ N ≤ 200
    1 ≤ sum of N over all test cases ≤ 400

Subtask #3 (50 points, time limit 3 seconds): original constraints
Example

Input:
	
2
2
2 3
1 2
5
4 3 5 2 1
5 3
1 3
2 1
3 4

Output:

2.5000000
2.6666667

Explanation
https://codechef_shared.s3.amazonaws.com/download/upload/LTIME56/AVG-sample.png

Example case 1: It's better to use one path containing both nodes (blue in the picture above) rather than keep each node in a separate one-node path, since the first way gives decomposition cost equal to (A1 + A2) / 2 = (2+3) / 2 = 2.5, while the second one gives decomposition cost min(A1 / 1, A2 / 1) = min(2 / 1, 3 / 1) = 2.

Example case 2: It's optimal to decompose the tree into three paths (coloured red, green and yellow in the picture). This way, the red path has cost (A3 + A4 + A5) / 3 = (5 + 2 + 1) / 3 = 8 / 3 = 2.6666667, the green path has cost A1 = 4 and the yellow path has cost A2 = 3. Thus, the cost of this decomposition is 2.6666667.

It's possible to merge the green and yellow paths into one path with cost 3.5 without changing the decomposition cost. Any other decomposition has smaller cost
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long;
#define pb push_back;
#define mp make_pair;
#define ft first;
#define sd second;
#define slld(x) scanf("%lf", &x)
#define plld(x) printf("%0.8lf", x)
#define nl putchar('\n')
#define test int T; scanf("%d", &T); while(T--)

const ll MAXN = (ll)1e5 + 8;
const ll MOD = (ll)1e9 + 7;

int main() {
    ll i, j, k;
    test {
        cin>>N;
        double A[N];
        for(i = 0; i < N; i++)
            slld(A[i]);
        for(i = 1; i < N; i++)
                scanf("%lld%lld", &x, &y);
    }
    double sum = 0;
    for(i = 0; i < N; i++)
        sum += A[i];
        sum /= N;
        plld(sum);
        nl;
    }
    return 0;
}                
    }
}