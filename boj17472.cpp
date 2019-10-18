#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
struct point {
	int a, b, dist;
	point(int _a, int _b, int _dist) :a(_a), b(_b), dist(_dist) {};
};
const int MAXN = 11;
const int MAXM = 101;
int n, m, idx;
int cells[MAXN][MAXN], visit[MAXN][MAXN], p[MAXM];
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
vector<point> v;

int find(int pos) {
	if (p[pos] == pos) return pos;
	return p[pos] = find(p[pos]);
}

int merg(int a, int b) {
	int na = find(a);
	int nb = find(b);

	if (na != nb) {
		p[nb] = na;
		return 1;
	}

	return 0;
}

bool cmp(point a, point b) {
	return a.dist < b.dist;
}
int bfs(int y, int x) {
	queue<pi> q;

	q.push({ y,x });
	visit[y][x] = idx;

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int i = 0; i <= 3; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
			if (visit[ny][nx] != 0 || cells[ny][nx] == 0) continue;

			visit[ny][nx] = idx;
			q.push({ ny,nx });

		}
	}
	return 0;
}

pi getdist(int y, int x, int num, int cnt, int dir) {
	if (y < 0 || y >= n || x < 0 || x >= m || visit[y][x] == num) return { -1,-1 };
	if (visit[y][x] != num && visit[y][x] > 0) return { cnt,visit[y][x] };

	return getdist(y + dy[dir], x + dx[dir], num, cnt + 1, dir);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	idx = 1;

	cin >> n >> m;

	for (int i = 0; i <= n * m; i++) {
		p[i] = i;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> cells[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visit[i][j] > 0 || cells[i][j] == 0) continue;
			bfs(i, j);
			idx++;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visit[i][j] == 0) continue;
			for (int k = 0; k <= 3; k++) {
				pi tmp = getdist(i + dy[k], j + dx[k], visit[i][j], 0, k);
				if (tmp.first == -1 || tmp.first < 2) continue;
				v.push_back(point(visit[i][j], tmp.second, tmp.first));
			}
		}
	}


	idx--;
	sort(v.begin(), v.end(), cmp);
	int ans = 0;
	int cnt = 0;
	bool flag = false;

	for (auto next : v) {
		int a = next.a;
		int b = next.b;
		int dist = next.dist;

		if (merg(a, b)) {
			ans += dist;
			cnt++;

			if (cnt == idx - 1) {
				flag = true;
				break;
			}
		}
	}

	if (!flag) cout << "-1\n";
	else cout << ans << "\n";

	return 0;
}