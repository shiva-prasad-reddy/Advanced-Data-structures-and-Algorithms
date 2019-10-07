#include<stdio.h>
#include<stdlib.h>

#define RED 1
#define BLACK 0

struct node {

	struct node *parent;
	int data;
	int color;
	struct node *left, *right;

};




void LLB(struct node **parent)
{
	struct node *temp = *parent;

	*parent = temp->left;
	(*parent)->parent = temp->parent;

	temp->left = (*parent)->right;
	if((*parent)->right) (*parent)->right->parent = temp;

	(*parent)->right = temp;
	temp->parent = *parent;

	(*parent)->color = BLACK;
	(*parent)->right->color = RED;
}

void LRB(struct node **parent)
{
	struct node *temp = *parent;

	*parent = (temp->left)->right;
	(*parent)->parent = temp->parent;

	(temp->left)->right = (*parent)->left;
	if((*parent)->left) (*parent)->left->parent = temp->left;


	(*parent)->left = temp->left;
	temp->left->parent = *parent;

	temp->left = (*parent)->right;
	if((*parent)->right) (*parent)->right->parent = temp;

	(*parent)->right = temp;
	temp->parent = *parent;

	(*parent)->color = BLACK;
	(*parent)->right->color = RED;
}

void RRB(struct node **parent)
{
	struct node *temp = *parent;

	*parent = temp->right;
	(*parent)->parent = temp->parent;

	temp->right = (*parent)->left;
	if((*parent)->left) (*parent)->left->parent = temp;

	(*parent)->left = temp;
	temp->parent = *parent;

	(*parent)->color = BLACK;
	(*parent)->left->color = RED;
}

void RLB(struct node **parent)
{
	struct node *temp = *parent;

	*parent = (temp->right)->left;
	(*parent)->parent = temp->parent;

	(temp->right)->left = (*parent)->right;
	if((*parent)->right) (*parent)->right->parent = temp->right;

	(*parent)->right = temp->right;
	temp->right->parent = *parent;

	temp->right = (*parent)->left;
	if((*parent)->left) (*parent)->left->parent = temp;

	(*parent)->left = temp;
	temp->parent = *parent;

	(*parent)->color = BLACK;
	(*parent)->left->color = RED;
}


void LLR__LRR__RRR__RLR(struct node *pu, struct node *gu, struct node *gu_l_r)
{
	pu->color = BLACK;
	if(gu->parent)	//if root node leave it as black
		gu->color = RED;
	gu_l_r->color = BLACK;
}


void balanceRBTree(struct node *u, struct node **parent)
{
	int flag = 0;
	struct node *pu = u->parent;
	struct node *gu = pu->parent;
	if(pu == gu->left) //L
	{
		//check gu right
		if(gu->right == NULL || gu->right->color == BLACK) //rotations
		{
			//LLB
			//LRB
			struct node **temp;
			if(gu->parent == NULL) temp = parent;
			else temp = gu->parent->left == gu ? &(gu->parent->left) : &(gu->parent->right);

			if(pu->left == u) LLB(temp);
			else LRB(temp);
			
		}
		else	// color change
		{
			//LLR
			//LRR
			flag = 1;
			LLR__LRR__RRR__RLR(pu, gu, gu->right);
		}

	}
	else	//R
	{
		//check gu left
		if(gu->left == NULL || gu->left->color == BLACK) //rotations
		{
			//RRB
			//RLB
			struct node **temp;
			if(gu->parent == NULL) temp = parent;
			else temp = gu->parent->left == gu ? &(gu->parent->left) : &(gu->parent->right);

			if(pu->right == u) RRB(temp);
			else RLB(temp);
		}
		else	// color change
		{
			//RRR
			//RLR
			flag = 1;
			LLR__LRR__RRR__RLR(pu, gu, gu->left);
		}
	}

	//further bubbling up the issue
	if(flag)
	{
		if(gu->color == RED && gu->parent->color == RED)
			balanceRBTree(gu, parent);
	}
}


struct node *newNode(int data, struct node *parent, int color) 
{

	struct node *ptr = NULL;
	ptr = (struct node *)malloc(sizeof(struct node));
	ptr->parent = parent;
	ptr->data = data;
	ptr->color = color;
	ptr->left = ptr->right = NULL;
	return ptr;
}

void insert(struct node **parent, int data)
{

	if(*parent == NULL)
	{
		*parent = newNode(data, NULL, BLACK);
		return;
	}

	struct node *temp, *ptr, *tree;
	temp = ptr = NULL;
	tree = *parent;
	while(tree)
	{
		temp = tree;
		if(data < tree->data) tree = tree->left;
		else tree = tree->right;
	}

	ptr = newNode(data, temp, RED);

	if(data < temp->data) temp->left = ptr;
	else temp->right = ptr;

	if(ptr->parent->color == RED) balanceRBTree(ptr, parent);

}


void delete(struct node **parent, int data)
{
	if(*parent == NULL)
		return;
	if((*parent)->data = data)
	{
		struct node *temp = NULL;
		if((*parent)->left == NULL && (*parent)->right == NULL)
		{
			//leaf node
			if((*parent)->color == RED)
			{
				temp = *parent;
				parent = NULL;
				free(temp);
			}
			else
			{
				
			}
		}
	}
}



void levelOrderTraversal(struct node *tree)
{

	printf("\nLevel Order Traversal :: \n");
	if(tree == NULL) return;
	
	struct node *(queue[20]);
	int front, rear;
	front = rear = -1;

	struct node *dummy = NULL;
	dummy = (struct node *)malloc(sizeof(struct node));
	dummy->data = -1000;
	dummy->left = NULL;
	dummy->right = NULL;

	queue[++rear] = tree;
	queue[++rear] = dummy;

	struct node *temp = NULL;

	while((front+1) != rear)
	{
		temp = queue[++front];
		if(temp->data != -1000)
		{
			printf("%d[%s],", temp->data, temp->color == RED ? "RED" : "BLACK");
			
			if(temp->left)
				queue[++rear] = temp->left;

			if(temp->right)
				queue[++rear] = temp->right;
		}
		else
		{
			queue[++rear] = dummy;
			printf("\n");
		}
	}


}



int main() 
{
	int choice, value;
	struct node *tree = NULL;
	
	do
	{
		printf("\n1.Insert\n2.Delete\n3.Level order\n4.Exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("\nValue to insert :: ");
				scanf("%d",&value);
				insert(&tree, value);
				break;
			
			case 2:
				printf("\nValue to delete :: ");
				scanf("%d",&value);
				//delete(&tree, value);
				break;
			case 3:
				levelOrderTraversal(tree);
				printf("\n");
				break;
		
				
		}
	} while(choice != 4);
	return 0;
	
}
