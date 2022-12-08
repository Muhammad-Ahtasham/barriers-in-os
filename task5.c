#include <stdio.h>
#include <pthread.h>

int arr[10], sum;
float avg;
pthread_barrier_t barrier;


void *SUM(){
	int Sum = 0;
	for(int i=0; i<10; i++){
		Sum += arr[i];
	}
	sum = Sum;
}

void *AVG(){
	float Avg = 0;
	Avg = sum/10;
	avg = Avg;
}

int main(){
	for(int i=0; i<10; i++){
		printf("Enter an integer: ");
		scanf("%d", &arr[i]);
	}
	pthread_barrier_init(&barrier, NULL, 1);
	pthread_t id_1, id_2;
	
	pthread_create(&id_1, NULL, SUM, NULL);
	pthread_join(id_1, NULL);
	pthread_create(&id_2, NULL, AVG, NULL);
	pthread_join(id_2, NULL);

	printf("AVG of entered NUMBERS ARE : %f\n", avg);
}