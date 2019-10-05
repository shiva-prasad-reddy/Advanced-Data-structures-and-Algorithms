#include<stdio.h>
#include<stdlib.h>

#define VERTICES 20

#define FALSE 0
#define TRUE 1

struct node 
{
	int vertex;
	struct node *link;
};




struct node **createGraph(int vertices)
{
	
	struct node **graph = (struct node **)calloc(vertices, sizeof(struct node *));

	struct node *temp, *last;
	int i,j,option;
	printf("[ YES -> 1 ]  OR  [ NO -> 0 ]\n");
	for(i = 0; i < vertices; i++)
	{
		temp = last = NULL;
		for(j = 0; j < vertices; j++)
		{
			if(i == j)
				continue;

			printf("[ %d ~ %d ] = ", i, j);
			scanf("%d",&option);

			if(option)
			{
				temp = (struct node *)malloc(sizeof(struct node));
				temp->vertex = j;
				temp->link = NULL;

				if(last == NULL) graph[i] = temp;
				else last->link = temp;
				last = temp;

			}
		}
	}


	return graph;

}




void VertexCoverApproximation(struct node **graph, int vertices)
{

	//Complexity would be O( |V| * |E| ) --> worst case (complete graph) O( N^3 ) --> polynomial
	//because the graph is untouched

	int answerSet[VERTICES] = {};
	int visited[VERTICES] = {};
	//visited is required because consider a vertex whose edges are all covered by other vertex and 
	//there is no edge left in it to cover 
	//we cannot add this to answerSet so visted can be used to overcome the problem

	struct node *edge = NULL;
	int i;

	for(i = 0; i < vertices; i++)
	{
		if(visited[i] == FALSE)
		{
			//find that edge which is not covered and include it
			edge = graph[i];
			while(edge && answerSet[edge->vertex] == TRUE) edge = edge->link;

			if(edge)
			{
				answerSet[i] = answerSet[edge->vertex] = TRUE;
				visited[i] = visited[edge->vertex] = TRUE;	
			}
			else
				//all vertices are covered not need to insert into answer set
				visited[i] = TRUE;
		}
	}


	printf("\nAPPROXIMATION OF VERTICES IN MINIMAL VERTEX COVER SET\n");
	for(i = 0; i < vertices; i++)
	{
		if(answerSet[i] == TRUE)
			printf("[ %d ]\n", i);
	}
}



int main()
{
	int vertices;
	printf("\nNumber of vertices :: ");
	scanf("%d",&vertices);

	struct node **graph = NULL;
	graph = createGraph(vertices);
	
	VertexCoverApproximation(graph, vertices);

	printf("\n\n");

	return 0;
}
