#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define TRUE 1
#define FALSE 0
#define DEGREE 2 // DEGREE
#define MIN_KEYS 1
#define MAX_KEYS 3

struct node
{
	int N;
	int leaf;
	int keys[DEGREE*2]; //KEYS = DEGREE*2 - 1 -- starts with 1
	struct node *(child[DEGREE * 2]); //DEGREE*2 -- starts with 0 and KEYS[1]->LEFT = child[0], KEYS[1]->RIGHT = ptrs[1]
};

struct node *newNode()
{
	return (struct node *)calloc(1, sizeof(struct node));
}

struct node *insert_into_full_node(struct node *, struct node *, int);

void insert_into_non_full_node(struct node *tree, int key)
{
	int i;
	if(tree->leaf == TRUE)
	{
		//shift elements and insert
		//printf("%d --->  Key Insertion happened\n", key);
		i = tree->N;
		while( (i >= 1) && (key < (tree->keys)[i]) )
		{
			(tree->keys)[i+1] = (tree->keys)[i];
			i--;
		}
		(tree->keys)[i+1] = key;
		tree->N = tree->N + 1;
		printf("[ key, position, NoOfKeys ] => [ %d, %d, %d ] Insertion happened\n", key, i+1, tree->N);
	}
	else
	{
		printf("Key Insertion into Internal node\n");
		i = tree->N;
		while( (i >= 1) && (key < (tree->keys)[i]) ) i--;
		//i satisfies every condition because we started child from index 0
		struct node *child = (tree->child)[i];
		//checking if child is full or not
		if(child->N == MAX_KEYS) //split is anticipated
			insert_into_full_node(tree, child, key);
		else
			insert_into_non_full_node(child, key);
	}

}


void shiftAndInsert(struct node *parent, struct node *newPointer, int key)
{

	//shift elements and insert
	printf("Shifting elements in parent node and inserting newnode [ %d ]\n", key);
	int i = parent->N;
	while( (i >= 1) && (key < (parent->keys)[i]) )
	{
			(parent->keys)[i+1] = (parent->keys)[i];
			(parent->child)[i+1] = (parent->child)[i];
			i--;
	}
	i++;
	//i=0 case would be satisfies beacuse y would point to it
	//newPointer should be inserted always on the right side of key
	(parent->keys)[i] = key;
	(parent->child)[i] = newPointer;
	parent->N = parent->N + 1;
}


struct node *insert_into_full_node(struct node *parent, struct node *fullNode, int key)
{
	//tree is passed whose child is full where we are trying to insert key
	printf("Anticipated Split.\n");
	struct node *new = NULL;
	new = newNode();
	
	int median = ceil(MAX_KEYS / (float)2);
	int i;
	printf("Anticipated Split at [ median ] => [ %d ].\n", median);
	i = median+1;
	while(i <= MAX_KEYS)
	{
		//copy keys and make them zero
		new->N = new->N + 1;
	 	(new->keys)[new->N] = (fullNode->keys)[i];
		(fullNode->keys)[i] = 0;
		//copy child pointers and make them NULL
		(new->child)[new->N - 1] = (fullNode->child)[i-1];
		(fullNode->child)[i-1] = NULL;

		i++;
		
	}
	(new->child)[new->N] = (fullNode->child)[i-1];	//copying last pointer and making it null
	(fullNode->child)[i-1] = NULL;
	
	//median value fullNode-keys[median] to be inserted into tree after position and the fullNode-keys[median] = 0
	fullNode->N = new->N = median - 1; //important
	new->leaf = fullNode->leaf; //important

	int nodeToBeInsetedIntoParent = (fullNode->keys)[median];
	(fullNode->keys)[median] = 0;

	//if parent is NULL 
	//root node is splitted 
	//new node should be created

	if(parent == NULL)
	{
		printf("Root Split happened.\n");
		
		parent = newNode();

		(parent->child)[0] = fullNode;
		(parent->keys)[1] = nodeToBeInsetedIntoParent;
		(parent->child)[1] = new;

		parent->leaf = FALSE; //important
		parent->N = 1;

	}
	else 
		shiftAndInsert(parent, new, nodeToBeInsetedIntoParent);

	if(key < nodeToBeInsetedIntoParent) //left
		insert_into_non_full_node(fullNode, key);
	else //right
		insert_into_non_full_node(new, key);


	//return parent is caught only when called from insert function otherwise ignore the return value
	return parent;

}


void insert(struct node **tree, int key)
{
	if(*tree == NULL)
	{
		*tree = newNode();
		(*tree)->leaf = TRUE;
		insert_into_non_full_node(*tree, key);
	}
	else
	{
		if((*tree)->N == MAX_KEYS)
			*tree = insert_into_full_node(NULL, *tree, key);
		else
			insert_into_non_full_node(*tree, key);
	}
}



