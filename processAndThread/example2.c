#include<sys/types.h>
#include<unistd.h>
#include<errno.h>

int main(){
	pid_t ret;
	int status,i;
	int role = -1;
	ret = fork();
	if (ret > 0){
		printf("Parent:This is the parent process(pid %d)\n",getpid);
		for (i = 0;i < 6;++ i){
			printf("Parent:At count %d\n",i);
			sleep(1);
		}
		ret = wait(&status);
		role = 0;
	}else if (ret == 0){
		printf("Child:This is the child process(pid %d)\n",getpid());
		for(i = 0;i < 6;++ i){
			printf("Child: At count %d\n",i);
			sleep(1);
		}
		role = 1;
	}else{
		printf("Parent:Error trying to fork() (%d)\n",errno);
	}
	printf("%s:Exiting...\n",((role == 0) ? "Parent" : "Child"));
	return 0;
}
