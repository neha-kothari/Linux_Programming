#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

void * task1(void * arg)
{
    printf("Thread 1 created\n");
}
void * task2(void * arg)
{
    printf("Thread 2 created\n");
}

void * task3(void * arg)
{
    printf("Thread 3 created\n");
}


int main(int argc, char * argv[])
{
    pthread_t tid_1, tid_2, tid_3;
    if(pthread_create(&tid_1, NULL, task1, NULL) != 0)
        ERR_EXIT("pthread_create() 1");
    if(pthread_create(&tid_2, NULL, task2, NULL) != 0)
        ERR_EXIT("pthread_create() 2");
    if(pthread_create(&tid_3, NULL, task3, NULL) != 0)
        ERR_EXIT("pthread_create() 3");
    pthread_exit(NULL);
    exit(EXIT_SUCCESS);
}