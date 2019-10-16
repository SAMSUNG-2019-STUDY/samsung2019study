#include<bits/stdc++.h>

using namespace std;

const int MAXN = 101;
struct point {
	int r, c, s, d, z;
	point() :r(0), c(0), s(0), d(0), z(0) {};
	point(int _r, int _c, int _s, int _d, int _z) :r(_r), c(_c), s(_s), d(_d), z(_z) {};
};

int r, c, m;
int cells[MAXN][MAXN];
queue<point> q;
int dy[] = { 0,-1,1,0,0 };
int dx[] = { 0,0,0,1,-1 };

int move() {
	vector<point> v;
	v.reserve(r * c + 1);

	while (!q.empty()) {
		point cur = q.front();
		q.pop();
		if (cells[cur.r][cur.c] == 0 || cells[cur.r][cur.c] != cur.z) continue;
		cells[cur.r][cur.c] = 0;
		int nd = cur.d;
		int nr = cur.r;
		int nc = cur.c;
		int dir = 0;
		int diff = 0;
		int ns = 0;
		dir = nd;

		if (nd == 1) {
			diff = nr - 1;
			if (diff < cur.s) {
				ns = cur.s - diff;
				if ((ns / (r - 1)) % 2 == 1)nr = r + (dy[1] * (ns % (r - 1))), dir = 1;
				else nr = 1 + (dy[2] * (ns % (r - 1))), dir = 2;
			}
			else {
				nr = nr + (dy[nd] * cur.s);
			}

		}
		else if (nd == 2) {
			diff = r - nr;
			if (diff < cur.s) {
				ns = cur.s - diff;
				if ((ns / (r - 1)) % 2 == 1) nr = 1 + (dy[2] * (ns % (r - 1))), dir = 2;
				else nr = r + (dy[1] * (ns % (r - 1))), dir = 1;
			}
			else {
				nr = nr + (dy[nd] * cur.s);
			}
		}
		else if (nd == 3) {
			diff = c - nc;
			if (diff < cur.s) {
				ns = cur.s - diff;
				if ((ns / (c - 1)) % 2 == 1) nc = 1 + (dx[3] * (ns % (c - 1))), dir = 3;
				else nc = c + (dx[4] * (ns % (c - 1))), dir = 4;
			}
			else {
				nc = nc + (dx[nd] * cur.s);
			}
		}
		else if (nd == 4) {
			diff = nc - 1;
			if (diff < cur.s) {
				ns = cur.s - diff;
				if ((ns / (c - 1)) % 2 == 1)nc = c + (dx[4] * (ns % (c - 1))), dir = 4;
				else nc = 1 + (dx[3] * (ns % (c - 1))), dir = 3;
			}
			else {
				nc = nc + (dx[nd] * cur.s);
			}
		}
		v.push_back(point(nr, nc, cur.s, dir, cur.z));
	}

	while (!v.empty()) {
		point cur = v.back();
		v.pop_back();
		cells[cur.r][cur.c] = max(cells[cur.r][cur.c], cur.z);
		if (cells[cur.r][cur.c] != cur.z) continue;
		q.push(cur);
	}

	return 0;
}

int getFish(int y, int x) {
	if (y > r) return 0;

	if (cells[y][x] > 0) {
		int ret = cells[y][x];
		cells[y][x] = 0;
		return ret;
	}

	return getFish(y + dy[2], x);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> r >> c >> m;

	for (int i = 0; i < m; i++) {
		int cr, cc, s, d, z;
		cin >> cr >> cc >> s >> d >> z;
		cells[cr][cc] = z;
		q.push(point(cr, cc, s, d, z));
	}

	int ans = 0;

	for (int i = 1; i <= c; i++) {
		int tc = getFish(1, i);
		ans += tc;
		move();
	}

	cout << ans << "\n";

	return 0;
}