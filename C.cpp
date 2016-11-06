#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

int n, k, r, x, arr[100005];
int main() {
	cin >> n >> k >> r;
	for (int i = 1; i <= k; i++) {
		cin >> x;
		arr[x] = 1;
	}

	int cur = 0, ans = 0;
	for (int i = 1; i <= n; i++) {
		cur += arr[i];
		if (i > r) cur -= arr[i-r];
		if (i >= r && cur < 2) {
			ans += (2 - cur);

			int cnt = 2 - cur;
			for (int j = i; j >= i - r + 1; j--) {
				if (cnt && !arr[j]) arr[j] = 1, cnt--;
				if (!cnt) break;
			}
			cur = 2;
		}
	}

	cout << ans << endl;
	return 0;
}