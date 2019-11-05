#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

//MONTE CARLO RANDOMIZATION APPROXIMATION
//Running Time Guaranteed
//Correctness Not Guaranteed
void rand_approx_median1(int *arr, int len, int delta, int median)
{
	int rdn = rand() % len;
	
	int k = 0;
	for(int i = 0; i < len; i++)
		if(arr[i] < arr[rdn])
			k++;

	if( (1 - delta)*median <= k && k <= (1 + delta)*median )
		printf("Median = %d\n", arr[k]);
	else
		printf("Failure\n");
}

//MONTE CARLO RANDOMIZATION APPROXIMATION
//Running Time Guaranteed
//Correctness Not Guaranteed
void rand_approx_median2(int *arr, int len, int delta, int median, int C)
{
	int c = 0, k, rdn;
	do
	{
		c++;
		rdn = rand() % len;
		k = 0;
		for(int i = 0; i < len; i++)
			if(arr[i] < arr[rdn])
				k++;

		if( (1 - delta)*median <= k && k <= (1 + delta)*median )
			break;
		else
			k = -1;
			
	} while(c < C);

	if(k != -1)
		printf("Median = %d\n", arr[k]);
	else
		printf("Failure\n");
}


//LAS VEGAS RANDOMIZATION APPROXIMATION
//Correctness Guaranteed
//Running Time Not Guaranteed
void rand_approx_median3(int *arr, int len, int delta, int median)
{
	int k, rdn;
	do
	{
		rdn = rand() % len;
		k = 0;
		for(int i = 0; i < len; i++)
			if(arr[i] < arr[rdn])
				k++;

		if( (1 - delta)*median <= k && k <= (1 + delta)*median )
			break;
			
	} while(1);

	printf("Median = %d\n", arr[k]);
}

int main()
{
	srand(time(0));

	int arr[] = {1,2,3,4,5};
	int len, median, delta;
	
	len = sizeof(arr)/sizeof(int);
	median = (int)floor((float)len/2);
	
	delta = 0.5;

	rand_approx_median2(arr, len, delta, median, 3); 

	return 0;
}