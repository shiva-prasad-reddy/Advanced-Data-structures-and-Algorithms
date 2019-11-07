#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


void hire(int *arr, int N)
{
	int rdn;
	int current = -1;
	for(int i = 0; i < N; i++)
	{
		rdn = rand() % N;
		if(current == -1 || arr[rdn] > arr[current])
		{
			//fire and hire
			current = rdn;
		}
	}
	printf("Candidate %d [ %d ] is hired.\n", current, arr[current]);
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