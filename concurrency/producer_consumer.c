#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define true 1
#define false 0

#define PRODUCER_WANT_INDEX 0
#define CONSUMER_WANT_INDEX 1

typedef int bool;
int remain = 0;
bool flag[2];
int turn;

void visit(int num){
	if (num == 0){
		printf("Producer is visiting\n");
		remain ++;
	}else{
		printf("Consumer is visiting\n");
		remain --;
	}
	printf("the sum of remain commoditis is %d\n",remain);
	sleep(1);
}

void Producer(){
	while(true){
		flag[PRODUCER_WANT_INDEX] = true;
		while(flag[CONSUMER_WANT_INDEX]){
			if (turn == CONSUMER_WANT_INDEX){
				flag[PRODUCER_WANT_INDEX] = false;
				while(turn == CONSUMER_WANT_INDEX);
				flag[PRODUCER_WANT_INDEX] = true;
			}
		}
		printf("Producer want to get critical region\n");
		turn = CONSUMER_WANT_INDEX;//give the puissance to consumer anyway
		if (remain < 10)
		{
			visit(0);
		}else{
			printf("critical region is full\n");
			sleep(1);
		}
		flag[PRODUCER_WANT_INDEX] = false;
	}
}

void Consumer(){
	while(true){
		flag[CONSUMER_WANT_INDEX] = true;
		while(flag[PRODUCER_WANT_INDEX]){
			if (turn == PRODUCER_WANT_INDEX){
				flag[CONSUMER_WANT_INDEX] = false;
				while(turn == PRODUCER_WANT_INDEX);
				flag[CONSUMER_WANT_INDEX] = true;
			}
		}
		printf("consumer want to visit critical region\n");
		turn = PRODUCER_WANT_INDEX;
		if (remain > 0){
			visit(CONSUMER_WANT_INDEX);
		}else{
			printf("Critical region is empty\n");
			sleep(1);
		}
		flag[CONSUMER_WANT_INDEX] = false;
	}
}

void main(){
	pthread_t consumer,producer;
	flag[PRODUCER_WANT_INDEX] = false;
	flag[CONSUMER_WANT_INDEX] = false;
	turn = CONSUMER_WANT_INDEX;
	int err;
	err = pthread_create(&consumer,NULL,(void *)Producer,NULL);
	if (err != 0)
		exit(-1);
	if (err != 0)
		exit(-1);
	err = pthread_create(&producer,NULL,(void *)Consumer,NULL);
	if (err != 0)
		exit(-1);
	if (err != 0)
		exit(-1);
	pthread_join(consumer,NULL);
	pthread_join(producer,NULL);
	exit(0);
}

