#include <bits/stdc++.h>
#define LIMIT 1000
using namespace std;

void round_robin (int n, int arrival_time[], int burst_time[], int time_slice)
{
	queue <int> q;

	vector < pair <int, int> > v(n);

	for (int i = 0; i < n; i++)
		v[i] = {arrival_time[i], i};

	sort(v.begin(), v.end());

	int wt[n], tat[n], temp[n], time = v[0].first;

	for (int i = 0; i < n; i++)
		temp[i] = burst_time[i];
	
	int count = n, index = 0;

	while (count)
	{
		while (index < n and v[index].first <= time)
		{
			q.push(v[index].second);
			index += 1;
		}

		if (q.empty())
		{
			index += 1;
			time = v[index].first;
			continue;
		}

		int p = q.front();
		q.pop();

		if (time_slice < temp[p])
		{
			temp[p] -= time_slice;
			time += time_slice;
			q.push(p);
		}
		else
		{
			time += temp[p];
			tat[p] = time - arrival_time[p];
			wt[p] = tat[p] - burst_time[p];

			temp[p] = 0;
			count -= 1;
		}
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
	int n, arrival_time[LIMIT], burst_time[LIMIT], time_slice;
	cout << "Enter number of processes: ";
	cin >> n;

	cout << "Enter arrival time for " << n << " processes:\n";
	for (int i = 0; i < n; i++)
		cin >> arrival_time[i];

	cout << "Enter burst time for " << n << " processes:\n";
	for (int i = 0; i < n; i++)
		cin >> burst_time[i];

	cout << "Enter time slice: " << endl;
	cin >> time_slice;

	round_robin (n, arrival_time, burst_time, time_slice);

	return 0;
}