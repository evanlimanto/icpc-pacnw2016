#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <queue>
#include <iostream>

using namespace std;
typedef pair<int, int> pii;

int n, m;
char arr[55][55];
string s;
vector<pair<int, int> > adj[50 * 50 * 50 + 50 * 50 + 5];
int dist[50 * 50 * 50 + 50 * 50 + 5];
int getV(int x, int y, int level) {
	x--;
	y--;
	return level * (n * m) + (x * m + y);
}

int dr[] = {1, 0, -1, 0};
int dc[] = {0, -1, 0, 1};

int getD(char ch) {
	if (ch == 'D') return 0;
	if (ch == 'L') return 1;
	if (ch == 'U') return 2;
	if (ch == 'R') return 3;
	return -1;
}

int sx, sy, ex, ey;
bool inRange(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}
bool valid(int x, int y) {
	return inRange(x, y) && arr[x][y] != '#';
}
priority_queue<pii, vector<pii>, greater<pii> > pq;
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 'R') {
				sx = i;
				sy = j;
			} else if (arr[i][j] == 'E') {
				ex = i;
				ey = j;
			}
		}
	}
	cin >> s;

	for (int k = 0; k <= (int)s.length(); k++) {
		if (k < (int)s.length()) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					int curadj = getV(i, j, k);
					int nextadj = getV(i, j, k + 1);

					adj[curadj].push_back(make_pair(nextadj, 1));

					char ch = s[k];
					int ddir = getD(ch);
					int nextx = i + dr[ddir];
					int nexty = j + dc[ddir];

					if (valid(nextx, nexty)) {
						nextadj = getV(nextx, nexty, k + 1);
						adj[curadj].push_back(make_pair(nextadj, 0));
					} else {
						nextadj = getV(i, j, k + 1);
						adj[curadj].push_back(make_pair(nextadj, 0));
					}
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int curadj = getV(i, j, k);
				for (int z = 0; z < 4; z++) {
					int nextx = i + dr[z];
					int nexty = j + dc[z];
					if (valid(nextx, nexty)) {
						int nextadj = getV(nextx, nexty, k);
						adj[curadj].push_back(make_pair(nextadj, 1));
					}
				}
			}
		}
	}

	const int INF = 1000 * 1000 * 1000;
	fill(dist, dist + 50 * 50 * 50 + 50 * 50 + 3, INF);
	int startadj = getV(sx, sy, 0);

	dist[startadj] = 0;
	pq.push(make_pair(0, startadj));
	while (!pq.empty()) {
		pii p = pq.top();
		pq.pop();

		int nd = p.second;
		for (int i = 0; i < (int)adj[nd].size(); i++) {
			int next = adj[nd][i].first;
			int cost = adj[nd][i].second;
			if (dist[next] > dist[nd] + cost) {
				dist[next] = dist[nd] + cost;
				pq.push(make_pair(dist[next], next));
			}
		}
	}

	int ans = INF;
	for (int k = 0; k <= (int)s.length(); k++) {
		int ansadj = getV(ex, ey, k);
		if (ans > dist[ansadj])
			ans = dist[ansadj];
	}
	cout << ans << endl;
	return 0;
}