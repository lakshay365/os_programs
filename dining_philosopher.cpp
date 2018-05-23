/*
 * It is my approach to solve
 * this problem using threads.
 * 
 * Vanjani's code is commented
 * at the bottom of this file.
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include <queue>

#define QUANTA 1 + rand() % 10

int chopstick[5];

void wait (int *s)
{
    while (*s <= 0);
    (*s)--;
}

void signal (int *s)
{
    (*s)++;
}

void *func (void *arg)
{
    int i = *((int *) arg);

    printf ("Philosopher %d is waiting for chopstick %d.\n", i, i);
    wait (chopstick + i);
    printf ("Philosopher %d has got chopstick %d.\n", i, i);

    int j = (i + 1) % 5;

    printf ("Philosopher %d is waiting for chopstick %d.\n", i, j);
    wait (chopstick + j);
    printf ("Philosopher %d has got chopstick %d.\n", i, j);

    printf("Philopher %d is eating...\n", i);
    sleep(QUANTA);
    printf("Philosopher %d is now full.\n", i);

    signal (chopstick + i);
    printf ("Philosopher %d has released chopstick %d.\n", i, i);

    signal (chopstick + j);
    printf ("Philosopher %d has released chopstick %d.\n", i, j);
}

int main ()
{
    for (int i = 0; i < 5; i++)
        chopstick[i] = 1;

    std::queue <pthread_t> q;

    while (true)
    {
        int arg;

        scanf("%d", &arg);

        if (arg < 0 || arg > 4)
            break;

        pthread_t p;

        pthread_create(&p, NULL, func, (void *) &arg);
    }

    while (!q.empty())
    {
        pthread_join (q.front(), NULL);
        q.pop();
    }

    return 0;
}


// #include <bits/stdc++.h>
// using namespace std;

// int chopstick[5];

// void wait(int &i)
// {
//   if (i > 0)
//     i--;
// }

// void signal(int &i)
// {
//   i++;
// }

// void philosopher(int i)
// {
//   wait(chopstick[i]);
//   wait(chopstick[(i + 1) % 5]);

//   cout << "Philosopher " << i << " eat" << endl;

//   signal(chopstick[i]);
//   signal(chopstick[(i + 1) % 5]);

//   cout << "Philospoher " << i << " think" << endl;
// }

// int main()
// {
//   for (int i = 0; i < 5; i++)
//     chopstick[i] = 1;

//   for (int i = 0; i < 5; i++)
//     if (chopstick[i] == 1 && chopstick[(i + 1) % 5] == 1)
//       philosopher(i);
// }