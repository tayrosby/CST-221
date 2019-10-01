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

struct
{
    pthread_mutex_t mutex;
    int deposit;
    int withdrawl;
    int amount;         
    int buffer[100];
} shared={PTHREAD_MUTEX_INITIALIZER};

void consume(int i){
	printf("withdrawn value %i\n", i);
}

int getAmount(){
	int i =shared.amount;
	shared.amount--;
	return i;
}

void *deposit(void *arg)
{
    //int value;
    for(int i = 0; i < 20; i++)
    {
        pthread_mutex_lock(&shared.mutex);
        if(shared.deposit < shared.buffer)
        {
            shared.amount++;
            shared.deposit++;
            printf("deposited value: %i \n", shared.deposit);
            sleep(1);
            pthread_mutex_unlock(&shared.mutex);
        }
        else
        {
            pthread_mutex_unlock(&shared.mutex);
            return 0;
        }
    }
}

void *withdrawl(void *arg)
{
    int x;
    for(int i = 0; i < 20; i++)
    {
        pthread_mutex_lock(&shared.mutex);
        if(shared.withdrawl<shared.deposit)
        {
            x = getAmount();
            consume(x);
            shared.withdrawl++;
            sleep(1);
            pthread_mutex_unlock(&shared.mutex);
        }
        else 
        {
            pthread_mutex_unlock(&shared.mutex);
            return 0;
        }
    }
}

int main()
{
    pthread_t tid1, tid2;

     if(pthread_create(&tid1, NULL, deposit, NULL))
    {
        printf("\n ERROR creating deposit thread");
        exit(1);
    }
    if(pthread_create(&tid2, NULL, withdrawl, NULL))
    {
        printf("\n ERROR creating withdrawl thread");
        exit(1);
    }

   if(pthread_join(tid1, NULL))
    {
        printf("\n ERROR joining deposit thread");
        exit(1);
    }
    if(pthread_join(tid2, NULL))
    {
        printf("\n ERROR joining withdrawl thread");
        exit(1);
    }

    // Thread creation cleanup
    pthread_exit(NULL);
}
