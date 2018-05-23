#include <bits/stdc++.h>
#define LIMIT 1000
#define PII pair <int, int>
using namespace std;

void priority_np (int n, int arrival_time[], int burst_time[], int priority[])
{
	// minimum priority queue
	priority_queue < PII, vector <PII>, greater <PII> > q;

	vector < pair <int, int> > v(n);

	for (int i = 0; i < n; i++)
		v[i] = {arrival_time[i], i};

	sort(v.begin(), v.end());

	int wt[n], tat[n], time = v[0].first;

	int count = n, index = 0;

	while (count)
	{
		while (index < n and v[index].first <= time)
		{
			int p_no = v[index].second;

			q.push({priority[p_no], p_no});
			index += 1;
		}

		if (q.empty())
		{
			index += 1;
			time = v[index].first;
			continue;
		}

		int p_no = q.top().second;
		q.pop();

		wt[p_no] = time - arrival_time[p_no];
		time += burst_time[p_no];
		tat[p_no] = time - arrival_time[p_no];

		count -= 1;
	}

	float total_wt = 0, total_tat = 0;

	cout << "\n\tWT\tTAT\n";

	for (int i = 0; i < n; i++)
	{
		cout << "P" << i << "\t";
		cout << wt[i] << "\t" << tat[i] << "\n";

		total_wt += wt[i];
		total_tat += tat[i];
	}

	cout << "\nAverage waiting time: " << total_wt / n << "\n";
	cout << "Average turnaround time: " << total_tat / n << "\n\n";

	return;
}

int main()
{
	int n, arrival_time[LIMIT], burst_time[LIMIT], priority[LIMIT];

	cout << "Enter number of processes: ";
	cin >> n;

	cout << "Enter arrival time for " << n << " processes:\n";
	for (int i = 0; i < n; i++)
		cin >> arrival_time[i];

	cout << "Enter burst time for " << n << " processes:\n";
	for (int i = 0; i < n; i++)
		cin >> burst_time[i];

	cout << "Enter priority for " << n << " processes:\n";
	for (int i = 0; i < n; i++)
		cin >> priority[i];

	priority_np (n, arrival_time, burst_time, priority);

	return 0;
}