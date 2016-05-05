#include <stdio.h> //For error checking mainly.
#include <signal.h> //For signal handling / catching
#include <limits.h> //For UINT_MAX
#include <stdlib.h> //For Calloc
#include <time.h>	//You don't want to know.


#define SIGHUP 1
#define SIGUSR1 10
#define SIGUSR2 12

void SIGHUP_Handler(int signum);
void SIGUSR1_Handler(int signum);
void SIGUSR2_Handler(int signum);

int main(int argc, char *argv[])
{
	unsigned int i = 0, j = 0;		//Loop Control Variables

	int total_time = time.time();

	printf("Attempting to malloc array.\n");

	unsigned int *a = calloc(UINT_MAX, sizeof *a); //Array for Numbers
	printf("Starting!\n");
	for(j=0,i=2; i < UINT_MAX && i > 0; i++, j++)
	{
		a[j]=i;	
		if(i%10000 == 0)
		{
			printf("%u\n", i);
		}
	}
	printf("Finished.");



	signal(SIGHUP, SIGHUP_Handler);
	signal(SIGUSR1, SIGUSR1_Handler);
	signal(SIGUSR2, SIGUSR2_Handler);
	
	free(a);
	return 0;
}
	
void SIGHUP_Handler(int signum)
{
	printf("%d\n", signum);
}
void SIGUSR1_Handler(int signum)
{
	printf("%d\n", signum);
}
void SIGUSR2_Handler(int signum)
{
    printf("%d\n", signum);
}
