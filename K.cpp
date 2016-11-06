#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

int k, r;
int dp[55][55];
int main() {
	cin >> k >> r;

	double ans = 0.0;
	for (int i = 1; i <= k; i++) {
		int hi = (1 << k) - 1;
		int lo = (1 << k) - r + 1;
		int curhi = (1 << k) - (1 << i);
		int cur = (1 << k) - (1 << i) - r + 2;

		double zz = 1.0;
		while (cur <= curhi) {
			zz *= (cur * 1.0);
			cur++;

			if (zz <= 0.0)
				break;

			if (zz > 100.0 && lo <= hi) {
				zz /= (1.0 * lo);
				lo++;
			}
		}

		if (zz <= 0.0)
			continue;

		while (lo <= hi) {
			zz /= (1.0 * lo);
			lo++;
		}
		ans += zz;
	}
	printf("%.5lf\n", ans);
	return 0;
}