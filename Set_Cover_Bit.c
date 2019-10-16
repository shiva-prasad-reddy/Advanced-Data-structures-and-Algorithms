
#include "stdio.h"
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define ARRAY_SIZE 2
#define int unsigned int

//IN ANY SET AT INDEX [0] THE NO. OF ELEMENTS PRESENT IN THAT SET ARE STORED
//CONTAINER[0] is an universal set


int addElementToSet(int set, int element)
{
	int add = 1;
	add = add << element;
	return set + add;
}

int **initializeSets(int no_of_sets)
{
	int **container = NULL, *set = NULL;
	container = (int **)calloc(no_of_sets, sizeof(int *));

	int input;
	for(int i = 0; i < no_of_sets; i++)
	{
		printf("No. of elements in set [ %d ] >>> ", i);
		scanf("%d", &input);

		set = (int *)calloc(ARRAY_SIZE, sizeof(int));
		set[0] = input;
		container[i] = set;

		printf("Enter the %d elements of set [ %d ]\n", input, i);
		for(int j = 1; j <= set[0]; j++)
		{
			scanf("%d", &input);
			set[1] = addElementToSet(set[1], input);
		}
		printf("\n");
	}

	/*
	for(int i = 0; i < no_of_sets; i++)
	{
		set = container[i];
		printf("\n Elements in Set [ %d ] >> [ %d ]", i, set[1]);
	}
	printf("\n");
	*/
	return container;
}

int find_set_containing_max_elements(int **container, int no_of_sets)
{
	int max_set_index = 1;
	for(int i = 1; i < no_of_sets; i++)
		if(container[i][0] > container[max_set_index][0])
			max_set_index = i;

	return max_set_index;
}

//	complexity can be reduced by taking the answer_set and 
//	not visiting the answer_set which is already considered
//	if(answer_set[j] == TRUE) continue; //not much complexity reduced --- even ERROR
//	because making it TRUE before removing elements

int countNoOfOneBits(int X)
{
	int count  = 0;
	while(X != 0)
	{
		if( X & 1 ) count++;
		X = X >> 1;
	}
	return count;
}

void remove_elements(int **container, int no_of_sets, int max_set_index)
{
	int max_set = container[max_set_index][1];

	for(int i = 0; i < no_of_sets; i++)
	{
		if( (max_set & container[i][1]) != 0)
		{
			//Bit level removal of elements
			container[i][1] = container[i][1] & (~max_set);
			container[i][0] = countNoOfOneBits(container[i][1]);
		}
	}

}

void set_covering_approximation_algorithm(int **container, int no_of_sets)
{
	int *answer_set = (int *)calloc(no_of_sets, sizeof(int));
	int max_set_index;

	while(container[0][0] != 0)
	{
		max_set_index = find_set_containing_max_elements(container, no_of_sets);
		answer_set[max_set_index] = TRUE;
		remove_elements(container, no_of_sets, max_set_index);
	}

	printf("\nApprox. Answer Set for Set Covering Problem\n");
	for(int i = 1; i < no_of_sets; i++)
		if(answer_set[i] == TRUE) printf("SET [ %d ]\n", i);

	free(answer_set);

}

int main()
{
	int no_of_sets = 0, **container = NULL;
	printf("\nEnter No. of Sets >>> ");
	scanf("%d", &no_of_sets);
	
	container = initializeSets(no_of_sets);

	set_covering_approximation_algorithm(container, no_of_sets);

	for(int i = 0; i < no_of_sets; i++) free(container[i]);
	free(container);
	printf("\n");
	return 0;
}