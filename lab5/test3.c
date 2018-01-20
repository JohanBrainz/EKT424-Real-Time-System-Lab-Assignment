#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>



struct temp_press{

	double value_temp;
	double value_press;
};


void timespec_add_us(struct timespec *t, long us){
	
	
	t->tv_nsec += us*1000;
		while (t->tv_nsec > 1000000000) 
		{
			t->tv_nsec = t -> tv_nsec - 1000000000;// + ms*1000000;
			t->tv_sec += 1;
		}
}


void *calcTemp ( void* args){
	
	struct temp_press *arguments = (struct temp_press *)args;
	double LOWER_TEMP_BOUND = 10;
	double UPPER_TEMP_BOUND = 100;
	struct timespec next, now;
	
	clock_gettime(CLOCK_REALTIME, &next);
	while (1) {
		timespec_add_us(&next, 3500000);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL); //clocknsleep =set waktu and tunggu waktu smpai baru dia keluar dr sleep
										//clock_nanosleep(clock type, flag, struc timespec request(waktu yg kita request dia keluar dr sleep), null) 
		arguments -> value_temp = LOWER_TEMP_BOUND +(int)(UPPER_TEMP_BOUND*rand()/(RAND_MAX+1.0)); calculation for temp, send to value temp
	}
	return NULL;
}


void *calcPres (void* args){

	struct temp_press *arguments = (struct temp_press *)args;
	double LOWER_PRESSURE_BOUND = 10;
	double UPPER_PRESSURE_BOUND = 100;
	struct timespec next, now;
	int j;

	clock_gettime(CLOCK_REALTIME, &next);
	while (1) {
		timespec_add_us(&next, 4000000);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
		arguments -> value_press = LOWER_PRESSURE_BOUND + (int)(UPPER_PRESSURE_BOUND*rand()/(RAND_MAX+1.0));
	}
	return NULL;	
}


void *showVal (void* args){

	struct temp_press *arguments = (struct temp_press *)args;
	struct timespec next, now;
	int j;

	clock_gettime(CLOCK_REALTIME, &next);
	while (1) {
		timespec_add_us(&next, 4000000);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
		printf("Value of temperature: %.1lf\t", arguments -> value_temp);
		printf("Value of pressure: %.1lf\n", arguments -> value_press);
	}
	return NULL;
}


int main(){

	pthread_t threadid1,threadid2,threadid3; // thread id
	
	pthread_attr_t myAttr;// create attribute id
	struct sched_param param1, param2, param3; // to set priority
	struct temp_press value;// save the location of temp_pree in value
	pthread_attr_init(&myAttr); // initialize attribute
		
	
	pthread_attr_setinheritsched(&myAttr, PTHREAD_EXPLICIT_SCHED); // to specify our attribute that we have set before to be used by the thread
	pthread_attr_setschedpolicy(&myAttr, SCHED_FIFO);//  fifo like rm
	param1.sched_priority = 90;// set prority
	pthread_attr_setschedparam(&myAttr, &param1); //initialize the priority given in myattr
	pthread_create(&threadid1, &myAttr, calcTemp, &value);// create thread with attr of myattr, &value contains location of struc
	
	pthread_attr_setinheritsched(&myAttr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&myAttr, SCHED_FIFO);
	param2.sched_priority = 80;
	pthread_attr_setschedparam(&myAttr, &param2);
	pthread_create(&threadid2, &myAttr, calcPres, &value);
	
	pthread_attr_setinheritsched(&myAttr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&myAttr, SCHED_FIFO);
	param3.sched_priority = 70;
	pthread_attr_setschedparam(&myAttr, &param3);
	pthread_create(&threadid3, &myAttr, showVal, &value);
	
	pthread_attr_destroy(&myAttr);

	pthread_join( threadid1,NULL); 
	pthread_join( threadid2,NULL);
	pthread_join( threadid3,NULL);
	
}