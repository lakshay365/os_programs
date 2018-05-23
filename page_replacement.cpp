#include <bits/stdc++.h>
using namespace std;

vector <int> pages;

int page_replacement_fifo (int capacity)
{
	int page_faults = 0;

	unordered_set <int> s;
	queue <int> indexes;

	for (auto page : pages)
	{
		if (s.size() < capacity and s.find(page) == s.end())
		{
			s.insert(page);
			page_faults++;
			indexes.push(page);
		}
		else if (s.size() >= capacity and s.find(page) == s.end())
		{
			s.erase(indexes.front());
			indexes.pop();

			s.insert(page);
			indexes.push(page);
			page_faults++;
		}
	}

	return page_faults;
}

int page_replacement_lru (int capacity)
{
	int page_faults = 0, i = 0;

	unordered_set <int> s;
	unordered_map <int, int> indexes;

	for (auto page : pages)
	{
		if (s.size() < capacity and s.find(page) == s.end())
		{
			s.insert(page);
			page_faults++;
		}
		else if (s.size() >= capacity and s.find(page) == s.end())
		{
			int lru = 1e9, val;

			for (auto avail_page : s)
			{
				if (indexes[avail_page] < lru)
				{
					lru = indexes[avail_page];
					val = avail_page;
				}
			}

			s.erase(val);
			s.insert(page);
			page_faults++;
		}
		
		indexes[page] = i++;
	}

	return page_faults;
}

int main()
{
	int capacity, var;

	cout << "Enter capacity: ";
	cin >> capacity;

	cout << "Pages: ";
	while (cin >> var)
		pages.push_back(var);

	/* Use ctrl + D or equivalent on other OS to end the input (signal EOF) */

	cout << "Page replacements (FIFO): " << page_replacement_fifo (capacity) << "\n";
	cout << "Page replacements (LRU) : " << page_replacement_lru (capacity) << "\n";

	return 0;
}