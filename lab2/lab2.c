#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>


int main(){

	pid_t o;
	char *mytask[] = {"./task1.out", "./task2.out", "./task3.out", "./task4.out", "./task5.out"};
	int i;

	for ( i = 0; i<5; i++){
	
		if ( (o = fork()) == 0){
			execl( mytask[i] , mytask[i] , (char*) NULL);
		}
	}
	wait(NULL);
}