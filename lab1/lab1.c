#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>


int main(){

 	struct timeval start, end;
	pid_t o;
	int i;

	for ( i = 0; i<5; i++){
	
		if ( (o = fork()) == 0){
			while(1){
			
			gettimeofday(&start, NULL);
			for(int w=0;w<=18500000;w++){}//delay +-1 second 18500000
			printf("hi this is child no %d with pid of %d, and parent id of %d ,",i, getpid(),getppid());
			gettimeofday(&end, NULL);
			double selangmasa = (((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));
			printf("%.1lf Micro Second\n", selangmasa);
			sleep(4);
			}
		}
	}
	wait(NULL);
}