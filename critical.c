#include <stdio.h>
#include <pthread.h>

int flag[2], turn, ans = 0;
const int max = 1e9;

void init()
{
	flag[0] = flag[1] = turn = 0;
}

void lock (int self)
{
	flag[self] = 1;
	turn = 1 - self;

	while (flag[1 - self] && turn == 1 - self);
}

void unlock (int self)
{
	flag[self] = 0;
}

void *func (void *arg)
{
	int self = *((int *) arg);

	printf("Thread entered: %d\n", self);

	lock(self);

	for (int i = 0; i < max; i++)
		ans++;

	unlock(self);
}

int main()
{
	pthread_t pid1, pid2;

	init();

	int p1 = 0, p2 = 1;

	pthread_create(&pid1, NULL, func, (void *) &p1);
	pthread_create(&pid2, NULL, func, (void *) &p2);

	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);

	printf("Actual count: %d | Expected count: %d\n", ans, max * 2);

	return 0;
}

