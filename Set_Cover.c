
#include "stdio.h"
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_SET_MEMBERS 20


//IN ANY SET AT INDEX [0] THE NO. OF ELEMENTS PRESENT IN THAT SET ARE STORED

int **initializeSets(int no_of_sets)
{
	int **container = NULL, *set = NULL;
	container = (int **)calloc(no_of_sets, sizeof(int *));

	int input;
	for(int i = 0; i < no_of_sets; i++)
	{
		printf("No. of elements in set [ %d ] >>> ", i);
		scanf("%d", &input);

		set = (int *)calloc(MAX_SET_MEMBERS, sizeof(int));
		set[0] = input;
		container[i] = set;

		printf("Enter the [ %d ] elements of set [ %d ]\n", input, i);
		for(int j = 1; j <= set[0]; j++)
		{
			scanf("%d", &input);
			set[input] = TRUE;
		}
		printf("\n");

	}


	for(int i = 0; i < no_of_sets; i++)
	{
		set = container[i];
		printf("\n Elements in Set [ %d ]", i);
		for(int j = 1; j < MAX_SET_MEMBERS; j++)
			if(set[j] == TRUE) printf("%d, ", j);

	}

	return container;
}



int find_set_containing_max_elements(int **container, int no_of_sets)
{
	int max_index = 1;
	for(int i = 2; i < no_of_sets; i++)
		if(container[i][0] > container[max_index][0])
			max_index = i;

	return max_index;
}

void remove_elements(int **container, int no_of_sets, int max_set_index, int *answer_set)
{

	//complexity can be reduced by taking the answer_set and not visiting the answer_set 
	//which is already considered

	int *max_set = container[max_set_index];
	for(int i = 1; i < MAX_SET_MEMBERS; i++)
	{
		if(max_set[i] == TRUE)
		{

			for(int j = 0; j < no_of_sets; j++)
			{
				if(container[j][i] == TRUE)
				{
					container[j][i] = FALSE;
					container[j][0] -= 1;
				}
			}

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

	printf("Approx. Answer Set for Set Covering Problem\n");
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

	return 0;
}


/*

int *set_union(int *a, int *b)
{
	int *c = (int *)calloc(MAX_SET_MEMBERS, sizeof(int));
	
	for(int i = 1; i < MAX_SET_MEMBERS; i++)
		if(a[i] == TRUE || b[i] == TRUE)
		{
			 c[i] = TRUE;
			 c[0] += 1;
		}

	return c;
}

int *set_intersection(int *a, int *b)
{
	int *c = (int *)calloc(MAX_SET_MEMBERS, sizeof(int));
	
	for(int i = 1; i < MAX_SET_MEMBERS; i++)
		if(a[i] == TRUE && b[i] == TRUE)
		{
			c[i] = TRUE;
			c[0] += 1;
		}

	return c;
}

int *set_difference(int *a, int *b)
{
	//int count_a = cardinality(a);
	//int count_b = cardinality(b);
	//int *c = (int *)calloc( (count_a + count_b), sizeof(int) );

	int *c = (int *)calloc(MAX_SET_MEMBERS, sizeof(int));
	
	for(int i = 1; i < MAX_SET_MEMBERS; i++)
		if(a[i] == TRUE && b[i] == FALSE)
		{
			c[i] = TRUE;
			c[0] += 1;
		}

	return c;
}

int cardinality(int *a)
{
	int i, count = 0;
	//l = (int)(sizeof(a) / sizeof(int));
	for(i = 0; i < MAX_SET_MEMBERS; i++)
		if(a[i] == TRUE) count++;

	return count;
}


*/