#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread1_function(void *arg);
void *thread2_function(void *arg);

int main(){
	pthread_t tid1, tid2;
	int id = 1;

	int thread1 = pthread_create(&tid1, NULL, thread1_function, &id);
	if(thread1 != 0){
		fprintf(stderr, "Error: unable to create thread 1: %d", thread1);
		return 1;
	}

	int thread2 = pthread_create(&tid2, NULL, thread2_function, &id);
	if(thread2 != 0){
		fprintf(stderr, "Error: unable to create thread 2: %d", thread2);
		return 1;
	}

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}

// thread function
void *thread1_function(void *arg){
	int id = *(int *)arg;
	printf("Hi, i am thread 1.\n");
	pthread_exit(NULL);
}

void *thread2_function(void *arg){
	int id = *(int *)arg;
	printf("Hi, i am thread 2.\n");
	pthread_exit(NULL);
}
