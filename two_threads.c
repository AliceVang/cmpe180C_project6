#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void *thread1_function(void *arg);
void *thread2_function(void *arg);
int turn = 0; // thread1 = 0, thread2 = 1

void SIGINT_handler(int sig);
void init_SIGINT();
volatile sig_atomic_t QUIT = 0;

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

void SIGINT_handler(int sig){
	(void)sig;
	QUIT = 1;
}

void init_SIGINT(){
	struct sigaction act = {0};
	act.sa_handler = SIGINT_handler;

	if(sigaction(SIGINT, &act, NULL) == -1){
		fprintf(stderr, "Error: unable to initialize SIGINT signal.\n");
		exit(1);
	}
}

