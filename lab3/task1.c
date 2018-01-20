#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sched.h>


timer_t timerID;


void exec_timer(void){
	struct itimerspec masa;
	

	masa.it_value.tv_sec = 0;
	masa.it_value.tv_nsec = 1;

	masa.it_interval.tv_sec = 10;
	masa.it_interval.tv_nsec = 0;


	timer_create(CLOCK_MONOTONIC,NULL, &timerID);
	timer_settime(timerID, 0, &masa, NULL);
	}


void starttask(int sig){
	
	 printf("hi, this is task 1!, pid= %d \n", getpid());
	 (void)signal(SIGALRM,starttask);
	
}


int main(){

	(void)signal(SIGALRM,starttask);
	exec_timer();
	while(1);
}


