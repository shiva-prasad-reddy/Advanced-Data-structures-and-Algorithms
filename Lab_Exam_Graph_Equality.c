#include<stdio.h>
#include<stdlib.h>


struct edge 
{
	int vertex;
	struct edge *link;
};

struct Graph
{
	struct edge **edgeList;
	int *inDegree;
	int *outDegree;
	int vertices;
};

struct Graph *createGraph(int vertices)
{
	struct Graph *graph = NULL;
	graph = (struct Graph *)calloc(1, sizeof(struct Graph));
	graph->vertices = vertices;
	graph->inDegree = (int *)calloc(vertices, sizeof(int));
	graph->outDegree = (int *)calloc(vertices, sizeof(int));
	graph->edgeList = (struct edge **)calloc(vertices, sizeof(struct edge *));
	return graph;
}

struct Graph *initializeGraph(int vertices)
{

	struct Graph *graph = createGraph(vertices);
	struct edge **edgeList = graph->edgeList;

	struct edge *temp, *last;
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
				//Updating InDegree and OutDegree
				graph->outDegree[i]++;
				graph->inDegree[j]++;

				temp = (struct edge *)malloc(sizeof(struct edge));
				temp->vertex = j;
				temp->link = NULL;
				if(last == NULL) edgeList[i] = temp;
				else last->link = temp;
				last = temp;
			}
		}
	}
	return graph;
}

//Assume the out degree of each vertex is unique
int *findMapping(struct Graph *graph1, struct Graph *graph2)
{
	int vertices = graph1->vertices;
	int *map = (int *)calloc(vertices, sizeof(int));
	for(int i = 0; i < vertices; i++)
	{
		for(int j = 0; j < vertices; j++)
		{
			if(graph1->outDegree[i] == graph2->outDegree[j])
			{
				map[i] = j;
				break;
			}
		}
	}
	return map;
}

int checkEquality(struct Graph *graph1, struct Graph *graph2, int *map)
{
	int x;
	for(int i = 0; i < graph1->vertices; i++)
	{
		x = map[i];
		if(graph1->inDegree[i] != graph2->inDegree[x]  ||  graph1->outDegree[i] != graph2->outDegree[x])
			return 0;
	}
	return 1;
}

void freeMemory(struct Graph *graph)
{
	free(graph->inDegree);
	free(graph->outDegree);
	struct edge *temp;
	for(int i = 0; i < graph->vertices; i++)
	{
		while(graph->edgeList[i])
		{
			temp = graph->edgeList[i];
			graph->edgeList[i] = graph->edgeList[i]->link;
			free(temp);
		}
	}
	free(graph->edgeList);
	free(graph);
}

int main()
{
	int vertices;
	struct Graph *graph1, *graph2;


	printf("\nEnter number of vertices for graph1 >> ");
	scanf("%d", &vertices);
	graph1 = initializeGraph(vertices);


	printf("\nEnter number of vertices for graph2 >> ");
	scanf("%d", &vertices);
	graph2 = initializeGraph(vertices);

	if(graph1->vertices != graph2->vertices)
	{
		printf("\nGraphs are not equal\n");
		return 0;
	}


	printf("\nIn and Out Degrees of Graph 1\n");
	for(int i = 0; i < vertices; i++)
		printf("Vertex = [ %d ],  In = [ %d ],  Out = [ %d ]\n", i, graph1->inDegree[i], graph1->outDegree[i]);

	printf("\nIn and Out Degrees Graph 2\n");
	for(int i = 0; i < vertices; i++)
		printf("Vertex = [ %d ],  In = [ %d ],  Out = [ %d ]\n", i, graph2->inDegree[i], graph2->outDegree[i]);

	int *map = NULL;
	map = findMapping(graph1, graph2);
	printf("\n\n==== Mapping ==== \n");
	for(int i = 0; i < vertices; i++)
		printf("[ %d ] --> [ %d ]\n", i, map[i]);
	printf("===================\n");

	if(checkEquality(graph1, graph2, map))
		printf("\nGraphs are equal\n");
	else
		printf("\nGraphs are not equal\n");



	free(map);
	freeMemory(graph1);
	freeMemory(graph2);
	printf("\n");
	return 0;
}