void search(struct node *tree, int key)
{
	if(tree)
	{
		int i=1;
		while( i <= tree->N && key > (tree->keys)[i])
			i++;

		if(i <= tree->N && key == (tree->keys)[i]) //found
			printf("\n\tELement found.\n");
		else
		{
			if(tree->leaf == TRUE)//not found
				printf("\n\tElement not found.\n");
			else
				search((tree->child)[i-1], key);
		}

	}
	else
		printf("\n\tEmpty Tree.\n");
}




void case_1(struct node *tree, int key)
{
	//remove the element and shift keys
	int i=1;
	while( i <= tree->N && key > (tree->keys)[i]) i++;
	
	if(i <= tree->N && key == (tree->keys)[i])
	{
		printf("[ %d ] is removed.\n", key);
		//Deleting the key and shifting the remaining keys
		(tree->keys)[i] = 0;
		i++;
		while(i <= tree->N)
		{
			(tree->keys)[i-1] = (tree->keys)[i];
			(tree->keys)[i] = 0;
			i++;
		}
		tree->N = tree->N - 1;

	}
	else
		printf("\n\tElement doesn't exists.\n");
}



struct node *anticipatedMerge(struct node *predecessor, struct node *successor, int key)
{
	//pushing successor keys and pointers into predecessor
	//key is to inserted because if we merge predecessor and successor there would one pointer whose position is not known
	printf("Anticipated Merge [ %d ]\n", key);
	predecessor->N  = predecessor->N + 1;
	predecessor->keys[predecessor->N] = key;
	int i=1;
	while(i <= successor->N)
	{
		predecessor->child[predecessor->N] = successor->child[i-1];
		predecessor->N  = predecessor->N + 1;
		predecessor->keys[predecessor->N] = successor->keys[i];
		i++;
	}
	predecessor->child[predecessor->N] = successor->child[i-1];
	free(successor);

	return predecessor;

}


struct node *predecessor(struct node *tree, int nodePosition)
{
	struct node *pre = tree->child[nodePosition-1];

	if(pre->N <= MIN_KEYS) return NULL;

	while(pre->leaf == FALSE)
		pre = (pre->child)[pre->N]; //going to extreme right child to find predecessor
	
	if(pre->N > MIN_KEYS) return pre;
	else return NULL;
}


struct node *successor(struct node *tree, int position)
{
	struct node *succ = (tree->child)[position];

	if(succ->N <= MIN_KEYS) return NULL;

	while(succ->leaf == FALSE)
		succ = (succ->child)[0]; //going to extreme left child to find successor
	
	if(succ->N > MIN_KEYS) return succ;
	else return NULL;
}


struct node *case_2_c(struct node *tree, int position, int key)
{

	printf("CASE-2-C\n");
	
	struct node *temp = NULL;
	temp = anticipatedMerge((tree->child)[position-1], (tree->child)[position], key);

	//shift and delete the element in tree node because it is added to the predecessor node
	int i = position + 1;
	while(i <= tree->N)
	{
		tree->keys[i-1] = tree->keys[i];
		tree->child[i-1] = tree->child[i];
		i++;
	}

	tree->keys[i-1] = 0;
	tree->child[i-1] = NULL;
	tree->N = tree->N - 1;

	return temp;
	
}

//even if the element to be deleted doesn't exists we are modifying the BTree
//even search involves disk access.

struct node *case_3_a(struct node *tree, int childPosition) //shift a key from right sibling 
{
	printf("CASE-3-A\n");
	struct node *rightSibling = NULL;
	rightSibling = tree->child[childPosition+1];
					
	int key_to_parent = rightSibling->keys[1];
	struct node *child_to_sibling = rightSibling->child[0];

	int i = 1;
	while(i < rightSibling->N)
	{
		rightSibling->keys[i] = rightSibling->keys[i+1];
		rightSibling->child[i-1] = rightSibling->child[i];
		i++;
	}
	rightSibling->child[i-1] = rightSibling->child[i];
	
	rightSibling->keys[i] = 0;
	rightSibling->child[i] = NULL;
	rightSibling->N = rightSibling->N - 1;


	int parent_key_to_sibling = tree->keys[childPosition+1];
	tree->keys[childPosition+1] = key_to_parent;

	struct node *sibling = NULL;
	sibling = tree->child[childPosition];
	sibling->N = sibling->N + 1;
	sibling->keys[sibling->N] = parent_key_to_sibling;
	sibling->child[sibling->N] = child_to_sibling;

	return sibling;
}

