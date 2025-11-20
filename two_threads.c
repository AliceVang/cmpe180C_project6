#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);

int main(){
	pthread_t tid;
	int id = 1;

	int thread1 = pthread_create(&tid, NULL, thread_function, &id);
	if(thread1 != 0){
		fprintf(stderr, "Error: unable to create thread 1: %d", thread1);
		return 1;
	}

	pthread_join(tid, NULL);
	return 0;
}

// thread function
void *thread_function(void *arg){
	int id = *(int *)arg;
	printf("Hi, i am thread 1.\n");
	pthread_exit(NULL);
}
