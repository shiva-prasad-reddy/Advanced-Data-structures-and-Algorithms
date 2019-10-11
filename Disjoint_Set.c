
//Disjoint sets can also be represented using linked list ((doubly))
/*

struct vertex
{
	int name;
	struct vertex *parent;
	struct vertex *next;
}

*/



#include<stdio.h>
#include<stdlib.h>

#define FALSE 0
#define TRUE 1
#define VERTICES 6 
#define EDGES 15

//##########################################
struct EdgeCost
{
	int u;
	int v;
};

struct EdgeCost *newNode(int u, int v)
{
	struct EdgeCost *temp = NULL;
	temp = (struct EdgeCost *)malloc(sizeof(struct EdgeCost));
	temp->u = u;
	temp->v = v;
	return temp;
}

int pushEdge(struct EdgeCost *(graph[]), int u, int v)
{
	static int edge_count = 0;
	graph[edge_count++] = newNode(u, v);
	return edge_count;
}

//################################################

int weight(int *set, int index)
{
	return set[index];
}


int collapsing_find(int *set, int parent)
{
	int index = parent;
	while(set[parent] > 0)
		parent = set[parent];

	set[index] = parent; //collapsing find
	return parent;

}

int find(int *set, int parent)
{
	while(set[parent] >= 0)
		parent = set[parent];

	return parent;
}

//weight or rank is the no. of elements in that set
void weighted_union(int *set, int u_parent, int v_parent, int u, int v)
{
	if(weight(set, u_parent) <= weight(set, v_parent))
	{
		set[u_parent] += set[v_parent];
		set[v] = u;
	}
	else
	{
		set[v_parent] += set[u_parent];
		set[u] = v;
	}
}


void find_cycle(struct EdgeCost *(graph[]), int totalEdges)
{
	//JUST FINDING CYCLE EXISTS OR NOT IN A GRAPH
	
	struct EdgeCost *edge = NULL;

	int set[VERTICES], u_parent, v_parent;

	for(int i = 0; i < VERTICES; i++) set[i] = -1;

	for(int i = 0; i < totalEdges; i++)
	{
		edge = graph[i];
		//printf("ADDING EDGE >> [ %d -- %d ]\n", edge->u, edge->v);
		u_parent = find(set, edge->u);
		v_parent = find(set, edge->v);
		//printf("parents >> [ %d -- %d ]\n", u_parent, v_parent);
		if(u_parent == v_parent)
		{
			printf("CYCLE FOUND\n");
		}
		else
		{
			weighted_union(set, u_parent, v_parent, edge->u, edge->v);
			//printf("SET >> \n");
			//for(int j = 0; j < VERTICES; j++) printf("[ %d -- %d ]\n", j, set[j]);
		}

	}

	printf("SET >> \n");
	for(int j = 0; j < VERTICES; j++) printf("[ %d -- %d ]\n", j, set[j]);

}


int main()
{
	struct EdgeCost *(graph[EDGES]);
	pushEdge(graph, 3, 4);
	pushEdge(graph, 0, 1);
	pushEdge(graph, 4, 5);
	pushEdge(graph, 2, 3);
	pushEdge(graph, 0, 5);
	pushEdge(graph, 1, 2);
	int edge_count = pushEdge(graph, 1, 4);

	find_cycle(graph, edge_count);
}
