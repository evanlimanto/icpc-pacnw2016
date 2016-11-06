#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long LL;
LL n; int k;
vector<pair<LL, LL> > v;
LL dp[400005];
vector<LL> compress;
vector<LL> adj[400005];
int main() {
	cin >> n >> k;
	for (int i = 1; i <= k; i++) {
		LL x, y;
		cin >> x >> y;
		v.push_back(make_pair(x, y));
		compress.push_back(x);
		compress.push_back(y);
	}

	compress.push_back(0);
	compress.push_back(n);
	sort(compress.begin(), compress.end());
	compress.erase(unique(compress.begin(), compress.end()), compress.end());

	for (int i = 0; i < k; i++) {
		LL x = v[i].first;
		LL y = v[i].second;

		x = lower_bound(compress.begin(), compress.end(), x) - compress.begin();
		y = lower_bound(compress.begin(), compress.end(), y) - compress.begin();
		v[i] = make_pair(x, y);
		adj[y].push_back(x);
	}

	dp[0] = 0;
	for (int i = 1; i < (int)compress.size(); i++) {
		dp[i] = dp[i-1] + (compress[i] - compress[i-1]);
		int sz = (int)adj[i].size();
		for (int j = 0; j < sz; j++) {
			int left = adj[i][j];
			dp[i] = min(dp[i], dp[left - 1] + compress[left] - compress[left - 1] - 1);
		}
	}

	LL ans = dp[(int)compress.size() - 1];
	cout << ans << endl;
	return 0;
}