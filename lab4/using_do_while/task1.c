#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include <signal.h>

timer_t timerID;
struct timespec start, stop;
int selangmasa;

void exec_timer(void){
	struct itimerspec masa;
	masa.it_value.tv_sec = 3;
	masa.it_value.tv_nsec = 0;

	masa.it_interval.tv_sec = 3;
	masa.it_interval.tv_nsec = 0;

	timer_create(CLOCK_MONOTONIC,NULL, &timerID);
	timer_settime(timerID, 0, &masa, NULL);
	}


void starttask(int sig){
	clock_gettime(CLOCK_MONOTONIC, &start);
	printf("task 1 \n");
	
	do{
		
		clock_gettime(CLOCK_MONOTONIC, &stop);
		selangmasa = ((stop.tv_sec - start.tv_sec) * 1000) + ((stop.tv_nsec - start.tv_nsec) / 1000000);	
	}
	while (selangmasa <= 1000);

	printf("%d ms\n", selangmasa);
	signal(SIGALRM,starttask);	
}

int main(){
	
	signal(SIGALRM,starttask);
	exec_timer();
	while(1);
}


