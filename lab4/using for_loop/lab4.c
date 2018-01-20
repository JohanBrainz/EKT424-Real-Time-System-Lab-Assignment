#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <unistd.h>

int main(){

	pid_t o;
	char *mytask[] = {"task1.out", "task2.out", "task3.out"};
	int priority[] = {50,60,40};
	struct sched_param johan_param;

	for ( int i = 0; i<3; i++){
	
		o = fork();

		if ( o == 0){

		johan_param.sched_priority = priority[i];
		sched_setparam(getpid(), &johan_param);
		sched_setscheduler(getpid(),SCHED_FIFO,&johan_param);
		
		execl(mytask[i],mytask[i],NULL);
		}

		else if ( o > 0){
				
		}
		else{
		printf("error");
		}
		
		
		
	}
	
}