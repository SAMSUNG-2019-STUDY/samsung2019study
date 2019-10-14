#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 1;
const int MAXM = 5000;
const int MOD = 1 << 8;
const int K = 50000000;

int test;
char sc[MAXN],si[MAXM];
int cp, ip, pp, a, b, c;
int num[MAXN],arr[MAXN];
vector<int> v;

bool chk(int l, int r) {
	int idx = l;

	for (int i = 0; i <=K; i++) {
		if (sc[idx] == '+') {
			arr[pp] = (arr[pp] + 1) % MOD;
		}
		else if (sc[idx] == '-') {
			arr[pp] = (arr[pp] - 1) % MOD;
		}
		else if (sc[idx] == '<') {
			pp = ((pp - 1) + a) % a;
		}
		else if (sc[idx] == '>') {
			pp = (pp + 1) % a;
		}
		else if (sc[idx] == '[') {
			if (arr[pp] == 0) {
				idx = num[idx];
				continue;
			}
		}
		else if (sc[idx] == ']') {
			if (arr[pp] != 0) {
				idx = num[idx];
				continue;
			}
			else {
				if(r==idx) return true;
			}
		}
		else if (sc[idx] == ',') {
			if (ip == c) arr[pp] = 255;
			else arr[pp] = si[ip++];
		}
		
		idx++;
		if (idx > r) idx = l;
	}

	return false;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> test;

	for (int tc = 1; tc <= test; tc++) {
		cin >> a >> b >> c;
		memset(num, 0, sizeof(num));
		memset(arr, 0, sizeof(arr));
		cp = ip = pp = 0;
		v.clear();

		for (int i = 0; i < b; i++) {
			cin >> sc[i];
			if (sc[i] == '[') {
				v.push_back(i);
			}
			else if (sc[i] == ']') {
				int cur = v.back();
				v.pop_back();
				num[i] = cur;
				num[cur] = i;
			}
		}

		for (int i = 0; i < c; i++) {
			cin >> si[i];
		}

		bool flag = true;

		while (cp<b) {
			if (sc[cp] == '+') {
				arr[pp] = (arr[pp] + 1) % MOD;
			}
			else if (sc[cp] == '-') {
				arr[pp] = (arr[pp] - 1) % MOD;
			}
			else if (sc[cp] == '<') {
				pp = ((pp - 1) + a) % a;
			}
			else if (sc[cp] == '>') {
				pp = (pp + 1) % a;
			}
			else if (sc[cp] == '[') {
				if (arr[pp] == 0) {
					cp = num[cp];
					continue;
				}
			}
			else if (sc[cp] == ']') {
				if (arr[pp] != 0) {
					if (!chk(num[cp], cp)) {
						flag = false;
						cout << "Loops " << num[cp] << " " << cp << "\n";
						break;
					}
				}
			}
			else if (sc[cp] == ',') {
				if (ip == c) arr[pp] = 255;
				else arr[pp]=si[ip++];
			}
		
			cp++;
		}

		if (flag) cout << "Terminates\n";
	}


	return 0;
}