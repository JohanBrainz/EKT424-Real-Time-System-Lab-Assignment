#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>


struct temp_press{

	double value_temp;
	double value_press;
	double LOWER_TEMP_BOUND,UPPER_TEMP_BOUND,LOWER_PRESSURE_BOUND,UPPER_PRESSURE_BOUND;
};

void timespec_add_us(struct timespec *t, long us){

	t->tv_nsec += us*1000;
		while (t->tv_nsec > 1000000000) 
		{
			t->tv_nsec = t->tv_nsec - 1000000000;// + ms*1000000;
			t->tv_sec += 1;
		}
}

void *tempfunc ( void* args){
	
	struct temp_press *arguments = (struct temp_press *)args;
	struct timespec next;
	struct timespec now;
	int j;


	clock_gettime(CLOCK_REALTIME, &next);
	while (1) {
		timespec_add_us(&next, 4000000);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
		arguments -> value_temp = arguments -> LOWER_TEMP_BOUND +(int)(arguments -> UPPER_TEMP_BOUND*rand()/(RAND_MAX+1.0));
		printf("Thread 1:Temperature\n");	
	}
	return NULL;
}


void *presfunc (void* args){

	struct temp_press *arguments = (struct temp_press *)args;
	
	struct timespec next;
	struct timespec now;
	int j;

	clock_gettime(CLOCK_REALTIME, &next);
	while (1) {
		timespec_add_us(&next, 3500000);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
		arguments -> value_press = arguments -> LOWER_PRESSURE_BOUND + (int)(arguments -> UPPER_PRESSURE_BOUND*rand()/(RAND_MAX+1.0));
		printf("Thread 2:Pressure\n");
	}
	return NULL;	
}


void *show (void* args){

	struct temp_press *arguments = (struct temp_press *)args;
	struct timespec next;
	struct timespec now;
	int j;

	clock_gettime(CLOCK_REALTIME, &next);
	while (1) {
		timespec_add_us(&next, 4000000);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
		printf("Thread 3 : Showing Value\n");
		printf("The value of temperature is: %.1lf\n", arguments -> value_temp);
		printf("The value of pressure is: %.1lf\n\n", arguments -> value_press);
	}
	return NULL;
}


int main(){

	pthread_t threadid1,threadid2,threadid3;
	pthread_attr_t myAttr;
	struct sched_param param1, param2, param3;
	struct temp_press value;
	
	int i = 0;
	value.LOWER_TEMP_BOUND = 20;
	value.UPPER_TEMP_BOUND = 90;
	value.LOWER_PRESSURE_BOUND = 20;
	value.UPPER_PRESSURE_BOUND = 90;
	
	printf("The process id: %d\n\n", getpid());
	
	param1.sched_priority = 80;
	pthread_attr_init(&myAttr);
	pthread_attr_setschedpolicy(&myAttr, SCHED_FIFO);
	pthread_attr_setinheritsched(&myAttr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedparam(&myAttr, &param1);
	pthread_create(&threadid1, &myAttr, tempfunc, &value);
	
	param2.sched_priority = 70;
	pthread_attr_init(&myAttr);
	pthread_attr_setschedpolicy(&myAttr, SCHED_FIFO);
	pthread_attr_setinheritsched(&myAttr, PTHREAD_EXPLICIT_SCHED);			
	pthread_attr_setschedparam(&myAttr, &param2);
	pthread_create(&threadid2, &myAttr, presfunc, &value);
	
	param3.sched_priority = 60;
	pthread_attr_init(&myAttr);
	pthread_attr_setschedpolicy(&myAttr, SCHED_FIFO);
	pthread_attr_setinheritsched(&myAttr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedparam(&myAttr, &param3);
	pthread_create(&threadid3, &myAttr, show, &value);

	pthread_attr_destroy(&myAttr);
	
	pthread_join( threadid1, NULL);			
	pthread_join( threadid2,NULL);			
	pthread_join( threadid3,NULL);
}