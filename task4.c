#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

/*
This program provides a possible solution for producer-consumer problem using mutex and semaphore.
I have used 5 producers and 5 consumers to demonstrate the solution. You can always play with these values.
*/

#define prod_MAX 1000
#define con_MAX  2500// Maximum items a producer can produce or a consumer can consume
#define BufferSize 10 // Size of the buffer

sem_t empty;
sem_t full;

int in = 0;
int out = 0;
int allcount=0;
int counter[10] = {0,0,0,0,0,0,0,0,0,0}; ;
int buffer[BufferSize];

pthread_mutex_t mutex;

void *producer(void *pno)
{   
    int item;
    for(int i = 0; i < prod_MAX; i++) {
        allcount++;
        item = allcount; // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno)
{   
    for(int i = 0; i < con_MAX; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        counter[out]++;
        printf("Consumer %d: Remove Item %d from %d for the %d time\n",*((int *)cno),item, out,counter[out]);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{   

    pthread_t pro[10],con[4];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int a[10] = {1,2,3,4,5,6,7,8,9,10}; //Just used for numbering the producer and consumer

    for(int i = 0; i < 10; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 4; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 10; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 4; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}