#include <stdio.h>	//For error checking mainly.
#include <unistd.h> //For Sleep, I think
#include <signal.h> //For signal handling / catching
#include <limits.h> //For UINT_MAX
#include <stdlib.h> //For Calloc
#include <time.h>	//Currently used to check time to walk through sections


void SIGHUP_Handler(int signum);
void SIGUSR1_Handler(int signum);
void SIGUSR2_Handler(int signum);
unsigned int * GenPrimes(unsigned int *a);
void PrintPrimes(unsigned int *a);

int PrimeLCV = 0;	//Used to control which prime is printing
int reverse = 0;	//Used to determine if loop is moving forwards or backwards
int skipnext = 0;	//Used to literally skip next prime

int main(int argc, char *argv[])
{
	int total_time = time(NULL);

	printf("Attempting to malloc array.\n");

	unsigned int *a = calloc(SHRT_MAX, sizeof *a); //Array for Numbers
	printf("Starting!\n");

	// http://stackoverflow.com/a/31322918
	for(unsigned int j=0,i=2; i < SHRT_MAX && i > 0; i++, j++)
	{
		a[j]=i;	//Make array of all numbers between 2 and shrt_max (36535)
	}

    printf("Starting Prime Number Gen.\n");
	printf("Time taken: %ld\n", time(NULL) - total_time);

	a = GenPrimes(a);	//Walk through array, setting non-primes to 0
						//And leaving primes as is.
	printf("Finished in %ld.\n", time(NULL) - total_time);

	PrintPrimes(a);

    free(a);
    return 0;
}

void PrintPrimes(unsigned int *a)
{
    // http://stackoverflow.com/a/31322918
	while(PrimeLCV < SHRT_MAX) 
	{
		/* Print all the non Zero *Prime numbers* */
		if(a[PrimeLCV] != 0 && skipnext == 0)	//Only prime numbers are left
		{										//In function A; rest are 0.
			printf("%d \n", a[PrimeLCV]);
			sleep(1);
		}
		else if (a[PrimeLCV] != 0 && skipnext == 1)
		{
			skipnext = 0;
		}

		signal(SIGHUP, SIGHUP_Handler);		//Catch signal 'SIGHUP' (1)
		signal(SIGUSR1, SIGUSR1_Handler);	//Catch signal 'SIGUSR1' (10)
		signal(SIGUSR2, SIGUSR2_Handler);	//Catch signal 'SIGUSR2' (12)
											//And call appropriate function
		if ( reverse )
		{
			if(PrimeLCV == 0)	//Check to make sure not printing below 2.
			{
				break;			//Exit function.
			}
			PrimeLCV--;
		}
		else
		{
			if(PrimeLCV > SHRT_MAX)	//Check to ensure number within range
			{
				break;			//Exit Function
			}
			PrimeLCV++;
		}
	}
}

void SIGHUP_Handler(int signum)
{
	printf("Received Signal %d; SIGHUP\n", signum);
	PrimeLCV = 0-1;	//Global Variables make life easy.
}
void SIGUSR1_Handler(int signum)
{
	printf("Received Signal %d; SIGUSR1\n", signum);
	skipnext = 1;		//Set skip int
}
void SIGUSR2_Handler(int signum)
{
	printf("Received Signal %d; SIGUSR2\n", signum);
	if (reverse == 0)
	{
		reverse = 1;	//Set Reverse to be true
	}
	else
	{
		reverse = 0;	//Set reverse to be false.
	}
}

unsigned int *GenPrimes(unsigned int *a)
{
	//Short walkthough to explain what's happening.
	//Take number at a[0] (2)
	//go through entire array, removing all numbers
	//evenly divisible by a[0] (2); make them 0.
	//after walk through entire array, increment to next
	//a; a[1] (3).
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
