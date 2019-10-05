#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_DEGREE 20

struct node
{
	int MARK;
	struct node *parent;
	struct node *prev;
	int key;
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


struct node *newNode(int key)
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
	//printf("LINK_UP -- %d to %d\n", c->key, parent->key);
	if(parent->child)
	{
		c->next = parent->child;
		c->prev = parent->child->prev;
		//printf("OK\n");
		if(c->prev) c->prev->next = c;
		if(c->next) c->next->prev = c;
	}
	else
		c->next = c->prev = c;

	c->parent = parent;
	parent->child = c;

	parent->n += 1;

	//if LINK_UP called independently

	c->MARK = FALSE;


	//printf("EXIT\n");

}

void CONSOLIDATE(struct FbHeap *heap)
{
	//printf("CONSOLIDATE\n");
	struct node *(A[MAX_DEGREE]) = {};
	int i = 1;
	struct node *dll = heap->minNode;
	
	struct node *x = NULL, *y = NULL;
	int d;
	while(i <= heap->n) //heap->n is a wrong statement -- not modifyin heap so correct 
	{
		//printf("OMG\n");
		x = dll;
		dll = dll->next;
		// check this wrong statement --> confusion  -- proved
		// root list gets modified dll->next may or may not exists in the root list --proved
		//the next dll node doesn't exists in the list at all

		d = x->n;

		while(A[d] != NULL)
		{
			//printf("SEE\n");
			y = A[d];
			//removin y from root list but not necessary 
			// do it in finding minNode


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

	//write code to make parent pointers to null and find next min in EXTRACT_MIN()
	//it is better if you write code in EXTRACT_MIN() 
	//find min node in root list and find min node in minimum node child list so more complexity
	//here the array gets consolidated so the time complexity would not be more than O(d) for finding min node
	//printf("CREATING ROOT LIST\n");
	//consider x as min node
	x = NULL;
	i=0;
	heap->n = 0;
	while(i < MAX_DEGREE)
	{
		if(A[i])
		{	
			A[i]->parent = NULL;
			heap->n += 1;
			//CHECK
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

				if(A[i]->key < x->key)
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

void CUT(struct FbHeap *heap, struct node *parent, struct node *child)
{
	//printf("Cut\n");
	parent->n -= 1;
	if(parent->child == child)
		if(parent->n == 0)
			parent->child == NULL;
		else
			parent->child = child->next;
	
	//printf("Happy\n");
	//printf("%p %p\n",child->prev, child->next);
	//remove child
	child->next->prev = child->prev;
	child->prev->next = child->next;
	//printf("Happy\n");
	child->parent = NULL;
	child->prev = child->next = child;
	//printf("Happy\n");
	//inserting child in root list
	INSERT(heap, child);
	//printf("Happy\n");
}


void CASCADE_CUT(struct FbHeap *heap, struct node *nodeTobeMarked)
{
	//printf("Cascade cut\n");
	if(nodeTobeMarked->MARK == TRUE)
	{
		struct node *parent = NULL;
		parent = nodeTobeMarked->parent;

		//cut nodeTobeMarked from list and add to root list
		
		CUT(heap, parent, nodeTobeMarked);
		CASCADE_CUT(heap, parent); 


	}
	else
		if(nodeTobeMarked->parent) nodeTobeMarked->MARK = TRUE;
}


void DECREASE_KEY(struct FbHeap *heap, struct node *Node, int key)
{
	//printf("Decrease key\n");
	if(key >= Node->key)
		return;
	struct node *parent = NULL;
	parent = Node->parent;

	Node->key = key;

	if(parent == NULL)
		if(key < heap->minNode->key)
			heap->minNode = Node;

	if(parent && parent->key > Node->key)
	{
		CUT(heap, parent, Node); //heap, parent, child
		//printf("Good\n");
		CASCADE_CUT(heap, parent);
	}

}


void DELETE(struct FbHeap *heap, struct node *Node)
{

	DECREASE_KEY(heap, Node, -1000);
	EXTRACT_MIN(heap);

}

//minNode, minNode
struct node *findNode(struct node *parent, struct node *Node, int key) //head->next
{
	if(Node)
	{	
		//printf("parent [ %d ] Node [ %d ]\n", parent->key, Node->key);
		//printf("Hello %p \n", Node->child);
		if(Node->key == key) return Node;
		if(parent != Node->next)
		{
			if(key < Node->key) return findNode(parent, Node->next, key);
			else
			{
				struct node *temp = NULL;
				
				
				//if(Node->child) printf("%d\n", Node->child->key);
				temp = findNode(Node->child, Node->child, key);
	
				if(temp) return temp;
				else return findNode(parent, Node->next, key);
			}
		}
		else return findNode(Node->child, Node->child, key);
	}
	return NULL;
}




void levelOrderTraversal(struct FbHeap *heap)
{
	printf("\nLevel Order Traversal :: \n");
	struct node *(queue[30]);
	int front, rear;
	front = rear = -1;

	struct node *dummy = NULL;
	dummy = (struct node *)calloc(1, sizeof(struct node)); //free(dummy) >>> Memory leakage problem
	dummy->key = -1000;

	

	int i=1;
	struct node *dll = heap->minNode;

	while(i <= heap->n)
	{
		queue[++rear] = dll;
		dll = dll->next;
		i++;
	}

	queue[++rear] = dummy;

	struct node *temp = NULL;

	while((front+1) != rear)
	{
		temp = queue[++front];
		if(temp->key != -1000)
		{
			printf("%d(%d), ", temp->key, (temp->parent? temp->parent->key : 0));
			i=1;
			dll = temp->child;

			while(dll && i <= temp->n) // i <= temp->n is enough
			{
				//printf("parent -- %d\n", temp->key);
				queue[++rear] = dll;
				dll = dll->next;
				i++;
			}
			
		}
		else
		{
			queue[++rear] = dummy;
			printf("\n");
		}
	}

	printf("\n");
}


int main()
{
	int choice, key;
	choice = 7;
	struct FbHeap *heap = NULL;
	heap = createFbHeap();
	struct node *temp = NULL;


	INSERT(heap, newNode(5));
	INSERT(heap, newNode(6));
	INSERT(heap, newNode(7));
	INSERT(heap, newNode(15));
	INSERT(heap, newNode(16));
	INSERT(heap, newNode(17));
	//levelOrderTraversal(heap);
	//EXTRACT_MIN(heap);

	do
	{
		printf("\nSelect an option\n1.Insert\n2.Find minimum\n3.Extract minimum\n4.Find Node\n5.Decrease key\n6.Delete\n7.Level order traversal\n8.Exit\n\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("\nEnter the key :: ");
				scanf("%d", &key);
				INSERT(heap, newNode(key));
				break;
			case 2:
				if(heap->minNode) printf("Minimum Key [ %d ]\n", heap->minNode->key);
				else printf("\n\tEmpty.\n");
				break;
			case 3:
				if(heap->minNode) EXTRACT_MIN(heap);
				else printf("\n\tEmpty.\n");
				break;
			case 4:
				printf("\nKey to find :: ");
				scanf("%d", &key);
				if( heap->minNode && (temp = findNode(heap->minNode, heap->minNode, key)) )
					printf(" [ %d ] exists\n",temp->key);
				else
					printf("\n\tKey Doesn't exists.\n");
				break;
			case 5:
				printf("\nKey to decrease :: ");
				scanf("%d", &key);
				if( heap->minNode && (temp = findNode(heap->minNode, heap->minNode, key)) )
				{
					//printf(" [ %d ] exists\n",temp->key);
					printf("[ %d ] Key to be decreased to >> ", temp->key);
					scanf("%d", &key);
					DECREASE_KEY(heap, temp, key);
				}
				else
					printf("\n\tKey Doesn't exists.\n");
				break;
			case 6:
				printf("\nKey to delete :: ");
				scanf("%d", &key);
				if( heap->minNode && (temp = findNode(heap->minNode, heap->minNode, key)) )
				{
					DELETE(heap, temp);
				}
				else
					printf("\n\tKey Doesn't exists.\n");
				break;
			case 7:
				levelOrderTraversal(heap);
				break;
			case 8:
				break;
			default:
				printf("\tInvalid Choice.\n");
		}
	} while(choice != 8);

	return 0;
}
