#include <stdio.h> //For error checking mainly.
#include <signal.h> //For signal handling / catching
#include <limits.h> //For UINT_MAX
#include <stdlib.h> //For Calloc
#include <time.h>	//You don't want to know.


void SIGHUP_Handler(int signum);
void SIGUSR1_Handler(int signum);
void SIGUSR2_Handler(int signum);
int * GenPrimes(unsigned int *a);


int main(int argc, char *argv[])
{
	int total_time = time(NULL);

	printf("Attempting to malloc array.\n");

	unsigned int *a = calloc(SHRT_MAX, sizeof *a); //Array for Numbers
	printf("Starting!\n");

	// http://stackoverflow.com/a/31322918
	for(unsigned int j=0,i=2; i < SHRT_MAX && i > 0; i++, j++)
	{
		a[j]=i;	
	}

    printf("Starting Prime Number Gen.\n");
	printf("Time taken: %ld\n", time(NULL) - total_time);

	a = GenPrimes(a);

	printf("Finished in %ld.\n", time(NULL) - total_time);

	for(unsigned int i = 0; i < SHRT_MAX; i++) 
	{
		/* Print all the non Zero *Prime numbers* */
		if(a[i] != 0) 
		{
			printf("%d \n", a[i]);
		}

		signal(SIGHUP, SIGHUP_Handler);
		signal(SIGUSR1, SIGUSR1_Handler);
		signal(SIGUSR2, SIGUSR2_Handler);
	}
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

int *GenPrimes(unsigned int *a)
{
	for(unsigned int i = 0; i < SHRT_MAX; i++)
    {
        int num = a[i];

		//If number is not 0, update later array index.
		if ( num != 0 )
		{
			for (unsigned int j = i+1; j < SHRT_MAX; j++)
			{
				if( ( a[j]%num == 0 ) )
				{
					a[j] = 0;
				}
			}
		}
	}

	return a;
}
