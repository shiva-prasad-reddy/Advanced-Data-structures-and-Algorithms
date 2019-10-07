#include<stdio.h>
#include<stdlib.h>

struct node 
{

struct node *parent;
int data;
struct node *left, *right;

}*BST = NULL;


void insert(struct node *bst, int data)
{
	struct node *ptr = NULL, *temp = NULL;
	ptr = (struct node *)malloc(sizeof(struct node));
	ptr->data = data;
	ptr->left = ptr->right = NULL;
	if(bst != NULL)
	{
		while(bst)
		{
			temp = bst;
			if(data < bst->data)
				bst = bst->left;
			else
				bst = bst->right;
		}
		if(data < temp->data)
			temp->left = ptr;
		else
			temp->right = ptr;
		ptr->parent = temp;
	}
	else
	{
		ptr->parent = NULL;
		BST = ptr; 
	}

}

struct node *search(struct node *bst, int data)
{
	while(bst && bst->data != data)
	{
		if(data < bst->data)
			bst = bst->left;
		else
			bst = bst->right;
	}
	return bst;
}

struct node *predecessor(struct node *bst, int data)
{
	
	struct node *ptr = NULL, *pre = NULL;
	ptr = search(bst, data);
	if(!ptr) return NULL;
	if(ptr->left)
	{
		ptr = ptr->left;
		while(ptr->right != NULL) ptr = ptr->right;
		return ptr;
	}
	else
	{
		/*

		while(bst && bst != ptr) {
			if(ptr->data < bst->data) bst = bst->left;
			else
			{
				pre = bst;
				bst = bst->right;
			}
		}
		return pre;

		*/
		while(ptr && ptr->parent && ptr->parent->left == ptr) ptr = ptr->parent;
		return ptr->parent;
		
		

	}
	
}
struct node *successor(struct node *bst)
{
}


struct node *delete(struct node *bst, int data)
{
	struct node *ptr = NULL, *temp = NULL;
	ptr = search(bst, data);
	if(ptr)
	{
		if(!ptr->left && !ptr->right)
		{
			temp = ptr;
			if(bst != ptr)
				if(ptr->data < ptr->parent->data) ptr->parent->left = NULL;
				else ptr->parent->right = NULL;
			else
				bst = NULL;		
			free(temp);
			
		}
		if( (ptr->left && !ptr->right) || (!ptr->left && ptr->right) )
		{
			temp = ptr;

			if(bst == ptr)
			{
				if(ptr->right == NULL)
				{
					ptr->left->parent = NULL;
					bst = ptr->left;
					
				}
				else
				{
					ptr->right->parent = NULL;
					bst = ptr->right;
				}
			}
			else
			{
				if(ptr->right == NULL)
				{
					if(ptr->parent->data > data) ptr->parent->left = ptr->left; 
					else ptr->parent->right = ptr->left;
					ptr->left->parent = ptr->parent;
				}
				else
				{
					if(ptr->parent->data > data)ptr->parent->left = ptr->right;
					else ptr->parent->right = ptr->right;
					ptr->right->parent = ptr->parent;
				}
			}

			
			free(temp);
		}
		if(ptr->left && ptr->right)
		{
			struct node *pre = NULL;
			pre = predecessor(bst, data);
			data = pre->data;
			delete(bst, data);
			ptr->data = data; 
			
		}
	}
	else
		printf("\n\tData doesn't exists\n");

	return bst;
}


void inorder(struct node *bst)
{
	if(bst)
	{
		inorder(bst->left);
		printf("%d, ", bst->data);
		inorder(bst->right);
	}
}

int main()
{
	
	//insert(BST, 50);insert(BST, 40);insert(BST, 30);
	int choice, value;
	struct node *temp = NULL;
	do
	{
		printf("\n1.Insert\n2.Search\n3.Predecessor\n4.Delete\n5.Inorder\n6.Exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("\nValue to insert :: ");
				scanf("%d",&value);
				insert(BST, value);
				break;
			case 2:
				printf("\nValue to be searched :: ");
				scanf("%d",&value);
				temp = search(BST, value);
				if(temp) printf("\nItem exists\n");
				else printf("\nItem doesn't exist\n");
				break;
			case 3:
				printf("\nEnter value to find its predecessor :: ");
				scanf("%d",&value);
				temp = predecessor(BST, value);
				if(temp) printf("\nPredecessor of %d is %d\n",value,temp->data);
				else printf("\nPredecessor not found\n");
				break;
			case 4:
				printf("\nValue to delete :: ");
				scanf("%d",&value);
				BST = delete(BST, value);
				break;
			case 5:
				printf("\nInorder Traversal :: \n");
				inorder(BST);
				printf("\n");
				break;
			
				
		}
	} while(choice != 6);

	printf("\n\n");
	return 0;
	
}