struct node *case_3_b(struct node *tree, int childPosition) //shift a key from left sibling 
{
	printf("CASE-3-B\n");
	struct node *leftSibling = NULL;
	leftSibling = tree->child[childPosition-1];
					
	int key_to_parent = leftSibling->keys[leftSibling->N];
	struct node *child_to_sibling = leftSibling->child[leftSibling->N];

	leftSibling->keys[leftSibling->N] = 0;
	leftSibling->child[leftSibling->N] = NULL;

	leftSibling->N = leftSibling->N - 1;


	int parent_key_to_sibling = tree->keys[childPosition];
	tree->keys[childPosition] = key_to_parent;

	struct node *sibling = NULL;
	sibling = tree->child[childPosition];

	//shift elements
	int i = sibling->N;
	while(i >= 1)
	{
		sibling->keys[i+1] = sibling->keys[i];
		sibling->child[i+1] = sibling->child[i];
		i--;
	}
	sibling->child[1] = sibling->child[0];

	sibling->keys[1] = parent_key_to_sibling;
	sibling->child[0] = child_to_sibling;
	sibling->N = sibling->N + 1;

	return sibling;
}


struct node *case_3_c(struct node *tree, int childPosition)
{
	printf("CASE-3-C\n");
	struct node *temp = NULL;
	if(childPosition != tree->N)
	{
		//merge with right child
		temp = anticipatedMerge(tree->child[childPosition], tree->child[childPosition+1], tree->keys[childPosition+1]);
		int i = childPosition + 1; //pointing i to correct key and child pointer to be replaced				
		while(i < tree->N)
		{
			tree->keys[i] = tree->keys[i+1];
			tree->child[i] = tree->child[i+1];
			i++;
		}
		tree->keys[i] = 0;
		tree->child[i] = NULL;
		tree->N  = tree->N - 1;
	}
	else
	{
		//merge with left child
		temp = anticipatedMerge(tree->child[childPosition-1], tree->child[childPosition], tree->keys[childPosition]);
		tree->keys[childPosition] = 0;
		tree->child[childPosition] = NULL;
		tree->N = tree->N - 1;				
	}
	return temp;
}

void delete(struct node *tree, int key, int fromRoot)
{
	struct node *temp = NULL;
	if(tree->leaf == TRUE && (tree->N > MIN_KEYS || fromRoot) )
	{
		//node to be deleted is present in tree and node is external node
		case_1(tree, key);
		return;
	}

	if(tree->N > MIN_KEYS || fromRoot)
	{
		fromRoot = 0;
		int i=1;
		while( i <= tree->N && key > (tree->keys)[i]) i++;
		if(i <= tree->N && key == (tree->keys)[i])
		{
			//case 2 
			//node exists in current node and has keys > MIN_KEYS ( except for root ) so search for its predecessor/successor
			//delete that predecessor/successor (exists in external node) and copy that key back to this node

			//2-a predecessor if there are > MIN_KEYS
			//2-b successor if there are > MIN_KEYS
			//2-c MERGE both successor and predecessor and delete the element
			//case_2(tree, i, key);
			int pre_succ;
			if( (temp = predecessor(tree, i)) )	//case_2_a
			{
				pre_succ = temp->keys[temp->N];
				printf("[ %d ] is replaced by its predecessor [ %d ] and deleting [ %d ]\n", key, pre_succ, pre_succ);
				delete(tree->child[i-1], temp->keys[temp->N], fromRoot);
				tree->keys[i] = pre_succ;
			}
			else if( (temp = successor(tree, i)) ) //case_2_b
			{
				pre_succ = (temp->keys)[1];
				printf("[ %d ] is replaced by its successor [ %d ] and deleting [ %d ]\n", key, pre_succ, pre_succ);
				delete(tree->child[i], (temp->keys)[1], fromRoot);
				(tree->keys)[i] = pre_succ;
			}
			else 	//case_2_c
			{
				temp = case_2_c(tree, i, key);
				//the node to be deleted is added to its predecessor so to delete it call delete on merged node(predecessor node)
				delete(temp, key, fromRoot);
			}


		}
		else
		{
			if(((tree->child)[i-1])->N > MIN_KEYS) delete((tree->child)[i-1], key, fromRoot);
			else
			{
				//case 3
				//node doesn't exists in current node and the child which is to traversed has MIN_KEYS

				//3-a Borrow a key from right sibling by shifting cyclically if it has > MIN_KEYS
				//3-b Borrow a key from left sibling by shifting cyclically if it has > MIN_KEYS
				//3-c ATICIPATED MERGE :
					// 3-c-1 either merge with left/right sibling
					// 3-c-2 if left/right sibling is the extreme border node the merge with that extreme sibling node
				int childPosition = i-1; //make childPosition point to the exact child pointer
				
				if(childPosition != tree->N && (tree->child[childPosition+1])->N > MIN_KEYS)
				{
					//borrow from right sibling which has tolerance
					//if the node exists in extreme right most child it wont execute this block
					//cyclicaly shift on key and one child pointer
					temp = case_3_a(tree, childPosition);
				}
				else
				{
					//left sibling
					if(childPosition != 0 && (tree->child[childPosition-1])->N > MIN_KEYS)
						//borrow from left sibling which has tolerance
						//if the node exists in extreme left most child it wont execute this block
						//cyclicaly shift one key and one child point
						temp = case_3_b(tree, childPosition);
					else 
						temp = case_3_c(tree, childPosition);
				}	

				delete(temp, key, fromRoot);
			}
		}

	}
}



