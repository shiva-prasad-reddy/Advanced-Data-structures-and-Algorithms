#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void perform_random_permutation(int *arr, int N)
{
	int rdn, temp;
	for(int i = 0; i < N; i++)
	{
		//to generate random number between i and N
		rdn = (rand() % (N - i)) + i;

		//swapping a[rdn] and a[i]
		temp = arr[i];
		arr[i] = arr[rdn];
		arr[rdn] = temp;
	}
}

void hire(int *arr, int N)
{

	//to change the order of candidates supplied by the employment agency
	perform_random_permutation(arr, N);
	//arr represents the quality of a candidate in a scale of 1 to N
	//Lets assume cost paid for hiring a candidate is 1
	int rdn;
	int current = -1;
	int total_cost = 0;
	for(int i = 0; i < N; i++)
	{
		rdn = rand() % N;
		if(current == -1 || arr[rdn] > arr[current])
		{
			//fire and hire
			current = rdn;
			total_cost++;
		}
	}
	printf("Candidate %d is hired\n", current);
	printf("Total Cost = %d and Expected Cost = %f and Worst Case Cost = %d\n", total_cost, (1 * log(N)), (1 * N));
}

int main()
{
	srand(time(0));

	int arr[] = {1,2,3,4,5};
	int N;
	
	N = sizeof(arr)/sizeof(int);

	hire(arr, N); 

	return 0;
}