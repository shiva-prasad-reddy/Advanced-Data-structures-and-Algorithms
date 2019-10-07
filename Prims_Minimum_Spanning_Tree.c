#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define VERTICES 5
#define EDGES 10

struct EdgeCost
{
	int u;
	int cost;
	int v;
};

struct EdgeCost *newNode(int u, int v, int cost)
{
	struct EdgeCost *temp = NULL;
	temp = (struct EdgeCost *)malloc(sizeof(struct EdgeCost));
	temp->u = u;
	temp->v = v;
	temp->cost = cost;
	return temp;
}

int pushEdge(struct EdgeCost *(graph[]), int u, int v, int cost)
{
	static int i = 0;
	graph[i++] = newNode(u, v, cost);
	return i;
}


int pushAdjacentEdgesAndGetMinimum(struct EdgeCost *(graph[]), int totalEdges, int *visited, int *adjacentEdges, int edgeIndex)
{
	int i;
	struct EdgeCost *temp = NULL, *edge = NULL;
	edge = graph[edgeIndex];

	int min  = -100;

	for(i = 0; i < totalEdges; i++)
	{
		//adding adjacent edges to list
		temp = graph[i];
		if(visited[temp->u] && visited[temp->v])
			continue;
		else
			if(edge->u == temp->u || edge->u == temp->v || edge->v == temp->u || edge->v == temp->v)
				adjacentEdges[i] = TRUE;

		//finding minimum adjacent edge
		if(adjacentEdges[i] == TRUE)
		{
			if(min == -100)
				min = i;
			else
				if(graph[i]->cost < graph[min]->cost)
					min = i;
		}

	}
	return min;
}


void prims(struct EdgeCost *(graph[]), int edgeToStart, int totalEdges)
{
	int adjacentEdges[EDGES] = {};
	int visited[VERTICES] = {};
	int MST[EDGES] = {};

	struct EdgeCost *edge = NULL;
	int min = edgeToStart;
	do
	{
		edge = graph[min];
		adjacentEdges[min] = FALSE;
		visited[edge->u] = visited[edge->v] = TRUE;
		MST[min] = TRUE;
		min = pushAdjacentEdgesAndGetMinimum(graph, totalEdges, visited, adjacentEdges, min);

	} while(min != -100);


	int i = 0, mstCost = 0;
	printf("EDGES IN MINIMUM SPANNING TREE\n");
	while(i < totalEdges)
	{
		if(MST[i] != 0)
		{
			printf("(%d, %d)\n", graph[i]->u, graph[i]->v);
			mstCost += graph[i]->cost;
		}
		i++;
	}
	printf("Cost of MST -->  %d\n", mstCost);


}


int main()
{
	struct EdgeCost *(graph[EDGES]);
	//List can also be generated from matrix representation
	/*
	pushEdge(graph, 0, 1, 5);
	pushEdge(graph, 1, 2, 2);
	pushEdge(graph, 2, 3, 8);
	pushEdge(graph, 3, 4, 9);
	pushEdge(graph, 4, 5, 6);
	pushEdge(graph, 0, 5, 3);
	int totalEdges = pushEdge(graph, 1, 4, 1);
	*/

	pushEdge(graph, 0, 1, 2);
	pushEdge(graph, 1, 2, 3);
	pushEdge(graph, 0, 3, 6);
	pushEdge(graph, 3, 4, 9);
	pushEdge(graph, 1, 3, 8);
	int x = pushEdge(graph, 1, 4, 5);

	prims(graph, 0, x);
	return 0;
	
}