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

//���� ���ű��� ����Ȯ��. dfs
void check1(int n)
{
	visited1[n] = 1;

	for (int i = 0; i < N; i++) //��� ���� �߿���
	{
		if (visited1[i] == 1 || visited1[i] == -1 || !map[n][i]) //�湮�� �����̰ų� �츮 ������ �ƴϸ� ����, ���� �� �� ���� ����
			continue;

		//�湮 �� �߰� ����Ǿ� �ִ� ����
		check1(i);
	}
}
void check2(int n)
{
	visited2[n] = 1;

	for (int i = 0; i < N; i++) //��� ���� �߿���
	{
		if (visited2[i] == 1 || visited2[i] == -1 || !map[n][i]) //�湮�� �����̰ų� �츮 ������ �ƴϸ� ����, ���� �� �� ���� ����
			continue;

		//�湮 �� �߰� ����Ǿ� �ִ� ����
		check2(i);
	}
}

//���ű� ������ nC1~nC(n/2)
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
		//���ű� ����
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
				visited2[i] = -1; //2�� ���ű� �� ���� 1�� ���ű� �� �ʿ� ����
			}
			else
			{
				visited1[i] = -1; //1�� ���ű� �� ���� 2�� ���ű� �� �ʿ� ����
				part2.push_back(i); //2�� ���ű�
			}

		}

#ifdef DEBUG
		cout << "visited1 ����" << endl;
		for (int i = 0; i < N; i++)
			cout << visited1[i] << " ";
		cout << endl;
		cout << "visited2 ����" << endl;
		for (int i = 0; i < N; i++)
			cout << visited2[i] << " ";
		cout << endl;
#endif

		//���� ���ű��� ����Ȯ��. 1�� ���ű�.
		check1(part[0]);
#ifdef DEBUG
		cout << "1�� ���ű�" << endl;
		for (int i = 0; i < 11; i++)
			cout << visited1[i] << " ";
		cout << endl;
#endif
		for (int i = 0; i < part.size(); i++)
		{
			if (visited1[part[i]] != 1) // ������ �� �Ǿ� ����
				succ = 0;
		}

		check2(part2[0]);
#ifdef DEBUG
		cout << "2�� ���ű�" << endl;
		for (int i = 0; i < 11; i++)
			cout << visited2[i] << " ";
		cout << endl;
#endif
		for (int i = 0; i < part2.size(); i++)
		{
			if (visited2[part2[i]] != 1) // ������ �� �Ǿ� ����
				succ = 0;
		}

		//����Ǿ��ִٸ� �α��� ���ؼ� ����
		if (succ)
		{
			int rslt, sum1 = 0, sum2 = 0;

			for (int i = 0; i < part.size(); i++)
				sum1 += population[part[i]];
			for (int i = 0; i < part2.size(); i++)
				sum2 += population[part2[i]];
			rslt = sum1 > sum2 ? sum1 - sum2 : sum2 - sum1;

#ifdef DEBUG
			cout << "����!" << rslt << endl;
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
	//���ű� ������ nC1~nC(n/2)
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



