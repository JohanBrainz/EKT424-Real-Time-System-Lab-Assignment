#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <unistd.h>

int main(){

	pid_t o;
	char *mytask[] = {"task1.out", "task2.out", "task3.out"};
	int priority[] = {50,60,40};
	struct sched_param myparams;

	for ( int i = 0; i<3; i++){
	
		if ( (o = fork()) == 0){

		myparams.sched_priority = priority[i];
		sched_setparam(getpid(), &myparams);
		sched_setscheduler(getpid(),SCHED_FIFO,&myparams);
		execl( mytask[i] , mytask[i], (char*) NULL);

		}
	}	
}
