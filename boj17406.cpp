#include<bits/stdc++.h>

using namespace std;

const int MAXN = 51;
const int MAXM = 10;
const int MAXB = 1 << 7;
const int INF = 1e7;
struct point {
	int r, c, s;
	point() {};
	point(int _r, int _c, int _s) :r(_r), c(_c), s(_s) {};
};
int cells[MAXN][MAXN], arr[MAXN][MAXN];
int n, m, k;
int dy[] = { 1,0,-1,0 };
int dx[] = { 0,1,0,-1 };
vector<int> v;
point num[MAXM];
bool visit[MAXB];

void rotate(int ly, int lx, int ry, int rx) {

	int tmp = arr[ly][lx];
	int diff = ry - ly;

	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j < diff; j++) {
			int ny = ly + dy[i];
			int nx = lx + dx[i];
			if (i == 3 && j == diff - 1) arr[ly][lx] = tmp;
			else arr[ly][lx] = arr[ny][nx];
			ly = ny;
			lx = nx;
		}
	}
}

int solve(int digit) {
	if ((digit & ((1 << k) - 1)) == ((1 << k) - 1)) {

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				arr[i][j] = cells[i][j];
			}
		}

		for (auto next : v) {
			int ly = num[next].r - num[next].s;
			int lx = num[next].c - num[next].s;
			int ry = num[next].r + num[next].s;
			int rx = num[next].c + num[next].s;

			while (ly != ry || lx != rx) {
				rotate(ly, lx, ry, rx);
				ly += 1;
				lx += 1;
				ry -= 1;
				rx -= 1;
			}
		}

		int t = INF;
		for (int i = 1; i <= n; i++) {
			int sum = 0;
			for (int j = 1; j <= m; j++) {
				sum += arr[i][j];
			}
			t = min(t, sum);
		}
		return t;
	}

	int ret = INF;

	for (int i = 0; i < k; i++) {
		if (digit & (1 << i)) continue;
		v.push_back(i);
		ret = min(ret, solve(digit | (1 << i)));
		v.pop_back();
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> cells[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		cin >> num[i].r >> num[i].c >> num[i].s;
	}

	cout << solve(0) << "\n";


	return 0;
}