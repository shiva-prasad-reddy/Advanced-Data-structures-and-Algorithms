#include<stdio.h>
#include"stdlib.h"

struct node
{
	int data;
	struct node *left, *right;
};

struct node *readTree(struct node *parent, char *side)
{
	int value;
	struct node *ptr = NULL;
	ptr = (struct node *)malloc(sizeof(struct node));
	
	if(parent == NULL)
		printf("\nEnter root node value :: ");
	else
		printf("\nEnter the node value of the %s side of node %d :: ", side, parent->data);

	scanf("%d",&value);
	ptr->data = value;

	printf("\nDoes node %d has left child :: ",ptr->data);
	scanf("%d",&value);
	if(value == 1)
		ptr->left = readTree(ptr, "left");
	else
		ptr->left = NULL;

	printf("\nDoes node %d has right child :: ",ptr->data);
	scanf("%d",&value);
	if(value == 1)
		ptr->right = readTree(ptr, "right");
	else
		ptr->right = NULL;

	return ptr;
}

void inorder(struct node *tree)
{
	if(tree)
	{
		inorder(tree->left);
		printf("%d, ",tree->data);
		inorder(tree->right);
	}
}
void preorder(struct node *tree)
{
	if(tree)
	{
		printf("%d, ",tree->data);
		preorder(tree->left);
		preorder(tree->right);
	}
}
void postorder(struct node *tree)
{
	if(tree)
	{
		postorder(tree->left);
		postorder(tree->right);
		printf("%d, ",tree->data);
	}
}

struct node *copyingTree(struct node *old)
{
	struct node *ptr = NULL;
	if(old != NULL)
	{
		ptr = (struct node *)malloc(sizeof(struct node));
		ptr->data = old->data;
		ptr->left = copyingTree(old->left);
		ptr->right = copyingTree(old->right);
	}
	return ptr;
}


int comparingTrees(struct node *tree1, struct node *tree2)
{
	if(tree1 != NULL && tree2 != NULL)
		return (tree1->data == tree2->data) && comparingTrees(tree1->left, tree2->left) && comparingTrees(tree1->right, tree2->right);
	else if(tree1 == tree2)
		return 1;
	else 
		return 0;

}

void traverse(struct node *tree)
{
	printf("\nPreorder Traversal\n");
	preorder(tree);
	printf("\nInorder Traversal\n");
	inorder(tree);
	printf("\nPostorder Traversal\n");
	postorder(tree);
	printf("\n\n");
}

int max(int a, int b)
{
	if(a > b)
		return a;
	else
		return b;
}

int height(struct node *tree)
{
	if(tree != NULL)
		return 1 + max(height(tree->left), height(tree->right));
	else
		return 0;
}

int count(struct node *tree)
{
	if(tree != NULL)
		return 1 + count(tree->left) + count(tree->right);
	else
		return 0;
}

int maxNodeInTree(struct node *tree)
{
	if(tree != NULL)
		return max(tree->data, max(maxNodeInTree(tree->left), maxNodeInTree(tree->right)));
	else
		return -1000;
}


struct node *mirrorImageOfTree(struct node *old)
{
	if(old != NULL)
	{
		struct node *temp = old->right;
		old->right = mirrorImageOfTree(old->left);
		old->left = mirrorImageOfTree(temp);
	}
	return old;
}

void levelOrderTraversal(struct node *tree)
{
	printf("\nLevel Order Traversal :: \n");
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
			printf("%d, ", temp->data);
			
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

int noOfNonLeafNodes(struct node *tree)
{
	if(tree == NULL)
		return 0;
	else if(tree->left == NULL && tree->right == NULL)
		return 0;
	else
		return 1 +  noOfNonLeafNodes(tree->left) + noOfNonLeafNodes(tree->right);
}

int main()
{

	struct node *tree1 = NULL, *tree2 = NULL;

	printf("\nBuilding Tree\n");
	tree1 = readTree(NULL,NULL);
	traverse(tree1);

	/*
	tree2 = copyingTree(tree1);
	traverse(tree2);
	
	printf("\nBuilding Tree\n");
	tree2 = readTree(NULL,NULL);
	if(comparingTrees(tree1,tree2))
		printf("Trees are same\n");
	else
		printf("Trees are different\n");
	*/


	printf("Height of Tree :: %d\n", height(tree1));
	printf("Maximum node in Tree :: %d\n", maxNodeInTree(tree1));
	printf("Number of nodes in Tree :: %d\n", count(tree1));
	printf("Number of non leaf nodes (or) Internal nodes :: %d\n", noOfNonLeafNodes(tree1));
	//tree1 = mirrorImageOfTree(tree1);
	//traverse(tree1);

	levelOrderTraversal(tree1);
	printf("\n\n");
	return 0;
}
