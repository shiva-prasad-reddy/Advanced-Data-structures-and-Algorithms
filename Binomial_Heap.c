#include<stdio.h>
#include<stdlib.h>

struct BHnode
{
	int key;
	struct BHnode *leftchild, *rightChild, *parent;
	int degree;
};

struct BHnode *newNode(int key)
{
	struct BHnode *temp = NULL;
	temp = (struct BHnode *)malloc(sizeof(struct BHnode));
	temp->key = key;
	temp->leftchild = temp->rightChild = temp->parent = NULL;
	temp->degree = 0;
	return temp;
}

struct BHnode *FIND_MIN(struct BHnode *head)
{
	if(head)
	{
		struct BHnode *minNode = head;
		head = head->rightChild;
		while(head)
		{
			if(head->key < minNode->key) minNode = head;
			head = head->rightChild;
		}

		return minNode;
	}
	else
		return NULL;
}

struct BHnode *MERGE(struct BHnode *headOne, struct BHnode *headTwo)
{
	struct BHnode *head = NULL, *tail = NULL;

	while(headOne && headTwo)
	{
		if(headOne->degree == headTwo->degree)
		{
			if(head == NULL)
			{
				head = headOne;
				headOne = headOne->rightChild; //important
				head->rightChild = headTwo;
			}
			else
			{
				tail->rightChild = headOne;
				tail = headOne;
				headOne = headOne->rightChild; //important
				tail->rightChild = headTwo;
				
			}
			tail = headTwo;
			headTwo = headTwo->rightChild;
		}
		else
		{
			if(headOne->degree < headTwo->degree)
			{
				if(head == NULL) head = headOne;
				else tail->rightChild = headOne;

				tail = headOne;
				headOne = headOne->rightChild;
			}
			else
			{
				if(head == NULL) head = headTwo;
				else tail->rightChild = headTwo;

				tail = headTwo;
				headTwo = headTwo->rightChild;
			}
		}
	}

	if(headOne) tail->rightChild = headOne;
	if(headTwo) tail->rightChild = headTwo;

	return head;
}

void LINK_UP(struct BHnode *child, struct BHnode *parent)
{
	printf("\nLinking [ %d ] to [ %d ]\n", child->key, parent->key);
 	child->rightChild = parent->leftchild;
	child->parent = parent;
	parent->leftchild = child;
	parent->degree = parent->degree + 1;
}

struct BHnode *UNION(struct BHnode *headOne, struct BHnode *headTwo)
{
	if(!headOne)
		return headTwo;
	if(!headTwo)
		return headOne;

	struct BHnode *head, *prev, *curr, *next, *temp;
	head = MERGE(headOne, headTwo);
	
	prev = NULL;
	curr = head;
	next = curr->rightChild;

	while(next != NULL)
	{
		if( (curr->degree != next->degree) || ((next->rightChild != NULL) && (next->degree == next->rightChild->degree)))
		{
			prev = curr;
			curr = next;
			next = next->rightChild;
		}
		else
		{
			if(curr->key < next->key)
			{
				//curr becomes parent
				temp = next;
				next = next->rightChild;
				curr->rightChild = next; //important
				LINK_UP(temp, curr); //child, parent //(curr->rightChild, curr)
			}
			else
			{
				temp = curr;
				//next becomes parent
				if(prev != NULL)
					prev->rightChild = next;
				else
					head = next;

				LINK_UP(temp, next); //child, parent //(curr, next)
				curr = next;
				next = next->rightChild;
			}
		}
	}
	return head;
}

struct BHnode *reverseBH(struct BHnode *curr)
{
	struct BHnode *prev = NULL, *next = NULL;
	while(curr)
	{
		next = curr->rightChild;
		curr->rightChild = prev;
		curr->parent = NULL;
		prev = curr;
		curr = next;
	}
	return prev;
}

