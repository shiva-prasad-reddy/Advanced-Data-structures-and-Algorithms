
//Convert a adjacent list graph representation to linear equations
//Convert linear equations to a matrix form
//Transpose the matrix to transform a minimization problem into a maximization problem
//Now add slack columns and Z and C columns to the matrix
//Use the simplex algorithm to solve the above maximization problem


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

struct tableau
{
	float **matrix;
	int rows;
	int columns;
};




int find_the_index_of_highest_negative_coefficient(float *list, int columns)
{
	int index = -1;
	for(int i = 0; i < columns; i++)
	{
		if(list[i] < 0)
			if(index == -1 || list[i] < list[index])
				index = i;
	}

	//if no negative entries the optimal solution found
	return index;
}

int find_the_pivot_row(struct tableau *tab, int pivot_column)
{
	//find the smallest non negative entries on the constants column
	int pivot_row = -1;
	float temp;
	for(int i = 0; i < tab->rows; i++)
	{
		temp = tab->matrix[i][tab->columns-1] / tab->matrix[i][pivot_column];
		if(temp > 0)
		{
			if(pivot_row == -1 || temp < (tab->matrix[pivot_row][tab->columns-1] / tab->matrix[pivot_row][pivot_column]))
			{
				pivot_row = i;
			}
		}
	}

	return pivot_row;
}

void apply_transformations(struct tableau *tab, int pivot_row, int pivot_column)
{
	//apply row transformations to make pivot element to 1 and other elements in its column to 0
	float temp = tab->matrix[pivot_row][pivot_column];
	if(temp != 1)
	{
		for(int i = 0; i < tab->columns; i++)
		{
			tab->matrix[pivot_row][i] = tab->matrix[pivot_row][i]/temp;
		}
	}
	
	for(int i = 0; i < tab->rows; i++)
	{
		if(i != pivot_row)
		{
			temp = tab->matrix[i][pivot_column];
			if(temp != 0)
			{
				for(int j = 0; j < tab->columns; j++)
				{
					tab->matrix[i][j] = tab->matrix[i][j] - (temp * tab->matrix[pivot_row][j]);
				}
			}
		}
	}
}

void display(struct tableau *tab)
{
	for(int i = 0; i < tab->rows; i++)
	{
		for(int j = 0; j < tab->columns; j++)
		{
			printf("%.2f\t", tab->matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

struct tableau *createGraphMatrix()
{

	int elements;
	printf("\nEnter total number of elements >> ");
	scanf("%d",&elements);

	int sets;
	printf("\nEnter total number of sets >> ");
	scanf("%d",&sets);

	

	float **matrix = (float **)malloc( (elements + 1) * sizeof(float *));

	for(int i = 0; i < elements+1; i++)
	{
		matrix[i] = (float *)calloc(sets, sizeof(float));
	}

	for(int i = 0; i < sets; i++)
	{
		printf("Enter the weight of set %d >> ", i);
		scanf("%f",&matrix[elements][i]);
	}
	printf("\n");

	int temp;
	for(int i = 0; i < elements; i++)
	{
		
		do {
			printf("Element [ %d ] present in set >> ", i);
			scanf("%d",&temp);
			if(temp == -1) break;
			matrix[i][temp] = 1;
		} while(1);
		printf("\n");
		/*
		for(int j = 0; j < sets; j++)
		{
			printf("\nDo Element [ %d ] present in Set [ %d ] >> ", i, j);
			scanf("%d",&temp);
			if(temp == 1)
			{
				matrix[i][j] = 1;
			}
		}
		*/
	}

	for(int i = 0; i < elements+1; i++)
	{
		for(int j = 0; j < sets; j++)
		{
			printf("%.2f\t",matrix[i][j]);
		}
		printf("\n");
	}

	struct tableau *node = (struct tableau *)malloc(sizeof(struct tableau));
	node->matrix = matrix;
	node->rows = elements + 1;
	node->columns = sets;

	return node;
}

struct tableau *transpose_and_addSlackVariables(struct tableau *tab)
{
	int rows = tab->columns + 1;
	int columns = tab->rows + tab->columns + 1; //slack variables
	float **matrix = (float **)malloc( rows * sizeof(float *));

	for(int i = 0; i < rows; i++)
	{
		matrix[i] = (float *)calloc(columns, sizeof(float));
	}

	for(int i = 0; i < tab->columns; i++)
	{
		for(int j = 0; j < tab->rows; j++)
		{
			if(j == tab->rows-1)
				matrix[i][columns-1] = tab->matrix[j][i];
			else
				matrix[i][j] = tab->matrix[j][i];
		}
	}

	for(int i=0; i < tab->rows-1; i++)
		matrix[tab->columns][i] = -1;

	for(int i = 0; i < rows; i++)
	{
		for(int j = tab->rows-1; j < columns-1; j++)
		{
			if(i == (j - tab->rows+1))
				matrix[i][j] = 1;
		}
	}

	struct tableau *newTab = (struct tableau *)malloc(sizeof(struct tableau));
	newTab->matrix = matrix;
	newTab->rows = rows;
	newTab->columns = columns;
	return newTab;
}


void freeMemory(struct tableau *tab, int rows)
{
	for(int i = 0; i < rows; i++)
	{
		free(tab->matrix[i]);
	}

	free(tab->matrix);
	free(tab);
}


void randomizedRounding_1(struct tableau *tab_, struct tableau *tab)
{
	int t = floor(2 * (log(tab_->rows-1) / log(2.7182818285)));

	float threshold;
	int *sets = calloc(tab_->columns, sizeof(int));

	for(int i = 0; i < t; i++)
	{
		threshold = (rand() % 10) * 0.1;
		printf("SEE --- %f -- \n", threshold);
		for(int i = 0; i < tab_->columns; i++)
		{
			if(tab->matrix[tab->rows-1][tab_->rows-1+i] >= threshold)
				sets[i] = 1;
		}
	}

	printf("\n======= Set Cover After Randomized Rounding 1 =======\n");
	for(int i = 0; i < tab_->columns; i++)
	{
		if(sets[i] == 1)
			printf("set %d is included\n", i);
	}
	printf("\n");



	free(sets);

}


int main()
{
	srand(time(0));
	struct tableau *tab_ = NULL;
	tab_ = createGraphMatrix();

	struct tableau *tab = NULL;
	tab = transpose_and_addSlackVariables(tab_);

	printf("===========================\n");
	display(tab);
	int pivot_row, pivot_column, count = 0;
	pivot_column = find_the_index_of_highest_negative_coefficient(tab->matrix[tab->rows-1], tab->columns);	
	while(pivot_column != -1)
	{
		pivot_row = find_the_pivot_row(tab, pivot_column);
		apply_transformations(tab, pivot_row, pivot_column);
		printf("=============== Iteration :: %d ==================\n", ++count);
		display(tab);
		pivot_column = find_the_index_of_highest_negative_coefficient(tab->matrix[tab->rows-1], tab->columns);
	}
	
	printf("\n======= Set Cover =======\n");
	for(int i = 0; i < tab_->columns; i++)
	{
		if(tab->matrix[tab->rows-1][tab_->rows-1+i] == 1)
			printf("set %d is included\n", i);
	}
	printf("\n");
	
	//still left to be done.
	randomizedRounding_1(tab_, tab);


	free(tab_);
	free(tab);
	return 0;
}
