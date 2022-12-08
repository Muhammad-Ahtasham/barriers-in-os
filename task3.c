#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //MODIFICATION by adding another standard Library for "sleep(1)" function/

//Function declarations
void *functionA();
void *functionB();

// Initialise a mutex called mutex1
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// Initialise a condition variable called con_var
pthread_cond_t con_var = PTHREAD_COND_INITIALIZER;

// Some global definitions and a variable
#define TOP_LIMIT 21
int counter = 1;

// MAIN

int main() {
pthread_t thread1, thread2, thread3; // declare 3 threads

// Create three threads -no error checking for simplicity
pthread_create(&thread1, NULL, &functionA,NULL) ;
pthread_create(&thread2, NULL, &functionB,NULL) ;

// Remember to use the thread joins
pthread_join( thread1,NULL) ;
pthread_join( thread2,NULL) ;

// Destroy the mutex and the condition variable
pthread_cond_destroy ( &con_var) ;
pthread_mutex_destroy ( &mutex1) ;

printf ("\nNow finished\n") ;

// main exits

exit(0) ;

}