void delete_init(struct node **root, int key)
{
	if(*root)
	{
		struct node *temp = NULL, *tree = *root;
		if((*root)->N > MIN_KEYS) delete(*root, key, 0);
		else
		{
			if(tree->N > 1) delete(*root, key, 1);
			else
			{
				int i=1;
				while( i <= tree->N && key > (tree->keys)[i]) i++;
				if(i <= tree->N && key == (tree->keys)[i])
				{
					if(tree->leaf == TRUE)
					{
						free(tree);
						*root = NULL;
					}
					else
					{
						//case_2
						int pre_succ;
						if( (temp = predecessor(tree, i)) )	//case_2_a
						{
							pre_succ = temp->keys[temp->N];
							printf("[ %d ] is replaced by its predecessor [ %d ] and deleting [ %d ]\n", key, pre_succ, pre_succ);
							delete(tree->child[i-1], temp->keys[temp->N], 0);
							tree->keys[i] = pre_succ;
						}
						else if( (temp = successor(tree, i)) ) //case_2_b
						{
							pre_succ = (temp->keys)[1];
							printf("[ %d ] is replaced by its successor [ %d ] and deleting [ %d ]\n", key, pre_succ, pre_succ);
							delete(tree->child[i], (temp->keys)[1], 0);
							(tree->keys)[i] = pre_succ;
						}
						else 	//case_2_c
						{
							temp = case_2_c(tree, i, key);
							free(tree);
							*root = temp;
							//the node to be deleted is added to its predecessor so to delete it call delete on merged node(predecessor node)
							delete(temp, key, 0);
						}
					}
				}
				else
				{
					if(tree->leaf == TRUE)
					{
						printf("\n\tElement doesn't exists.\n");
					}
					else
					{
						//case_3
						if(((tree->child)[i-1])->N > MIN_KEYS) 
							delete((tree->child)[i-1], key, 0);
						else
						{
							int childPosition = i-1; //make childPosition point to the exact child pointer
				
							if(childPosition != tree->N && (tree->child[childPosition+1])->N > MIN_KEYS)
							{
								temp = case_3_a(tree, childPosition);
							}
							else
							{
								//left sibling
								if(childPosition != 0 && (tree->child[childPosition-1])->N > MIN_KEYS)
									temp = case_3_b(tree, childPosition);
								else 
								{
									temp = case_3_c(tree, childPosition);
									free(tree);
									*root = temp;
								}
							}	
							delete(temp, key, 0);
						}
					}
				}
			}
		}
	}
	else
		printf("\n\tTree is Empty.\n");
}

int main()
{
	struct node *BTree = NULL; //BTree ---> Balanced tree all leaves are at same level.
	int choice, key;
	/*
	insert(&BTree, 1);
	insert(&BTree, 5);
	insert(&BTree, 9);
	insert(&BTree, 10);
	insert(&BTree, 15);
	insert(&BTree, 16);
	insert(&BTree, 18);
	insert(&BTree, 7);
	insert(&BTree, 8);
	insert(&BTree, 4);
	insert(&BTree, 3);
	insert(&BTree, 0);
	insert(&BTree, 6);
	*/
	/*
	insert(&BTree, 5);
	insert(&BTree, 10);
	insert(&BTree, 15);
	insert(&BTree, 20);
	insert(&BTree, 25);
	insert(&BTree, 30);
	*/

	do
	{
		printf("\n1.Insert\n2.Delete\n3.Search\n4.Exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("\nKey to insert :: ");
				scanf("%d",&key);
				insert(&BTree, key);
				break;
			case 2:
				printf("\nKey to delete :: ");
				scanf("%d",&key);
				delete_init(&BTree, key);
				break;
			case 3:
				printf("\nKey to search :: ");
				scanf("%d",&key);
				search(BTree, key);
				break;		
		}
	} while(choice != 4);
	return 0;
	
}