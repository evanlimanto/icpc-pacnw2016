#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> pll;

int n, k;
vector<pll> v;
long long x, y;
vector<pll> neg, pos;
LL mymail, ans;

void func(vector<pll> &curv) {
	int sz = (int)curv.size();
	// move to edge
	int curpos = 0;
	LL used = min(curv[0].second, mymail);
	ans += abs(curv[0].first);

	mymail -= used;
	curv[0].second -= used;

	curpos = curv[0].first;

	for (int i = 0; i < sz; i++) {
		LL mail = curv[i].second;
		LL pos = curv[i].first;

		// move rightwards to this point
		ans += abs(curpos - pos);
		curpos = pos;

		// remove extra mail from myself
		used = min(mail, mymail);
		mymail -= used;
		mail -= used;

		if (mail) {
			// number of times to move back and forth from origin
			LL numtimes = (mail + k - 1) / k;
			ans += numtimes * abs(curpos) * 2;
			mymail = numtimes * k - mail;
		}
	}

	ans += abs(curpos);
	mymail = k;
}

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> x >> y;
		if (x < 0) {
			neg.push_back(make_pair(x, y));
		} else if (x > 0) {
			pos.push_back(make_pair(-x, y));
		}
	}

	sort(neg.begin(), neg.end());
	sort(pos.begin(), pos.end());

	mymail = k;
	if (!neg.empty()) func(neg);
	if (!pos.empty()) func(pos);
	cout << ans << endl;
	return 0;
}