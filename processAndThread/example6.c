#include<pthread.h>
#include<stdio.h>

void *myThread(void *arg){
	printf("Thread %d started\n",*((int *)arg));
	pthread_exit(arg);
}

#define MAX_THREADS 5

int main(){
	int ret,l,k,i;
	void *status;
	pthread_t threadlds[MAX_THREADS];
	int a[MAX_THREADS] = {0,1,2,3,4};
	for (i = 0;i < MAX_THREADS;++ i){
		ret = pthread_create(&threadlds[i],NULL,myThread,(void*)&a[i]);
		if (ret != 0){
			printf("Error creating thread %d\n",i);
		}
	}
	for (k = 0;k < MAX_THREADS;++ k){
		ret = pthread_join(threadlds[k],&status);
		if (ret != 0){
			printf("Error joining thread %d\n",k);
		}else{
			printf("Status = %d\n",*((int *)status));
		}
	}
	return 0;
}
