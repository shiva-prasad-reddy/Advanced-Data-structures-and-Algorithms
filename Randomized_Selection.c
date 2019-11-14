#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int selection(int *arr, int N, int rank)
{

	int output;
	//printf("N %d rank %d\n", N, rank);
	int rdn = rand() % N;
	//printf("rdn -- %d\n", rdn);
	int *arr_less, arr_less_count = 0;
	int *arr_greater, arr_greater_count = 0;

	arr_less = (int *)malloc(N* sizeof(int));
	arr_greater = (int *)malloc(N * sizeof(int));

	for(int i = 0; i < N; i++)
	{
		if(arr[i] < arr[rdn])
		{
			arr_less[arr_less_count++] = arr[i];
		} 
		if(arr[i] > arr[rdn])
		{
			arr_greater[arr_greater_count++] = arr[i];
		}
	}

	if(arr_less_count == rank - 1)
	{
		output = arr[rdn];
	}
	else
	{
		if(arr_less_count >= rank) //important
		{
			output = selection(arr_less, arr_less_count, rank);
		}
		else
		{
			output = selection(arr_greater, arr_greater_count, rank - (arr_less_count+1));
		}
	}

	free(arr_less);
	free(arr_greater);
	return output;
}

int main()
{
	srand(time(0));

	int arr[] = {4, 12, 7, 2, 0};
	int N;
	
	N = sizeof(arr)/sizeof(int);

	int rank = 3;

	printf("The element with rank %d is %d\n",rank, selection(arr, N, rank));

	return 0;
}
