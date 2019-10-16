
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#include "FIB_HEAP_TSP.h"

struct tsp_node 
{
	int vertex;
	int weight;
	struct tsp_node *link;
};


struct tsp_node **createGraph(int vertices)
{
	struct tsp_node **graph = (struct tsp_node **)calloc(vertices, sizeof(struct tsp_node *));
	struct tsp_node *temp, *last;
	int i,j,weight;
	printf("\n\t[ YES -> weight ]  OR  [ NO -> 0 ]\n\n");
	for(i = 0; i < vertices; i++)
	{
		temp = last = NULL;
		for(j = 0; j < vertices; j++)
		{
			if(i == j)
				continue;

			printf("[ %d ~ %d ] = ", i, j);
			scanf("%d",&weight);

			if(weight)
			{
				temp = (struct tsp_node *)malloc(sizeof(struct tsp_node));
				temp->vertex = j;

				temp->link = NULL;
				temp->weight = weight;

				if(last == NULL) graph[i] = temp;
				else last->link = temp;
				last = temp;
			}
		}
	}
	return graph;
}


// --- O(X)
void addEdgeToMSTGraph(struct tsp_node **graph, int parentVertex, int vertex, int weight)
{

	if(parentVertex == -1 || weight == 0)
		return;

	printf("[%d -- %d]\n", parentVertex, vertex);

	struct tsp_node *temp = NULL, *t = NULL;
	temp = (struct tsp_node *)malloc(sizeof(struct tsp_node));

	temp->vertex = vertex;
	temp->link = NULL;
	temp->weight = weight;

	//ORDER IS MAINTAINED
	t = graph[parentVertex];
	if(t)
	{
		while(t->link) t = t->link;
		t->link = temp;
	}
	else
	{
		graph[parentVertex] = temp;
	}
}


// ---   V*log(V) + V*X + V(V-1) == V*log(V) + V*X + 2E 
// --- X can be made O(1) with additional array to keep track of last pointers
// --- O(E + V*log(V))

struct tsp_node **MST_Prims(struct FbHeap *heap, struct tsp_node **graph, struct node **Map, int vertices)
{
	
	int *visited = (int *)calloc(vertices, sizeof(int));
	
	struct tsp_node **mst = (struct tsp_node **)calloc(vertices, sizeof(struct tsp_node *));
	struct tsp_node *temp = NULL;
	
	struct node *min = NULL;
	int totalCost = 0;

	printf("\n\nEdges in MST\n");
	while(heap->minNode) // --- V
	{
		min = EXTRACT_MIN(heap); // --- V * log(V)
		visited[min->vertex] = TRUE;

		addEdgeToMSTGraph(mst, min->parentVertex, min->vertex, min->key); // --- V * O(X)
		totalCost += min->key;

		temp = graph[min->vertex];
		while(temp) // --- V * O(V-1)
		{
			if(visited[temp->vertex] == FALSE) 
				DECREASE_KEY(heap, Map[temp->vertex], temp->weight, min->vertex);
			temp = temp->link;
		}
	}
	printf("\nTotal cost of MST => [ %d ]\n", totalCost);

	free(visited);

	return mst;

}


void preorder(struct tsp_node **mst, int source, struct node **Map)
{
	printf("%d -- ", source);
	struct tsp_node *temp = mst[source];
	while(temp)
	{
		preorder(mst, temp->vertex, Map);
		temp = temp->link;
	}


	//removing fibnoacci nodes 
	//recursive approach so every node gets visited once and memory is freed
	free(Map[source]);
	Map[source] = NULL;
	
}


void freeMemory(struct tsp_node **graph, int vertices)
{
	struct tsp_node *temp = NULL;
	int i;	
	for(i = 0; i< vertices; i++)
	{
		while(graph[i])
		{
			temp = graph[i];
			graph[i] = graph[i]->link;
			free(temp);
		}
	}
}

int main()
{
	int vertices, i , source;
	source = 0;

	printf("\nNumber of vertices :: ");
	scanf("%d",&vertices);

	struct tsp_node **graph = NULL;
	graph = createGraph(vertices);

	struct FbHeap *heap = NULL;
	heap = createFbHeap();

	struct node **Map = (struct node **)calloc(vertices, sizeof(struct node *));

	//int key, int vertex, int parentVertex

	Map[source] = newNode(0, source, -1);	
	INSERT(heap, Map[source]);

	for(i = 0; i < vertices; i++)
	{
		if(i != source)
		{
			Map[i] = newNode(INT_MAX, i, -1);
			INSERT(heap, Map[i]);
		}
	}

	struct tsp_node **mst = NULL;
	mst = MST_Prims(heap, graph, Map, vertices);

	printf("\nApproximation of TSP (Graph follows Triangular Inequality Condition)\n");
	preorder(mst, source, Map);
	printf("%d\n\n", source);

	//Memory CleanUp
	free(heap);
	freeMemory(graph, vertices);
	free(graph);
	free(Map);
	freeMemory(mst, vertices);
	free(mst);

	return 0;
	
}
