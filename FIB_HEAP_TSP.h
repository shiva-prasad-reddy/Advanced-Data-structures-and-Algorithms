#define MAX_DEGREE 20
#define FALSE 0
#define TRUE 1

struct node
{
	int MARK;
	struct node *parent;
	struct node *prev;
	
	int key;
	int vertex;
	int parentVertex;

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


struct node *newNode(int key, int vertex, int parentVertex)
{
	struct node *temp = NULL;
	temp = (struct node *)calloc(1, sizeof(struct node));
	temp->key = key;
	temp->vertex = vertex;
	temp->parentVertex = parentVertex;
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


void INSERT(struct FbHeap *heap, struct node *temp)
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

		if(temp->key < minNode->key) heap->minNode = temp;
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


	if(heapTwoMinNode->key < heapOneMinNode->key)
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
			if(y->key < x->key)
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
				A[i]->next = x->next;
				x->next->prev = A[i];
				A[i]->prev = x;
				x->next = A[i];

				if(A[i]->key < x->key)
					x = A[i];
			}

			
		}
		i++;
	}
	heap->minNode = x;
}

struct node *EXTRACT_MIN(struct FbHeap *heap)
{
	if(!heap->minNode) return NULL;
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
	//free(minNode);
	return minNode;

}

void CUT(struct FbHeap *heap, struct node *parent, struct node *child)
{
	parent->n -= 1;
	if(parent->child == child)
		if(parent->n == 0)
			parent->child == NULL;
		else
			parent->child = child->next;
	
	child->next->prev = child->prev;
	child->prev->next = child->next;

	child->parent = NULL;
	child->prev = child->next = child;

	INSERT(heap, child);
}


void CASCADE_CUT(struct FbHeap *heap, struct node *nodeTobeMarked)
{
	if(nodeTobeMarked->MARK == TRUE)
	{
		struct node *parent = NULL;
		parent = nodeTobeMarked->parent;
		CUT(heap, parent, nodeTobeMarked);
		CASCADE_CUT(heap, parent); 
	}
	else
		if(nodeTobeMarked->parent) nodeTobeMarked->MARK = TRUE;
}


void DECREASE_KEY(struct FbHeap *heap, struct node *Node, int key, int parentVertex)
{
	if(key >= Node->key)
		return;
	struct node *parent = NULL;
	parent = Node->parent;

	Node->key = key;
	Node->parentVertex = parentVertex;

	if(parent == NULL)
		if(key < heap->minNode->key)
			heap->minNode = Node;

	if(parent && parent->key > Node->key)
	{
		CUT(heap, parent, Node); //heap, parent, child
		CASCADE_CUT(heap, parent);
	}

}
