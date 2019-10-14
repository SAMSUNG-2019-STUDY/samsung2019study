#include<iostream>
#include<vector>

using namespace std;

//#define DEBUG

int N;
int population[11];
int map[11][11];
vector<int> part;
int visited1[11] = { 0, };
int visited2[11] = { 0, };
int answer = 10000000;

void input()
{
	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> population[i];

	for (int i = 0; i < N; i++)
	{
		int connect;

		//map[i][i] = 1;

		cin >> connect;
		for (int j = 0; j < connect; j++)
		{
			int district;
			cin >> district;
			map[i][district - 1] = map[district - 1][i] = 1;
		}
	}

#ifdef DEBUG
	cout << endl << "map" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << map[i][j] << " ";
		cout << endl;
	}
#endif
}

//나눈 선거구로 연결확인. dfs
void check1(int n)
{
	visited1[n] = 1;

	for (int i = 0; i < N; i++) //모든 지역 중에서
	{
		if (visited1[i] == 1 || visited1[i] == -1 || !map[n][i]) //방문한 지점이거나 우리 구역이 아니면 제외, 연결 안 된 지점 제외
			continue;

		//방문 안 했고 연결되어 있는 구역
		check1(i);
	}
}
void check2(int n)
{
	visited2[n] = 1;

	for (int i = 0; i < N; i++) //모든 지역 중에서
	{
		if (visited2[i] == 1 || visited2[i] == -1 || !map[n][i]) //방문한 지점이거나 우리 구역이 아니면 제외, 연결 안 된 지점 제외
			continue;

		//방문 안 했고 연결되어 있는 구역
		check2(i);
	}
}

//선거구 나누기 nC1~nC(n/2)
void permutation(int cnt, int r)
{
	if (part.size() == r)
	{
		vector<int> part2;
		int flag = 0;
		int succ = 1;
#ifdef DEBUG
		for (int i = 0; i < part.size(); i++)
			cout << part[i] << " ";
		cout << endl;
#endif
		//선거구 셋팅
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < part.size(); j++)
			{
				if (i == part[j])
				{
					flag = 1;
					break;
				}
			}
			if (flag == 1)
			{
				flag = 0;
				visited2[i] = -1; //2번 선거구 볼 때는 1번 선거구 볼 필요 없음
			}
			else
			{
				visited1[i] = -1; //1번 선거구 볼 때는 2번 선거구 볼 필요 없음
				part2.push_back(i); //2번 선거구
			}

		}

#ifdef DEBUG
		cout << "visited1 셋팅" << endl;
		for (int i = 0; i < N; i++)
			cout << visited1[i] << " ";
		cout << endl;
		cout << "visited2 셋팅" << endl;
		for (int i = 0; i < N; i++)
			cout << visited2[i] << " ";
		cout << endl;
#endif

		//나눈 선거구로 연결확인. 1번 선거구.
		check1(part[0]);
#ifdef DEBUG
		cout << "1번 선거구" << endl;
		for (int i = 0; i < 11; i++)
			cout << visited1[i] << " ";
		cout << endl;
#endif
		for (int i = 0; i < part.size(); i++)
		{
			if (visited1[part[i]] != 1) // 연결이 안 되어 있음
				succ = 0;
		}

		check2(part2[0]);
#ifdef DEBUG
		cout << "2번 선거구" << endl;
		for (int i = 0; i < 11; i++)
			cout << visited2[i] << " ";
		cout << endl;
#endif
		for (int i = 0; i < part2.size(); i++)
		{
			if (visited2[part2[i]] != 1) // 연결이 안 되어 있음
				succ = 0;
		}

		//연결되어있다면 인구차 구해서 저장
		if (succ)
		{
			int rslt, sum1 = 0, sum2 = 0;

			for (int i = 0; i < part.size(); i++)
				sum1 += population[part[i]];
			for (int i = 0; i < part2.size(); i++)
				sum2 += population[part2[i]];
			rslt = sum1 > sum2 ? sum1 - sum2 : sum2 - sum1;

#ifdef DEBUG
			cout << "연결!" << rslt << endl;
#endif
			answer = answer < rslt ? answer : rslt;
		}

		for (int i = 0; i < N; i++)
			visited1[i] = visited2[i] = 0;

		return;
	}

	for (int i = cnt; i < N; i++)
	{
		if (part.size() < r)
		{
			part.push_back(i);
			permutation(i + 1, r);
			part.pop_back();
		}
	}
}

void solve()
{
	//선거구 나누기 nC1~nC(n/2)
	for (int i = 1; i <= N / 2; i++)
		permutation(0, i);

}
int main()
{
	input();
	solve();
	if (answer == 10000000)
		cout << -1;
	else
		cout << answer;
}



