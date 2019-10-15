//Taylor Rosby
//CST - 221
//http://tuxthink.blogspot.com/2012/12/deadlock-creation-and-avoidence-in.html

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t read_mutex;
pthread_mutex_t write_mutex;
clock_t start;
FILE *file1;

void *write(void *arg)
{
    char *str;
    pthread_mutex_lock(&write_mutex);
    sleep(1);
    pthread_mutex_lock(&read_mutex);
    printf("\nFile locked, please enter the message \n");
    file1 = fopen("temp", "w");
    scanf("%s", str);
    fprintf(file1, "%s", str);
    fclose(file1);
    pthread_mutex_unlock(&read_mutex);
    pthread_mutex_unlock(&write_mutex);
    printf("\nUnlocked the file you can read it now \n");
}

void *read(void *arg)
{
    char *str;
    pthread_mutex_lock(&read_mutex);
    sleep(1);
    pthread_mutex_lock(&write_mutex);
    printf("\nOpening file \n");
    file1 = fopen("temp", "r");
    fscanf(file1, "%s", str);
    printf("\nMessage from file is %s \n", str);

    fclose(file1);

    pthread_mutex_unlock(&write_mutex);
    pthread_mutex_unlock(&read_mutex);
}

void *kill(void *arg)
{
    do 
    {
        start = clock() / CLOCKS_PER_SEC;
    }
    while(start < 10);

     printf("\nTimed out \n ");
     exit(0);
}

main()
{
    start = clock() / CLOCKS_PER_SEC;

    pthread_t write_thread, read_thread, timer_thread;

    pthread_create(&write_thread, NULL, write, NULL);
    pthread_create(&read_thread, NULL, read, NULL);
    pthread_create(&timer_thread, NULL, kill, NULL);

    printf("\nCreated thread \n");

    pthread_join(timer_thread, NULL);
    pthread_join(write_thread, NULL);
    pthread_join(read_thread, NULL);

    return 0;
}
