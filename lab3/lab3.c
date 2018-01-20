#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

	pid_t o;
	char *mytask[] = {"task1.out", "task2.out", "task3.out"};

	for ( int i = 0; i<3; i++){
	
		if ( (o = fork()) == 0){
		execl( mytask[i] , mytask[i], (char*) NULL);
		}
	}
	wait(NULL);	
}