struct BHnode *EXTRACT_MIN(struct BHnode *head)
{
	struct BHnode *minNode = NULL, *newBH = NULL;
	minNode = FIND_MIN(head);
	if(!minNode) return head;
	printf("Extracting Minimum [ %d ]\n", minNode->key);
	//handle null cases in union
	//works for every case even for B0 and B1
	newBH = reverseBH(minNode->leftchild);

	//remove minNode from BH
	struct BHnode *trav = head;
	while(trav != minNode && trav->rightChild != minNode) trav = trav->rightChild;
	if(head == minNode) head = head->rightChild;
	else trav->rightChild = minNode->rightChild;
	free(minNode); //node pointer is in minNode

	return UNION(head, newBH);
}

struct BHnode *INSERT(struct BHnode *head, int key)
{
	return UNION(head, newNode(key));
}

void SWAP(struct BHnode *a, struct BHnode *b)
{
	int temp = a->key;
	a->key = b->key;
	b->key = temp;
}

void DECREASE_KEY(struct BHnode *node, int newKey)
{
	if(node->key <= newKey)
	{
		printf("Previous key [ %d ] is lesser than new key [ %d ]\n", node->key, newKey);
	}
	else
	{
		node->key = newKey;
		struct BHnode *parent = NULL;
		parent = node->parent;
		while(parent && node->key < parent->key)
		{
			SWAP(node, parent);
			node = parent;
			parent = node->parent;
		}
	}
}

//check it once
struct BHnode *findNode(struct BHnode *head, int key)
{
	if(head)
	{
		if(head->key == key) return head;
		if(key < head->key) return findNode(head->rightChild, key);
		else
		{
			struct BHnode *temp = NULL;
			temp = findNode(head->leftchild, key);
			if(temp) return temp;
			else return findNode(head->rightChild, key);
		}
	}
	return head;
}

struct BHnode *DELETE(struct BHnode *head, struct BHnode *keyNode)
{

	DECREASE_KEY(keyNode, -1000);
	return EXTRACT_MIN(head);
}

int main()
{
	int choice, key;
	choice = 7;
	struct BHnode *head, *temp;
	head = temp = NULL;
	head = INSERT(head, 5);
	head = INSERT(head, 6);
	head = INSERT(head, 7);
	head = INSERT(head, 10);
	head = INSERT(head, 8);
	head = INSERT(head, 9);
	head = INSERT(head, 15);
	head = INSERT(head, 12);

	do
	{
		printf("\nSelect an option\n1.Insert\n2.Find minimum\n3.Extract minimum\n4.Find Node\n5.Decrease key\n6.Delete\n7.Exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("\nEnter the key :: ");
				scanf("%d", &key);
				head = INSERT(head, key);
				break;
			case 2:
				temp = FIND_MIN(head);
				if(temp) printf("Minimum Key [ %d ]\n", temp->key);
				else printf("\n\tEmpty.\n");
				break;
			case 3:
				head = EXTRACT_MIN(head);
				break;
			case 4:
				printf("\nKey to find :: ");
				scanf("%d", &key);
				if( (temp = findNode(head, key)) )
					printf(" [ %d ] exists\n",temp->key);
				else
					printf("\n\tKey Doesn't exists.\n");
				break;
			case 5:
				printf("\nKey to decrease :: ");
				scanf("%d", &key);
				if( (temp = findNode(head, key)) )
				{
					//printf(" [ %d ] exists\n",temp->key);
					printf("[ %d ] Key to be decreased to >> ");
					scanf("%d", &key);
					DECREASE_KEY(temp, key);
				}
				else
					printf("\n\tKey Doesn't exists.\n");
				break;
			case 6:
				printf("\nKey to delete :: ");
				scanf("%d", &key);
				if( (temp = findNode(head, key)) )
				{
					head = DELETE(head, temp);
				}
				else
					printf("\n\tKey Doesn't exists.\n");
				break;
			case 7:
				break;
			default:
				printf("\tInvalid Choice.\n");
		}
	} while(choice != 7);

	return 0;
	
}
