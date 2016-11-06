#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;
string s;
int dp[55];
int main() {
	cin >> s;
	int n = (int)s.length();
	int ans = 1;

	for (int i = 0; i < n; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (s[i] > s[j])
				dp[i] = max(dp[i], dp[j] + 1);
		}
		ans = max(ans, dp[i]);
	}
	cout << 26 - ans << endl;
	return 0;
}