#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>

void usr1_handler(int sig_num){
	printf("Parent (%d) got the SIGUSR1\n",getpid());
}

int main(){
	pid_t ret;
	int status;
	int role = -1;
	ret = fork();

	if(ret > 0){
		printf("Parent: This is the parent process(pid %d)\n",getpid());
		signal(SIGUSR1,usr1_handler);
		role = 0;
		pause();
		printf("Parent:Awaiting child exit\n");
		ret = wait(&status);
	}else if(ret == 0){
		printf("Child : This is the child process(pid %d)\n",getpid());
		role = 1;
		sleep(1);
		printf("Child:Sending SIGUSR1 to pid %d\n",getppid());
		kill(getppid(),SIGUSR1);
		sleep(2);
	}else{
		printf("Parent:Error trying to fork() (%d)\n",errno);
	}
	printf("%s:Exiting...\n",((role == 0) ? "Parnent" : "Child"));
	return 0;
}
