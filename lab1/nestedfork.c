#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

	pid_t x;
	int status = 0;


	x = fork();

	if(x == 0){
	
		x = fork();
		if(x == 0){

			x = fork();
			if (x == 0){
				printf("child 3 pid=%d, parent id:%d\n", getpid(), getppid());
			}				
			else if( x>0){
				printf("child 2 pid=%d, parent id:%d\n", getpid(), getppid());
				wait(NULL);
			}
		}
	
		else if(x >0){
			x = fork();
			if (x == 0){
				printf("parent 3 pid=%d, parent id:%d\n", getpid(), getppid());
			}				
			else if( x>0){
				printf("parent 2 pid=%d, parent id:%d\n", getpid(), getppid());
				wait(NULL);
			}
			wait(NULL);		
		}
		
	}

	else if(x > 0){
		printf("parent 1, pid=%d, parent id:%d\n", getpid(), getppid());
		wait(NULL);	
	}
}