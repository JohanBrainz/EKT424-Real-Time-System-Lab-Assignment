#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include <signal.h>


timer_t timerID;
struct timespec start, end;
int w;

void exec_timer(void){
	
	struct itimerspec masa;
	masa.it_value.tv_sec = 5;
	masa.it_value.tv_nsec = 0;

	masa.it_interval.tv_sec = 5;
	masa.it_interval.tv_nsec = 0;

	timer_create(CLOCK_MONOTONIC,NULL, &timerID);
	timer_settime(timerID, 0, &masa, NULL);
	}


void starttask(int sig){
	
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(w=0;w<=287000000;w++){}
	clock_gettime(CLOCK_MONOTONIC, &end);
	double selangmasa = ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_nsec - start.tv_nsec) / 1000000);
	printf( "1 %2f\n", selangmasa);
	signal(SIGALRM,starttask);	
}

int main(){
	
	signal(SIGALRM,starttask);
	exec_timer();
	while(1);
}


