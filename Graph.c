#include<stdio.h>
#include<stdlib.h>
#define SIZE 20

struct node 
{
	int vertex;
	struct node *link;
};

struct node *(graph[SIZE]) = {};
int visited[SIZE] = {};


void createGraph()
{
	int vertices;
	printf("\nNumber of vertices :: ");
	scanf("%d",&vertices);

	//adjList = (struct node *)malloc((vertices+1)*sizeof(struct node *));


	struct node *temp, *last;
	int i,j,option;
	for(i=1; i<=vertices; i++)
	{
		temp = last = NULL;
		for(j=1; j<=vertices; j++)
		{
			if(i == j)
				continue;
			printf("\nDoes node %d has an edge to %d :: ", i, j);
			scanf("%d",&option);
			if(option)
			{
				temp = (struct node *)malloc(sizeof(struct node));
				temp->vertex = j;
				temp->link = NULL;

				if(last == NULL)
				{
					graph[i] = temp;
					last = temp;
				}
				else
				{
					last->link = temp;
					last = temp;
				}

			}
		}
	}

}


void DFS(int vertex)
{
	visited[vertex] = 1;
	printf("%d, ", vertex);
	struct node *temp;
	temp = graph[vertex];
	while(temp)
	{
		if(visited[temp->vertex] == 0)
		{
			DFS(temp->vertex);
		}
		temp = temp->link;
	}
}

void BFS(int vertex)
{
	int queue[SIZE];
	int front, rear;
	front = rear = -1;
	int visited[SIZE] = {};
	struct node *temp = NULL;

	visited[vertex] = 1;
	queue[++rear] = vertex;


	while(front != rear)
	{
		vertex = queue[++front];
		printf("%d, ", vertex);
		temp = graph[vertex];

		while(temp)
		{
			if(visited[temp->vertex] == 0)
			{
				visited[temp->vertex] = 1;
				queue[++rear] = temp->vertex;
			}
			temp = temp->link;
		}

	}

}


int main()
{

	createGraph();
	printf("\nDepth First Search\n");
	DFS(1);

	printf("\nBreadth First Search\n");
	BFS(1);

	printf("\n\n");

	return 0;
	
}