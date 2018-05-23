#include <stdio.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFF_MAX 10
#define QUANTA 3

void wait (int *s)
{
	while (*s <= 0);
	
	*s = *s - 1;
}

void signal (int *s)
{
	*s = *s + 1;
}

int main ()
{
	int shmid_mutex, shmid_full, shmid_empty, shmid_loop;

	int *mutex, *full, *empty, *loop;

	char choice, c;

	shmid_mutex = shmget(IPC_PRIVATE, sizeof(int), 0777 | IPC_CREAT);
	shmid_full = shmget(IPC_PRIVATE, sizeof(int), 0777 | IPC_CREAT);
	shmid_empty = shmget(IPC_PRIVATE, sizeof(int), 0777 | IPC_CREAT);
	shmid_loop = shmget(IPC_PRIVATE, sizeof(int), 0777 | IPC_CREAT);

	mutex = (int *) shmat(shmid_mutex, 0, 0);
	full = (int *) shmat(shmid_full, 0, 0);
	empty = (int *) shmat(shmid_empty, 0, 0);
	loop = (int *) shmat(shmid_loop, 0, 0);

	*mutex = 1;
	*full = 0;
	*empty = BUFF_MAX;
	*loop = 1;

	printf("The producer consumer problem using semaphores\n\n");

	printf("Producer can produce process whenever it wishes.\n");
	printf("[Enter y in console to produce one, any other key to exit.]\n\n");

	printf("The consumer will consume a process every %d seconds.\n\n", QUANTA);

	if (fork() == 0)
	{
		do
		{
			sleep(QUANTA);

			wait(full);
			wait(mutex);

			printf("\nA process is consumed. Process left in buffer: %d\n", *full);

			signal(mutex);
			signal(empty);
		}
		while (*loop);
	}
	else
	{
		do
		{
			scanf("%c", &choice);

			// clear i/o buffer
			while ((c = getchar()) != '\n' && c != EOF);

			wait(empty);
			wait(mutex);

			if (choice == 'y')
			{
				printf("A process is produced! Process left in buffer: %d\n", *full + 1);
				signal(mutex);
				signal(full);
			}
			else
			{
				printf("Exiting the program!\n");
				*loop = 0;
				break;
			}
		}
		while(*loop);
	}

	shmdt(mutex);
	shmdt(full);
	shmdt(empty);
	shmdt(loop);

	shmctl(shmid_mutex, IPC_RMID, 0);
	shmctl(shmid_full, IPC_RMID, 0);
	shmctl(shmid_empty, IPC_RMID, 0);
	shmctl(shmid_loop, IPC_RMID, 0);

	return 0;
}