#include <iostream>
using namespace std;

int mutex = 1, write = 1, readcount = 0;

void wait (int &s)
{
	if (s > 0)
		s--;
}

void signal (int &s)
{
	s++;
}

void reader()
{
	wait (mutex);

	readcount++;
	if (readcount == 1)
		wait (write);

	signal (mutex);

	printf("Read\n");

	wait (mutex);

	readcount--;
	if (readcount == 0)
		signal (write);

	signal (mutex);
}

void writer()
{
	wait (write);

	printf("Write\n");

	signal (write);
}

int main()
{
	int choice;

	printf("1. Read\n2. Write\nAny other key to exit...\n");

	while (true)
	{
		scanf("%d", &choice);

		if (choice == 1)
		{
			if (mutex and write)
				reader();
			else
				printf("Can not read.\n");
		}
		else if (choice == 2)
		{
			if (write)
				writer();
			else
				printf("Can not write.\n");
		}
		else
		{
			printf("Exiting...\n");
			break;
		}
	}

	return 0;
}