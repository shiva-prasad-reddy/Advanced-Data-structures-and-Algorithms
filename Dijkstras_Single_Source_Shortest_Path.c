#include<stdio.h>
#include<limits.h>
#define TRUE 1
#define FALSE 0
#define VERTICES 5



int minIndex(int *cost, int *visited, int source)
{
	int minIndex = source;
	int i=0;
	while(i < VERTICES)
	{
		if(cost[i] < cost[minIndex] && visited[i] == FALSE)
			minIndex = i;
		i++;
	}
	//if source is returned the algorithm is stopped
	return minIndex;
}


void start(int graph[VERTICES][VERTICES], int *cost, int *visited, int *parent, int curr, int source)
{
	int i;
	visited[curr] = TRUE;
	for(i = 0; i < VERTICES; i++)
	{
		if(curr == source)
		{
			if(graph[curr][i] != 0)
			{
				cost[i] = graph[curr][i];
				parent[i] = curr;
			}
		}
		else
		{
			if(visited[i] == TRUE)
				continue;
			//overflow INT_MAX + anything and reches to negative
			int sum = graph[curr][i] == 0 ? INT_MAX : (graph[curr][i] + cost[curr]);
			if(cost[i] > sum)
			{
				parent[i] = curr;
				cost[i] = sum;
			}
		}
	}
	
	int mI = minIndex(cost, visited, source);
	
	if(mI != source)
		start(graph, cost, visited, parent, mI, source);
	else
	{
		printf("  COST(FROM, TO) = C \t PATH\n");
		int prev;
		for(i = 0; i < VERTICES; i++)
		{
			if(i != source)
			{
				printf("  COST(%d, %d) =  %d \t", source, i, cost[i]);
				prev = i;
				while(prev != source)
				{
					printf("%d -- ", prev);
					prev = parent[prev];
				}
				printf("%d", source);
				printf("\n");
			}
		}


	}

}

void dijkstras(int graph[VERTICES][VERTICES], int source)
{
	int visited[VERTICES], parent[VERTICES], cost[VERTICES];
	int i;
	for(i = 0; i < VERTICES; i++)
	{
		visited[i] = FALSE;
		parent[i] = -1;
		cost[i] = INT_MAX;
	}
	parent[source] = source;
	start(graph, cost, visited, parent, 0, 0);
}




int main()
{

	int graph[VERTICES][VERTICES] = {
							{0, 1, 5, 0, 0},
							{1, 0, 0, 0, 6},
							{5, 0, 0, 3, 1},
							{0, 0, 3, 0, 1},
							{0, 6, 1, 1, 0}
									};
	/*
	int graph[VERTICES][VERTICES] = { 
						{ 0, 4, 0, 0, 0, 0, 0, 8, 0 }, 
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 }, 
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 }, 
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 }, 
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 }, 
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 }, 
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 }, 
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 }, 
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } 
                    };
    */

	dijkstras(graph, 0);
	return 0;
	
}