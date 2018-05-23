#include <bits/stdc++.h>
#define LIMIT 1000
using namespace std;

void fcfs (int n, int arrival_time[], int burst_time[])
{
	vector < pair <int, int> > v(n);

	for (int i = 0; i < n; i++)
		v[i] = {arrival_time[i], i};

	sort(v.begin(), v.end());

	int wt[n], tat[n], current = v[0].first;

	for (auto u : v)
	{		
		wt[u.second] = current - u.first;
		current += burst_time[u.second];
		tat[u.second] = current - u.first;
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
	int n, arrival_time[LIMIT], burst_time[LIMIT];

	cout << "Enter number of processes: ";
	cin >> n;

	cout << "Enter arrival time for " << n << " processes:\n";
	for (int i = 0; i < n; i++)
		cin >> arrival_time[i];

	cout << "Enter burst time for " << n << " processes:\n";
	for (int i = 0; i < n; i++)
		cin >> burst_time[i];

	fcfs (n, arrival_time, burst_time);

	return 0;
}