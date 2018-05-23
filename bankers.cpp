#include <bits/stdc++.h>
#define N 100
#define M 100
using namespace std;

int n, m, q, available[M], allocation[N][M], maximum[N][M];
vector <int> safe_sequence;

bool safety_algo()
{
	safe_sequence.clear();

	int work[m];

	for (int i = 0; i < m; i++)
		work[i] = available[i];

	bool finish[n] = {false};

	int need[n][m];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			need[i][j] = maximum[i][j] - allocation[i][j];

	while (true)
	{
		bool should_break_this_loop = true;

		for (int i = 0; i < n; i++)
		{
			if (finish[i])
				continue;

			bool resources_can_be_satisfied = true;

			for (int j = 0; j < m; j++)
			{
				if (need[i][j] > work[j])
				{
					resources_can_be_satisfied = false;
					break;
				}
			}

			if (resources_can_be_satisfied)
			{
				finish[i] = true;

				for (int j = 0; j < n; j++)
					work[j] += allocation[i][j];

				safe_sequence.push_back(i + 1);

				should_break_this_loop = false;
			}
		}

		if (should_break_this_loop)
			break;
	}

	for (int i = 0; i < n; i++)
	{
		if (!finish[i])
		{
			printf("\nOops! Deadlock.\n");
			return false;
		}
	}

	return true;
}

void request_algo(int process, int request[])
{
	int need[m];

	for (int j = 0; j < m; j++)
		need[j] = maximum[process][j] - allocation[process][j];

	for (int i = 0; i < m; i++)
	{
		if (available[i] < need[i])
		{
			printf("I'm afraid! Not this much resources are currently available.\n");
			return;
		}

		if (request[i] > need[i])
		{
			printf("Err..! Process %d is not allowed to access this many resources.\n", process + 1);
			return;
		}
	}

	for (int i = 0; i < m; i++)
	{
		allocation[process][i] += request[i];
		need[process] -= request[i];
		available[i] -= request[i];
	}

	if (safety_algo())
	{
		char ch;

		printf("This request can be served. Do you want to? [Y/n]: ");
		cin >> ch;

		if (ch != 'Y' || ch != 'y')
		{
			for (int i = 0; i < m; i++)
			{
				allocation[process][i] -= request[i];
				need[process] += request[i];
				available[i] += request[i];
			}
		}
	}
}

int main()
{
	printf("Enter number of processes: ");
	scanf("%d", &n);

	printf("Enter number of resources: ");
	scanf("%d", &m);

	printf("\nEnter number of instances for %d resource(s):\n", m);
	for (int i = 0; i < m; i++)
		scanf("%d", available + i);

	printf("\nEnter number of resources' instances ALLOCATED for each process:\n");
	for (int i = 0; i < n; i++)
	{
		printf("Process %d: ", i + 1);

		for (int j = 0; j < m; j++)
			scanf("%d", &allocation[i][j]);
	}

	printf("\nEnter MAXIMUM number of resources' instance that can be allocated for each process:\n");
	for (int i = 0; i < n; i++)
	{
		printf("Process %d: ", i + 1);

		for (int j = 0; j < m; j++)
			scanf("%d", &maximum[i][j]);
	}

	if (safety_algo())
	{
		printf("\nSafe sequence: ");

		for (auto p : safe_sequence)
			printf("%d ", p);

		printf("\n");
	}

	printf("\nEnter number of requests: ");
	scanf("%d", &q);

	while (q--)
	{
		int process, request[m];

		printf("\nRequesting process: ");
		scanf("%d", &process);

		printf("Request: ");
		for (int i = 0; i < m; i++)
			scanf("%d", request + i);

		request_algo(process - 1, request);
	}

	return 0;
}