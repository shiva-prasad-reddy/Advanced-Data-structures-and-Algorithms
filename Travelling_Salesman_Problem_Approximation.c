#include<stdio.h>
#include<stdlib.h>
#define MAX_DEGREE 20

#define VERTICES 20
#define FALSE 0
#define TRUE 1

struct tsp_node 
{
	int from;
	int to;

	int weight;

	struct tsp_node *link;
};



//########################################################################

struct node
{
	int MARK;
	struct node *parent;
	struct node *prev;
	struct tsp_node *key;
	struct node *next;
	struct node *child;
	int n; //No of nodes in its child List
};

struct FbHeap
{
	struct node *minNode;
	int degreeMax;
	int n; // No of nodes in the root list
};


struct node *newNode(struct tsp_node *key)
{
	struct node *temp = NULL;
	temp = (struct node *)calloc(1, sizeof(struct node));
	temp->key = key;
	temp->prev = temp->next = temp;
	return temp;
}


struct FbHeap *createFbHeap()
{
	struct FbHeap *heap = NULL;
	heap = (struct FbHeap *)calloc(1, sizeof(struct FbHeap));
	heap->degreeMax = MAX_DEGREE;
	return heap;
}


void INSERT(struct FbHeap *heap, struct node *temp)  //int key)
{
	if(heap->minNode == NULL) heap->minNode = temp;
	else
	{
		struct node *minNode = heap->minNode;
		//attach temp into root list
		temp->next = minNode->next;
		temp->next->prev = temp;
		temp->prev = minNode;
		minNode->next = temp;

		if(temp->key->weight < minNode->key->weight) heap->minNode = temp;
	}
	heap->n += 1;
}


struct FbHeap *UNION(struct FbHeap *heapOne, struct FbHeap *heapTwo)
{
	if(!heapOne->minNode)
		return heapTwo;
	if(!heapTwo->minNode)
		return heapOne;

	struct node *heapOneMinNode, *heapTwoMinNode;
	heapOneMinNode = heapOne->minNode;
	heapTwoMinNode = heapTwo->minNode;


	heapTwoMinNode->prev->next = heapOneMinNode->next;
	heapOneMinNode->next->prev = heapTwoMinNode->prev;

	heapOneMinNode->next = heapTwoMinNode;
	heapTwoMinNode->prev = heapOneMinNode;


	if(heapTwoMinNode->key->weight < heapOneMinNode->key->weight)
		heapOne->minNode = heapTwoMinNode;

	heapOne->n += heapTwo->n;

	return heapOne;
}

void LINK_UP(struct node *c, struct node *parent)
{
	if(parent->child)
	{
		c->next = parent->child;
		c->prev = parent->child->prev;
		if(c->prev) c->prev->next = c;
		if(c->next) c->next->prev = c;
	}
	else
		c->next = c->prev = c;

	c->parent = parent;
	parent->child = c;
	parent->n += 1;
	c->MARK = FALSE;
}

void CONSOLIDATE(struct FbHeap *heap)
{
	struct node *(A[MAX_DEGREE]) = {};
	int i = 1;
	struct node *dll = heap->minNode;
	
	struct node *x = NULL, *y = NULL;
	int d;
	while(i <= heap->n)
	{
		x = dll;
		dll = dll->next;
		d = x->n;
		while(A[d] != NULL)
		{
			y = A[d];
			if(y->key->weight < x->key->weight)
			{
				LINK_UP(x, y); //child, parent
				x = y;
			}
			else
			{
				LINK_UP(y, x); //child, parent
			}

			A[d] = NULL;
			d++;

		}
		A[d] = x;
		i++;
	}
	x = NULL;
	i=0;
	heap->n = 0;
	while(i < MAX_DEGREE)
	{
		if(A[i])
		{	
			A[i]->parent = NULL;
			heap->n += 1;
			A[i]->MARK = FALSE;
			if(!x)
			{
				x = A[i];
				x->next = x->prev = x;
			}
			else
			{
				//add A[i] to root list
				A[i]->next = x->next;
				x->next->prev = A[i];
				A[i]->prev = x;
				x->next = A[i];

				if(A[i]->key->weight < x->key->weight)
					x = A[i];
			}			
		}
		i++;
	}
	heap->minNode = x;
}

