#include<bits/stdc++.h>

using namespace std;

const int MAXN = 10;
const int MAXM = 1025;
const int INF = 1e7;
const int MAXK = 5;
int cells[MAXN],coloredPaper[MAXK];
int ans;

bool IsFished() {
	for (int i = 0; i < 10; i++) {
		if (cells[i] != 0) return false;
	}
	return true;
}

int getPos(int& y, int& x) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (cells[i] & (1 << j)) {
				y = i;
				x = j;
				return 1;
			}
		}
	}
	return 0;
}

bool chk(int y,int x,int num) {
	if (y + num > 10 || x + num > 10) return false;

	for (int i = y; i < y + num; i++) {
		for (int j = x; j < x + num; j++) {
			if (cells[i] & (1 << j)) continue;
			return false;
		}
	}
	return true;
}

void painted(int y, int x, int num) {
	for (int i = y; i < y + num; i++) {
		for (int j = x; j < x + num; j++) {
			cells[i] = cells[i] ^ (1 << j);
		}
	}
}

int solve(int cnt) {
	if (IsFished()) {
		return cnt;
	}

	int y, x;
	y = x = 0;
	getPos(y, x);

	int ret = INF;

	for (int i = 5; i >= 1; i--) {
		if (chk(y, x, i) && coloredPaper[i]>0) {
			painted(y, x, i);
			coloredPaper[i]--;
			ret=min(ret,solve(cnt + 1));
			coloredPaper[i]++;
			painted(y, x, i);
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	for (int i = 1; i <= 5; i++) {
		coloredPaper[i] = 5;
	}

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			int a;
			cin >> a;
			if (a == 1) cells[i] = cells[i] | (1 << j);
		}
	}

	ans = solve(0);

	if (ans == INF) cout << "-1\n";
	else cout << solve(0) << "\n";
	
	return 0;
}