#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

const int MAXN1 = 50000;
const int MAXN2 = 50000;
const int MAXM = 150000;
int n1, n2, edges, last[MAXN1], prv[MAXM], head[MAXM];
int matching[MAXN2], dist[MAXN1], Q[MAXN1];
bool used[MAXN1], vis[MAXN1];

void init(int _n1, int _n2) {
	n1 = _n1;
	n2 = _n2;
	edges = 0;
	fill(last, last + n1, -1);
}

void addEdge(int u, int v) {
	head[edges] = v;
	prv[edges] = last[u];
	last[u] = edges++;
}

void bfs() {
	fill(dist, dist + n1, -1);
	int sizeQ = 0;
	for (int u = 0; u < n1; u++) {
		if (!used[u]) {
			Q[sizeQ++] = u;
			dist[u] = 0;
		}
	}

	for (int i = 0; i < sizeQ; i++) {
		int u1 = Q[i];
		for (int e = last[u1]; e >= 0; e = prv[e]) {
			int u2 = matching[head[e]];
			if (u2 >= 0 && dist[u2] < 0) {
				dist[u2] = dist[u1] + 1;
				Q[sizeQ++] = u2;
			}
		}
	}
}

bool dfs(int u1) {
	vis[u1] = true;
	for (int e = last[u1]; e >= 0; e = prv[e]) {
		int v = head[e];
		int u2 = matching[v];
		if (u2 < 0 || (!vis[u2] && dist[u2] == dist[u1] + 1 && dfs(u2))) {
			matching[v] = u1;
			used[u1] = true;
			return true;
		}
	}
	return false;
}

int maxMatching() {
	fill(used, used + n1, false);
	fill(matching, matching + n2, -1);
	for (int res = 0;;) {
		bfs();
		fill(vis, vis + n1, false);
		int f = 0;
		for (int u = 0; u < n1; u++) {
			if (!used[u] && dfs(u))
				f++;
		}
		if (!f)
			return res;
		res += f;
	}
}

int n, m;
char arr[45][45];
int dr[] = {1, 0, -1, 0};
int dc[] = {0, -1, 0, 1};
bool valid(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}
bool flag[45][45], marked[45][45];
map<pair<int, int>, int> evenidx, oddidx;
int evenit, oddit;
vector<pair<int, int> > clouds;

void flood1(int x, int y) {
	queue<pair<int, int> > q;
	q.push(make_pair(x, y));
	flag[x][y] = true;
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();

		int curx = p.first;
		int cury = p.second;
		clouds.push_back(make_pair(curx, cury));
		marked[curx][cury] = true;

		for (int i = 0; i < 4; i++) {
			int xx = p.first + dr[i];
			int yy = p.second + dc[i];

			if (valid(xx, yy) && !flag[xx][yy] && arr[xx][yy] == 'C') {
				flag[xx][yy] = true;
				q.push(make_pair(xx, yy));
			}
		}
	}
}

void flood(int x, int y) {
	queue<pair<int, int> > q;
	q.push(make_pair(x, y));
	flag[x][y] = true;

	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int xx = p.first + dr[i];
			int yy = p.second + dc[i];

			if (valid(xx, yy) && !flag[xx][yy] && arr[xx][yy] == 'L') {
				flag[xx][yy] = true;
				q.push(make_pair(xx, yy));
			}
		}
	}
}

int main() {
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (arr[i][j] == 'L') {
				for (int k = 0; k < 4; k++) {
					int xx = i + dr[k];
					int yy = j + dc[k];

					if (valid(xx, yy) && arr[xx][yy] == 'C') {
						arr[xx][yy] = 'W';
					}
				}
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!flag[i][j] && arr[i][j] == 'L') {
				flood(i, j);
				ans++;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!flag[i][j] && arr[i][j] == 'C') {
				flood1(i, j);
			}
		}
	}

	int N = (int)clouds.size();
	int aa = 0, bb = 0;
	for (int i = 0; i < N; i++) {
		int xx = clouds[i].first;
		int yy = clouds[i].second;

		if ((xx + yy) % 2 == 0) {
			aa++;
			evenidx[clouds[i]] = evenit++;
		} else {
			bb++;
			oddidx[clouds[i]] = oddit++;
		}
	}

	// even, odd
	init(aa, bb);
	for (int i = 0; i < N; i++) {
		int xx = clouds[i].first;
		int yy = clouds[i].second;

		if ((xx + yy) % 2 == 0) {
			for (int j = 0; j < 4; j++) {
				int nextx = xx + dr[j];
				int nexty = yy + dc[j];
				if (valid(nextx, nexty) && marked[nextx][nexty]) {
					int iter = oddidx[make_pair(nextx, nexty)];
					addEdge(evenidx[clouds[i]], iter);
				}
			}
		}
	}

	int maxmatch = maxMatching();
	ans += ((int)clouds.size() - maxmatch);
	cout << ans << endl;
	return 0;
}