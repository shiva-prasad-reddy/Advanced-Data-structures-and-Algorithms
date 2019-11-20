
//Convert a adjacent list graph representation to linear equations
//Convert linear equations to a matrix form
//Transpose the matrix to transform a minimization problem into a maximization problem
//Now add slack columns and Z and C columns to the matrix
//Use the simplex algorithm to solve the above maximization problem


#include<stdio.h>
#include<stdlib.h>

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
	int vertices;
	printf("\nEnter number of vertices >> ");
	scanf("%d",&vertices);

	int edges = (vertices * (vertices - 1)) / 2; //maximum possible edges

	float **matrix = (float **)malloc( (edges + 1) * sizeof(float *));

	for(int i = 0; i < edges+1; i++)
	{
		matrix[i] = (float *)calloc(vertices, sizeof(float));
	}

	for(int i = 0; i < vertices; i++)
	{
		printf("Enter the weight of vertix %d >> ", i);
		scanf("%f",&matrix[edges][i]);
	}
	printf("\n");

	int temp;
	int k = 0;
	for(int i = 0; i < edges; i++)
	{
		for(int j = i+1; j < vertices; j++)
		{
			matrix[k][i] = matrix[k][j] = 1;
			k++;
		}
	}

	for(int i = 0; i < edges+1; i++)
	{
		for(int j = 0; j < vertices; j++)
		{
			printf("%.2f\t",matrix[i][j]);
		}
		printf("\n");
	}

	struct tableau *node = (struct tableau *)malloc(sizeof(struct tableau));
	node->matrix = matrix;
	node->rows = edges+1;
	node->columns = vertices;

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


int main()
{
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
	
	printf("\n======= Vertex Cover =======\n");
	float total_weight = 0;
	for(int i = 0; i < tab_->columns; i++)
	{
		if(tab->matrix[tab->rows-1][tab_->rows-1+i] >= 0.5)
		{
			printf("Vertex %d is included\n", i);
			total_weight += tab_->matrix[tab_->rows-1][i];
		}
	}
	printf("\nMinimum weight that could be achieved  = [ %f ]\n", total_weight);
	printf("\n");
	
	free(tab_);
	free(tab);
	return 0;
}
