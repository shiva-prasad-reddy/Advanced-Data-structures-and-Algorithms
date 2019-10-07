#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define VERTICES 6 
#define EDGES 15

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


int getMinimum(struct EdgeCost *(graph[]), int totalEdges, int *visitedEdges)
{
	int i, min  = -100;

	for(i = 0; i < totalEdges; i++)
	{	
		//finding minimum adjacent edge
		if(visitedEdges[i] == FALSE)
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


int checkCycle(int *visited, int u, int v)
{
	while(visited[u] != -1) u = visited[u];
	while(visited[v] != -1) v = visited[v];
	if(u == v) return -100;
	return u;
}

void kruskals(struct EdgeCost *(graph[]), int totalEdges)
{
	int visitedEdges[EDGES] = {};
	int visited[VERTICES];
	int MST[EDGES] = {};

	int i;
	for(i = 0; i < VERTICES; i++)
		visited[i] = -1;

	struct EdgeCost *edge = NULL;
	int min = getMinimum(graph, totalEdges, visitedEdges);
	do
	{
		visitedEdges[min] = TRUE;
		edge = graph[min];
		if((i = checkCycle(visited, edge->u, edge->v)) != -100 ) //cycle skip just dont add
		{
			visited[i] = edge->v;
			MST[min] = TRUE;
		}
		min = getMinimum(graph, totalEdges, visitedEdges);

	} while(min != -100);

	int mstCost = 0;	
	printf("EDGES IN MINIMUM SPANNING TREE\n");
	for(i = 0; i < totalEdges; i++)
	{
		if(MST[i] == TRUE)
		{
			printf("(%d, %d)\n", graph[i]->u, graph[i]->v);
			mstCost += graph[i]->cost;
		}	
	}
	printf("Cost of MST -->  %d\n", mstCost);


}


int main()
{
	struct EdgeCost *(graph[EDGES]);
	//List can also be generated from matrix representation
	
	pushEdge(graph, 0, 1, 5);
	pushEdge(graph, 1, 2, 2);
	pushEdge(graph, 2, 3, 8);
	pushEdge(graph, 3, 4, 9);
	pushEdge(graph, 4, 5, 6);
	pushEdge(graph, 0, 5, 3);
	int x = pushEdge(graph, 1, 4, 1);
	
	/*
	pushEdge(graph, 0, 1, 2);
	pushEdge(graph, 1, 2, 3);
	pushEdge(graph, 0, 3, 6);
	pushEdge(graph, 3, 4, 9);
	pushEdge(graph, 1, 3, 8);
	int x = pushEdge(graph, 1, 4, 5);
	*/

	kruskals(graph, x);
	return 0;
	
}