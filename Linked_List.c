//Write a modular program in c for following operations to create a list till -1 is not input
//traverse the list
//find maximum value in the list
//reverse the list using recursiveReverse and without recursiveReverse

#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *link;
}*start = NULL;

struct node *createNode(int value)
{
	struct node *ptr = NULL;
	ptr = (struct node *)malloc(sizeof(struct node));
	ptr->data = value;
	ptr->link = NULL;
	return ptr;
}

struct node *createList()
{
	int input;
	struct node *ptr = NULL, *start = NULL, *last = NULL;
	while(1)
	{
		printf("\nEnter the next value for linked list :: ");
		scanf("%d",&input);
		if(input == -1)
			break;
        ptr = createNode(input);
        if(start == NULL)
        {
                start = ptr;
                last = ptr;
        }
        else
        {
                last->link = ptr;
                last = ptr;
        }

	}
	return start;
}

void traverse(struct node *list)
{
    printf("\nNodes in list are :: ");
    while(list != NULL)
    {
        printf("%d, ", list->data);
        list = list->link;
    }
}

int maximum(struct node *list)
{

    int high = -1000;
    while(list != NULL)
    {
        if(list->data > high)
            high = list->data;

        list = list->link;
    }
    return high;
}

void recursiveReversal(struct node *previous, struct node *current)
{
  if(current != NULL)
  {
    recursiveReversal(current, current->link);
    current->link = previous;
  }
  else
  {
    start = previous;
  }
}

struct node *iterativeReversal(struct node *temp)
{
  struct node *left = NULL, *right = NULL;
  while(temp!= NULL)
  {
    right = temp->link;
    temp->link = left;
    left = temp;
    temp = right;
  }
  return left;
}

struct node *insertAtPosition(struct node *start, int value, int position)
{
	struct node *ptr = NULL, *temp = NULL;
	int i;
	if(position == 1)
	{
		ptr = createNode(value);
		ptr->link = start;
		start = ptr;
	}
	else
	{
		position = position - 1;
		temp = start;
		for(i=1; i<position && temp != NULL; i++)
			temp = temp->link;
		if(i == position && temp != NULL)
		{
			ptr = createNode(value);
			ptr->link = temp->link;
			temp->link = ptr;
		}
		else
			printf("\n\tInvalid Position\n");
	}
	return start;
}

struct node *deleteAtPosition(struct node *start, int position)
{
	struct node *temp = NULL, *ptr = NULL;
	int i;
	if(start == NULL)
	{
		printf("\n\tNo Items to delete\n");
	}
	else if(position == 1)
	{
		temp = start;
		start = start->link;
		free(temp);
	}
	else
	{
		position = position - 1;
		temp = start;
		for(i=1; i<position && temp->link != NULL; i++)
			temp = temp->link;
		if(i == position && temp->link != NULL)
		{
			ptr = temp->link;
			temp->link = ptr->link;
			free(ptr);
		}
		else
			printf("\n\tInvalid Position\n");
	}
	return start;
}

int main()
{
    start = createList();
    traverse(start);
    printf("\nMaximum value in linked list is :: %d\n", maximum(start));
    //recursiveReversal(NULL, start);
    //start = iterativeReversal(start);
    //traverse(start);

    int value, position = 0;
    while(position != -1) {
    	//printf("\nValue :: ");
    	//scanf("%d",&value);
    	printf("\nPosition :: ");
    	scanf("%d",&position);
    	//start = insertAtPosition(start,value,position);
    	start = deleteAtPosition(start,position);
    	traverse(start);
    }

    printf("\n\n");
    return 0;
}