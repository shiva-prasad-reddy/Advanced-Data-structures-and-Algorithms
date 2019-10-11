#include<stdio.h>
#define NO_OF_ELEMENTS 5


//Exponential Time Solution for Subset Sum Problem

void fun(int *A, int size_A, int *U, int size_U, int *sol, int T)
{	
	if(size_U != 0)
	{
		int _A[NO_OF_ELEMENTS];

		for(int i = 0; i < NO_OF_ELEMENTS; i++)
			_A[i] = A[i];
		
		size_U--;

		_A[size_A] = U[size_U];
		
		fun(_A, size_A + 1, U, size_U, sol, T);
		fun(A, size_A, U, size_U, sol, T);

	}
	else
	{
		int sum = 0;
		for(int i = 0; i < size_A; i++) sum += A[i];

		if(sum == T)
		{
			if(sol[NO_OF_ELEMENTS] == -1 || sol[NO_OF_ELEMENTS] > size_A)
			{
				sol[NO_OF_ELEMENTS] = size_A;
				for(int i = 0; i < size_A; i++) sol[i] = A[i];
			}
		}
	}
}


int main()
{
	int A[NO_OF_ELEMENTS] = {};
	int U[] = {1, 4, 5, 8, 11};
	int sol[NO_OF_ELEMENTS+1];

	int T = 20;

	for(int i = 0; i < NO_OF_ELEMENTS+1; i++) sol[i] = -1;

	fun(A, 0, U, NO_OF_ELEMENTS, sol, T);
	
	printf("Size of subset which produces sum [ %d ] is [ %d ] and the elements are...\n", T, sol[NO_OF_ELEMENTS]);
	for(int i = 0; i < sol[NO_OF_ELEMENTS]; i++) printf("[ %d ]\n", sol[i]);

	return 0;
}