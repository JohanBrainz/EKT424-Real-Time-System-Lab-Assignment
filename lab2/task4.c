#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int main(){

	struct timespec mula, berhenti;	
	int w;

	while(1){
	clock_gettime(CLOCK_MONOTONIC_RAW, &mula);
	printf("hi, this is task 4 using execl, ");
	for(w=0;w<=10000000;w++){}
	clock_gettime(CLOCK_MONOTONIC_RAW, &berhenti);
	double selangmasa = ((berhenti.tv_sec - mula.tv_sec) * 1000) + ((berhenti.tv_nsec - mula.tv_nsec) / 1000000);
	printf( "%.2f Milisecond\n", selangmasa); 
	sleep(4);
	
	}
	
}