void EXTRACT_MIN(struct FbHeap *heap)
{
	struct node *minNode = NULL;
	minNode = heap->minNode;

	if(heap->n == 1)
	{
		heap->minNode = NULL;
		heap->n = 0;
	}
	else
	{
		heap->minNode = minNode->next;
		minNode->next->prev = minNode->prev;
		minNode->prev->next = minNode->next;
		heap->n -=  1;
	}

	struct FbHeap *newHeap = NULL;
	newHeap = createFbHeap();
	newHeap->minNode = minNode->child;
	newHeap->n = minNode->n;

	struct FbHeap *h = NULL;
	h = UNION(heap, newHeap);
	CONSOLIDATE(h);

	heap->minNode = h->minNode;
	heap->n = h->n;

	free(newHeap);
	free(minNode);
}


//##############################################################################################

















struct tsp_node **createGraph(int vertices)
{
	struct tsp_node **graph = (struct tsp_node **)calloc(vertices, sizeof(struct tsp_node *));
	struct tsp_node *temp, *last;
	int i,j,weight;
	printf("[ YES -> weight ]  OR  [ NO -> 0 ]\n");
	for(i = 0; i < vertices; i++)
	{
		temp = last = NULL;
		for(j = i+1; j < vertices; j++)
		{
			//if(i == j)
			//	continue;

			printf("[ %d ~ %d ] = ", i, j);
			scanf("%d",&weight);

			if(weight)
			{
				temp = (struct tsp_node *)malloc(sizeof(struct tsp_node));
				
				temp->from = i;
				temp->to = j;

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



void addEdgeToMSTGraph(struct tsp_node **graph, struct tsp_node *temp)
{
	struct tsp_node *nodeToadd = NULL;
	nodeToadd = (struct tsp_node *)malloc(sizeof(struct tsp_node));

	*nodeToadd =  *temp;
	nodeToadd->link = NULL;

	temp = graph[nodeToadd->from];
	if(temp)
	{
		while(temp->link) temp = temp->link;
		temp->link = nodeToadd;
	}
	else
	{
		graph[nodeToadd->from] = nodeToadd;
	}

}

struct tsp_node **MST_Prims(struct tsp_node **graph, int source, int vertices)
{
	int visited[VERTICES] = {};
	struct FbHeap *heap = NULL;
	heap = createFbHeap();

	struct tsp_node **mst = (struct tsp_node **)calloc(vertices, sizeof(struct tsp_node *));

	struct tsp_node *temp = NULL, *min = NULL;
	temp = graph[source];
	while(temp)
	{
		INSERT(heap, newNode(temp));
		temp = temp->link;
	}
	visited[source] = TRUE;
	printf("\n\nEdges in MST\n");
	while(heap->minNode) //until minnode exists
	{
		min = heap->minNode->key;
		EXTRACT_MIN(heap);

		source = min->to;
		if(visited[source] == FALSE)
		{
			printf("[%d -- %d]\n", min->from, min->to);
			addEdgeToMSTGraph(mst, min);
			temp = graph[source];
			while(temp)
			{
				INSERT(heap, newNode(temp));
				temp = temp->link;
			}
			visited[source] = TRUE;
		}

	}

	return mst;

}


void preorder(struct tsp_node **mst, int source)
{
	printf("%d -- ", source);
	struct tsp_node *temp = mst[source];
	while(temp)
	{
		preorder(mst, temp->to);
		temp = temp->link;
	}
}


int main()
{
	int vertices;
	printf("\nNumber of vertices :: ");
	scanf("%d",&vertices);

	struct tsp_node **graph = NULL;
	graph = createGraph(vertices);

	struct tsp_node **mst = NULL;
	int source = 0;
	mst = MST_Prims(graph, source, vertices);

	printf("\nApproximation of TSP (Graph follows Triangular Inequality Condition)\n");
	preorder(mst, source);
	printf("%d\n\n", source);


	return 0;
	
}