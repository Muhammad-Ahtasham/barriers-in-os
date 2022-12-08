#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 6
void *thread_function(void *arg);
pthread_barrier_t barrier;
int main(){
int res;
pthread_t a_thread[NUM_THREADS];
void *thread_result;
int thread_id[NUM_THREADS];
int i;
// Barrier initialization
if(pthread_barrier_init(&barrier, NULL, NUM_THREADS)){
perror("Could not create a barrier\n");
exit(EXIT_FAILURE);
}
for(i = 0; i < NUM_THREADS; i++) {
thread_id[i] = i;
res = pthread_create(&(a_thread[i]), NULL,
thread_function, (void *)&thread_id[i]);
if (res != 0){
perror("Thread creation failed");
exit(EXIT_FAILURE);
}
}
printf("Waiting for threads to finish...\n");
for(i = 0; i < NUM_THREADS; i++){
res = pthread_join(a_thread[i], &thread_result);
if (res == 0) {
printf("Picked up a thread\n");
}
else {
perror("pthread_join failed");
}
}
printf("All done\n");
exit(EXIT_SUCCESS);
}
void *thread_function(void *arg) {
int my_number = *(int *)arg;
int rand_num;
int result;
int i;
for (i=0; i<10; i++){
fprintf(stderr, "\tthread_function %d, %d\n",
my_number,i);
// Barrier’s usage
result = pthread_barrier_wait(&barrier);
if(result != 0 && result != PTHREAD_BARRIER_SERIAL_THREAD)
{
perror("Could not wait on barrier\n");
exit(-1);
}
}
printf("Bye from %d\n", my_number);
pthread_exit(NULL);
}