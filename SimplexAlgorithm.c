#include<stdio.h>

#define HSIZE 12
#define VSIZE 5
//Solving a maximization problem

int find_the_index_of_highest_negative_coefficient(float *list)
{
	int index = -1;
	for(int i = 0; i < HSIZE; i++)
	{
		if(list[i] < 0)
			if(index == -1 || list[i] < list[index])
				index = i;
	}

	//if no negative entries the optimal solution found
	return index;
}

int find_the_pivot_row(float tableau[][HSIZE], int pivot_column)
{
	//find the smallest non negative entries on the constants column
	int pivot_row = -1;
	float temp;
	for(int i = 0; i < VSIZE; i++)
	{
		temp = tableau[i][HSIZE-1] / tableau[i][pivot_column];
		if(temp > 0)
		{
			if(pivot_row == -1 || temp < (tableau[pivot_row][HSIZE-1] / tableau[pivot_row][pivot_column]))
			{
				pivot_row = i;
			}
		}
	}

	return pivot_row;
}

void apply_transformations(float tableau[][HSIZE], int pivot_row, int pivot_column)
{
	//apply row transformations to make pivot element to 1 and other elements in its column to 0
	float temp = tableau[pivot_row][pivot_column];
	if(temp != 1)
	{
		for(int i = 0; i < HSIZE; i++)
		{
			tableau[pivot_row][i] = tableau[pivot_row][i]/temp;
		}
	}
	
	for(int i = 0; i < VSIZE; i++)
	{
		if(i != pivot_row)
		{
			temp = tableau[i][pivot_column];
			if(temp != 0)
			{
				for(int j = 0; j < HSIZE; j++)
				{
					tableau[i][j] = tableau[i][j] - (temp * tableau[pivot_row][j]);
				}
			}
		}
	}


}


void display(float tableau[][HSIZE])
{
	for(int i = 0; i < VSIZE; i++)
	{
		for(int j = 0; j < HSIZE; j++)
		{
			printf("%.2f\t", tableau[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
	//fully connected graph
	//constraints = no of edges

	//int NON_BASIC_VARIABLES = 4
	//int CONSTRAINTS = (NON_BASIC_VARIABLES * (NON_BASIC_VARIABLES - 1))/2;
	//int SLACK_VARIABLES = CONSTRAINTS;

	
	//CONVERT THE MINIMIZATION PROBLEM INTO MAXIMIZATION PROBLEM
	//BY TRANSPOSING THE MATRIX






	float tableau[][HSIZE] = {
		{1,1,1,0,0,0,1,0,0,0,0,20},
		{1,0,0,1,1,0,0,1,0,0,0,5},
		{0,1,0,1,0,1,0,0,1,0,0,11},
		{0,0,1,0,1,1,0,0,0,1,0,2},
		{-1,-1,-1,-1,-1,-1,0,0,0,0,1,0}
	};

					/*{{2,1,1,0,0,3},
						 {1,2,0,1,0,9},
						{-8,-8,0,0,1,0}};

						/*
						{{1,3,2,1,0,0,10},
						 {1,5,1,0,1,0,8},
						{-8,-10,-7,0,0,1,0}};
							
						*/
	



	/*
	printf("SEE\n");
	pivot_column = find_the_index_of_highest_negative_coefficinet(tableau[VSIZE-1]);
	pivot_row = find_the_pivot_row(tableau, pivot_column);
	apply_transformations(tableau, pivot_row, pivot_column);
	display(tableau);
	*/
	display(tableau);
	int pivot_row, pivot_column, count = 0;
	pivot_column = find_the_index_of_highest_negative_coefficient(tableau[VSIZE-1]);	
	while(pivot_column != -1)
	{
		pivot_row = find_the_pivot_row(tableau, pivot_column);
		apply_transformations(tableau, pivot_row, pivot_column);
		printf("=============== Iteration :: %d ==================\n", ++count);
		display(tableau);
		pivot_column = find_the_index_of_highest_negative_coefficient(tableau[VSIZE-1]);
	}
	
	
	
}