#include<stdio.h>
#include<stdlib.h>

struct node
{

	int height;
	int data;
	struct node *left, *right;

};

int max(int a, int b)
{
	if(a > b) return a;
	else return b;
}

int calculateHeight(struct node *left, struct node *right)
{
	int l, r;
	l = r = 0;
	if(left) l = left->height;
	if(right) r = right->height;
	return 1 + max(l, r);	
}

void LL(struct node **parent)
{
	//printf("\n\t Applying LL \n");
	struct node *temp = *parent;
	*parent = temp->left;
	temp->left = (*parent)->right;
	(*parent)->right = temp;

	//A height
	temp->height = calculateHeight(temp->left, temp->right);

}
void LR(struct node **parent)
{
	//printf("\n\t Applying LR \n");
	struct node *temp = *parent;
	*parent = (temp->left)->right;
	(temp->left)->right = (*parent)->left;
	(*parent)->left = temp->left;
	temp->left = (*parent)->right;
	(*parent)->right = temp;

	//A height
	temp->height = calculateHeight(temp->left, temp->right);
	//C height
	(*parent)->height = calculateHeight((*parent)->left, (*parent)->right);
}
void RR(struct node **parent)
{
	//printf("\n\t Applying RR \n");
	struct node *temp = *parent;
	*parent = temp->right;
	temp->right = (*parent)->left;
	(*parent)->left = temp;

	//A height
	temp->height = calculateHeight(temp->left, temp->right);

}
void RL(struct node **parent)
{
	//printf("\n\t Applying RR \n");
	struct node *temp = *parent;
	*parent = (temp->right)->left;
	(temp->right)->left = (*parent)->right;
	(*parent)->right = temp->right;
	temp->right = (*parent)->left;
	(*parent)->left = temp;

	//A height
	temp->height = calculateHeight(temp->left, temp->right);
	//C height
	(*parent)->height = calculateHeight((*parent)->left, (*parent)->right);

}


void insert(struct node **parent, int data)
{	
	struct node *temp = NULL;
	if(*parent == NULL)
	{
		temp = (struct node *)malloc(sizeof(struct node));
		temp->data = data;
		temp->height = 1;
		temp->left = temp->right = NULL;
		*parent = temp;
		  
	}
	else
	{
		if(data < (*parent)->data) insert(&((*parent)->left), data);
		else insert(&((*parent)->right), data);

		int l, r, bf;
		l = r = 0;
		if((*parent)->left) l = ((*parent)->left)->height;
		if((*parent)->right) r = ((*parent)->right)->height;
		(*parent)->height  = 1 + max(l, r);

		bf = l - r;
		if(  !(bf >= -1 && bf <= 1) )
			//rotations
			if(data < (*parent)->data)
				//L
				if(data < ((*parent)->left)->data ) LL(parent);
				else LR(parent);
			else
				//R
				if(data > ((*parent)->right)->data ) RR(parent);
				else RL(parent);		
	}
}


struct node **helper;
struct node *successor(struct node *root, struct node *ptr)
{
	//find successor of a node
	if(ptr == NULL) return NULL;
	if(ptr->right)
	{
		ptr = ptr->right;
		while(ptr->left != NULL) ptr = ptr->left;
		return ptr;
	}
	else
	{
		struct node *suc = NULL;
		while(root && root != ptr)
		{
			if(ptr->data < root->data) {
				suc = root;
				root = root->left;
			}
			else root = root->right;
		}
		return suc;

	}

}

int computeWeight(struct node *parent)
{
	if(parent->left)
	{
		if(parent->right)
			if(parent->left->height < parent->right->height) return 1;
		return 0;
	}
	else
		return 1;
}

void delete(struct node **parent, int data)
{
	if(*parent == NULL)
		return;
	if((*parent)->data == data)
	{
		struct node *temp;
		//leaf node
		if((*parent)->left == NULL && (*parent)->right == NULL)
		{
			temp = *parent;
			*parent = NULL; //node deleted
			free(temp);
		}
		//single child node
		else if(   ((*parent)->left == NULL && (*parent)->right) || ((*parent)->left && (*parent)->right== NULL)  )
		{
			temp = *parent;
			if((*parent)->left == NULL && (*parent)->right) *parent = (*parent)->right;
			if((*parent)->left && (*parent)->right== NULL) *parent = (*parent)->left;
			free(temp);
		}
		//node with two children
		else if((*parent)->left && (*parent)->right) //unnecessary statement
		{
			//find successor (leaf node)
			temp = successor(*helper, *parent);
			//copy data
			int copy = temp->data;
			//delete successor
			delete(parent, copy);
			//replace current node data with successor node data
			(*parent)->data = copy;
		}


		return;
	}
	if(data < (*parent)->data) delete(&((*parent)->left), data);
	else delete(&((*parent)->right), data);


		int l, r, bf;
		l = r = 0;
		if((*parent)->left) l = ((*parent)->left)->height;
		if((*parent)->right) r = ((*parent)->right)->height;
		(*parent)->height  = 1 + max(l, r);

		bf = l - r;
		if(  !(bf >= -1 && bf <= 1) )
		{
			if(!computeWeight(*parent)) {
				if(!computeWeight((*parent)->left)) LL(parent);
				else LR(parent);
			}
			else
			{
				if(!computeWeight((*parent)->right)) RL(parent);
				else RR(parent);
			}
		}



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

void inorder(struct node *tree)
{
	if(tree)
	{
		inorder(tree->left);
		printf("%d, ", tree->data);
		inorder(tree->right);
	}
}


int main()
{
	int choice, value;
	struct node *tree = NULL;
	helper = &tree;
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
				delete(&tree, value);
				break;
			case 3:
				//printf("\nLevel order Traversal :: \n");
				levelOrderTraversal(tree);
				printf("\n");
				break;
		
				
		}
	} while(choice != 4);
	return 0;
	
}
