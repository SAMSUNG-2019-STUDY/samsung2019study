#include<bits/stdc++.h>

using namespace std;

const int MAXN = 21;
int n, m, x, y, k;
int cells[MAXN][MAXN], num[MAXN];
int dy[] = { 0,0,0,-1,1 };
int dx[] = { 0,1,-1,0,0 };

int right() {
	int tmp = num[1];
	num[1] = num[4];
	num[4] = num[6];
	num[6] = num[3];
	num[3] = tmp;
	return 0;
}

int left() {
	int tmp = num[1];
	num[1] = num[3];
	num[3] = num[6];
	num[6] = num[4];
	num[4] = tmp;
	return 0;
}

int up() {
	int tmp = num[1];
	num[1] = num[5];
	num[5] = num[6];
	num[6] = num[2];
	num[2] = tmp;
	return 0;
}

int down() {
	int tmp = num[1];
	num[1] = num[2];
	num[2] = num[6];
	num[6] = num[5];
	num[5] = tmp;
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> y >> x >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> cells[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		int a;
		cin >> a;
		int ny = y + dy[a];
		int nx = x + dx[a];

		if (ny < 0 || ny >= n || nx < 0 || nx >= m) {
			continue;
		}

		if (a == 1) right();
		else if (a == 2) left();
		else if (a == 3) up();
		else down();
		y = ny;
		x = nx;

		if (cells[y][x] != 0) num[6] = cells[y][x], cells[y][x] = 0;
		else cells[y][x] = num[6];

		cout << num[1] << "\n";

	}


	return 0;
}