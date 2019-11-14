#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


//Rank of a number(k)  = 1 + |{x E A : x < k}|

//MONTE CARLO RANDOMIZATION APPROXIMATION
//random choices influences correctness but not running time
//T(N) = O(N)
//P(S) = 2*delta
void rand_approx_median1(int *arr, int N, int delta)
{
	int rdn = rand() % N;
	//printf("%d\n", rdn);
	int k = 0;
	for(int i = 0; i < N; i++)
		if(arr[i] < arr[rdn])
			k++;

	if( (0.5 - delta)*(N+1) <= k && k <= (0.5 + delta)*(N+1) )
		printf("Median = %d\n", arr[k]);
	else
		printf("Failure\n");
}

//IT is a Mixturex
//MONTE CARLO RANDOMIZATION APPROXIMATION
//random choices influences both running time and correctness
//T(N) = O(C * N)
//P(F) = (1 - 2 * delta) ^ C
void rand_approx_median2(int *arr, int N, int delta, int C)
{
	int c = 0, k, rdn;
	do
	{
		c++;
		rdn = rand() % N;
		k = 0;
		for(int i = 0; i < N; i++)
			if(arr[i] < arr[rdn])
				k++;

		if( (0.5 - delta)*(N+1) <= k && k <= (0.5 + delta)*(N+1) )
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
//random choices influence the running time
//T(N) = O(N / delta)
void rand_approx_median3(int *arr, int N, int delta)
{
	int k, rdn;
	do
	{
		rdn = rand() % N;
		k = 0;
		for(int i = 0; i < N; i++)
			if(arr[i] < arr[rdn])
				k++;

		if( (0.5 - delta)*(N+1) <= k && k <= (0.5 + delta)*(N+1) )
			break;
			
	} while(1);

	printf("Median = %d\n", arr[k]);
}

int main()
{
	srand(time(0));

	int arr[] = {1,2,3,4,5};
	int N, delta;
	
	N = sizeof(arr)/sizeof(int);
	delta = 0.5;

	rand_approx_median1(arr, N, delta); 

	return 0;
}