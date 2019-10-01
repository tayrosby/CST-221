//Taylor Rosby
//CST - 221
//Monitors and Semaphores

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

struct
{
    pthread_mutex_t mutex;
    int deposit;
    int withdrawl;
    int amount;
    int buffer[100];
} shared = {PTHREAD_MUTEX_INITIALIZER};

void consume(int i)
{
    printf("withdrawn value %i\n", i);
}

int getAmount()
{
    int i = shared.amount;
    shared.amount--;
    return i;
}

void deposit()
{
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&mutex);
        if (shared.deposit < shared.buffer)
        {
            shared.amount++;
            shared.deposit++;
            printf("deposited value: %i \n", shared.deposit);
            sleep(1);
            sem_post(&mutex);
        }
        else
        {
            sem_post(&mutex);
        }
        sem_post(&mutex);
    }
}

void withdrawl()
{
    int x;
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&mutex);
        if (shared.withdrawl < shared.deposit)
        {
            x = getAmount();
            consume(x);
            shared.withdrawl++;
            sleep(1);
            sem_post(&mutex);
        }
        else
        {
            sem_post(&mutex);
        }
    }
}

int main()
{
    sem_init(&mutex, 0, 1);

    deposit();
    withdrawl();

    sem_destroy(&mutex);

}
