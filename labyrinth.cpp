#include<bits/stdc++.h>
using namespace std;

#define mp make_pair;

class compare {
	bool operator() (pair<int, pair<int, int>> n1, pair<int, pair<int, int>> n2) {
		return n1.first < n2.first;
	}
};

int arr[1001][1001] = {0};
int ans[1001][1001] = {0};
int visited[1001][1001] = {0};

priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, compare>q;

void bfs(int n, int m) {
	while(!q.empty()) {
		pair<int, pair<int, int>> p = q.top();
		q.pop();
		if(visited[p.second.first][p.second.second])
			continue;
		visited[p.second.first][p.second.second] = 1;
		int cost = p.first;
		if(cost <= 0)
			break;
		int i = p.second.first, j = p.second.second;
		ans[i][j] = cost;
		if(i > 0 && !visited[i - 1][j] && !ans[i - 1][j] && arr[i - 1][j] != -1)
			q.push(mp(cost - 1, mp(i - 1, j)));
		if(i < n - 1 && !visited[i + 1][j] && !ans[i + 1][j] && arr[i + 1][j] != -1)
			q.push(mp(cost - 1, mp(i + 1, j)));
		if(j > 0 && !visited[i][j - 1] && !ans[i][j - 1] && arr[i][j - 1] != -1)
			q.push(mp(cost - 1, mp(i, j - 1)));
		if(j < m - 1 && !visited[i][j + 1] && !ans[i][j + 1] && arr[i][j + 1] != -1)
			q.push(mp(cost - 1, mp(i, j + 1)));
	}
}

int main() {
	int t, i, j;
	scanf("%d", &t);
	while(t--) {
		memset(ans, 0, sizeof(ans));
		memset(arr, 0, sizeof(arr));
		memset(visited, 0, sizeof(visited));
		while(!q.empty())
			q.pop();
		int n, m;
		scanf("%d%d" &n, &m);
		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++) {
				scanf("%d", &arr[i][j]);
				if(arr[i][j] > 0)
					q.push(mp(arr[i][j] + 1, mp(i, j)));
			}
		}
		bfs(n, m);
		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++) {
				if(arr[i][j] == -1)
					printf("B");
				else if(ans[i][j] == 0)
					printf("N");
				else
					printf("Y");

			}
			printf("\n");
		}

	}
	return 0;
}