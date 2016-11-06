#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

int n, q;
LL a[200 * 1000 + 100];
vector<pair<pair<int, int>, pair<LL, int> > > queries; // l, r, v, id
vector<pair<int, LL > > answers; // id, ans
int mq[200 * 1000 + 100], qhead, qtail;

bool dec_value_cmp(int x, int y) {
	return a[x] > a[y];
}

void handle_and_pop_query() {
	--q;
	pair<pair<int, int>, pair<LL, int> > query = queries[q];
	queries.pop_back();
	int l = query.fi.fi, r = query.fi.se, qid = query.se.se;
	LL v = query.se.fi;

	int pos = l - 1;
	LL ans = v;
	while (1) {
		// after pos
		int startidx = lower_bound(mq + qhead, mq + qtail, pos + 1) - mq;
		if (startidx >= qtail || mq[startidx] > r) {
			break;
		}

		// first a[i] that <= remainder
		a[0] = ans;
		int modidx = lower_bound(mq + startidx, mq + qtail, 0) - mq;
		if (modidx >= qtail || mq[modidx] > r) {
			break;
		}
		pos = mq[modidx];
		if (pos <= r) {
			ans %= a[pos];
		}
	}
	answers.pb(mp(qid, ans));
}

int main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= q; i++) {
		int l, r;
		LL v;
		cin >> v >> l >> r;
		queries.pb(mp(mp(l, r), mp(v, i)));
	}

	sort(queries.begin(), queries.end());
	qhead = qtail = 200 * 1000 + 30;
	for (int i = n; i >= 1; i--) {
		// add to monoqueue
		while (qtail > qhead && a[mq[qhead]] >= a[i]) {
			qhead++;
		}
		mq[--qhead] = i;
		while (q > 0 && queries[q-1].fi.fi == i) {
			handle_and_pop_query();
		}
	}
	sort(answers.begin(), answers.end());
	for (int i = 0; i < (int)answers.size(); i++) {
		cout << answers[i].se << endl;
	}
}