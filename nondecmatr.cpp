/*
Chef Restores a Matrix Problem Code: CO92MATR
All submissions for this problem are available.
Read problems statements in Mandarin chinese, Russian and Vietnamese as well.

Chef defines a non-decreasing matrix as a matrix that satisfies the following rules:

    For each row of the matrix, the elements of this row form a non-decreasing sequence.
    For each column of the matrix, the elements of this column form a non-decreasing sequence.

Chef has a matrix A with size N × M. Each element of this matrix is either unknown (denoted by -1) or a positive integer.

Chef would like to replace each unknown element of this matrix by a positive integer in such a way that the resulting matrix is non-decreasing. Find one possible resulting matrix or determine that it's impossible.
Input

    The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
    The first line of each test case contains two space-separated integers N and M.
    N lines follow. For each valid i, the i-th of these lines contains M space-separated integers Ai1, Ai2, ..., AiM denoting the elements of the i-th row of matrix A.

Output

    For each test case, if there is no way to obtain a non-decreasing matrix, print a single line containing the integer -1.
    Otherwise, print N lines describing the matrix obtained by replacing all unknown elements.
    For each valid i, the i-th of these lines should contain M space-separated integers denoting the elements of the i-th row of this matrix. Each of these elements should lie between 1 and 2,000,000,000 inclusive.

Constraints

    1 ≤ T ≤ 100
    1 ≤ N, M ≤ 100
    1 ≤ Aij ≤ 109 or Aij = -1 for each valid i, j

Example

Input:

2
4 4
1 2 2 3
1 -1 7 -1
6 -1 -1 -1
-1 -1 -1 -1
2 3
1 4 -1
1 -1 3

Output:

1 2 2 3
1 7 7 100
6 10 20 101
7 11 21 20000
-1

*/

# include <bits/stdc++.h>
# define pp pair<int, int>
# define mk make_pair
# define pb push_back
# define mod 10000000007
# define ll long long
using namespace std;

const int N = 105;

int a[N][N];

int main() {
    int t;
    cin>>t;

    while(t--) {
        int n, m;
        cin>>n>>m;

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                cin>>a[i][j];
            }
        }

        for(int i = 0; i <= n; i++)
            a[i][0] = 1;

        for(int i = 0; i <= m; i++)
            a[0][i] = 1;

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(a[i][j] == -1) {
                    int u = max(a[i][j - 1], a[i - 1][j]), v = u, l = u;
                    a[i][j] = u;
                }
            }
        }

        int fl = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(a[i][j] < a[i][j - 1]) {
                    fl = 0;
                    break;
                }
            }

            if(fl == 0) 
                break;
        }

        for(int j = 1; j <= m; j++) {
            if(fl == 0) 
                break;

            for(int i = 1; i <= n; i++) {
                if(a[i][j] < a[i -1][j]) {
                    fl = 0;
                    break;
                }
            }
        }

        if(!fl) 
            cout<<"-1\n";
        else {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= m; j++)
                    cout<<a[i][j]<<" ";
                cout<<"\n";
            }
        }

    }
    return 0;
}