#include <stdio.h>
#define N 3

int buffer[1000], inp = 0, out = 0;

int mutex = 1, empty = N, full = 0;

void wait (int *s)
{
	if (*s > 0)
		(*s)--;
}

void signal (int *s)
{
	(*s)++;
}

void producer (int nextp)
{
	wait(&mutex);
	wait(&empty);

	buffer[inp] = nextp;
	printf("Item %d inserted in buffer.\n", nextp);
	inp = (++inp) % N;

	signal(&full);
	signal(&mutex);
}

void consumer ()
{
	wait(&mutex);
	wait(&full);

	int nextc = buffer[out];
	printf("Item %d taken from buffer.\n", nextc);
	out = (++out) % N;

	signal(&empty);
	signal(&mutex);
}

int main()
{
	int choice;

	printf("1. Producer\n2. Consumer\nAny other key to exit...\n");

	while (1)
	{
		scanf("%d", &choice);

		if (choice == 1)
		{
			int temp;

			scanf("%d", &temp);

			if (mutex == 1 && empty != 0)
				producer (temp);
			else
				printf("Buffer is full.\n");
		}
		else if (choice == 2)
		{
			if (mutex == 1 && full != 0)
				consumer();
			else
				printf("Buffer is empty.\n");
		}
		else
		{
			printf("Exiting...\n");
			break;
		}
	}

	return 0;
}