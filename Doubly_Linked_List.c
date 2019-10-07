#include<stdio.h>
#include"stdlib.h"

struct node
{
	int data;
	struct node *prev, *next;
}*start = NULL;

struct node *createNode(int value)
{
	struct node *ptr = NULL;
	ptr = (struct node *)malloc(sizeof(struct node));
	ptr->data = value;
	ptr->prev = ptr->next = NULL;
	return ptr;
}

struct node *createList()
{
	int input;
	struct node *ptr = NULL, *start = NULL, *last = NULL;
	while(1)
	{
		printf("\nEnter the next value for Doubly linked list :: ");
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
                last->next = ptr;
                ptr->prev = last;
                last = ptr;
        }

	}
	return start;
}

void traverseForward(struct node *list)
{
    if(list != NULL)
    {
    	printf("%d, ", list->data);
    	traverseForward(list->next);
    }
}

void traverseBackward(struct node *list)
{
    if(list != NULL)
    {
    	while(list->next != NULL) list = list->next;
    	while(list != NULL)
    	{
    		printf("%d, ", list->data);
    		list = list->prev;
    	}
    }
}

void recursiveReversal(struct node *previous, struct node *current)
{
  if(current)
  {
    recursiveReversal(current, current->next);
    current->next = previous;
    if(previous)
    	previous->prev = current;
  }
  else
  {
    start = previous;
    if(start)
    	start->prev = NULL;
  }
}

struct node *iterativeReversal(struct node *temp)
{
  struct node *left = NULL, *right = NULL;
  while(temp)
  {
    right = temp->next;
    temp->next = left;
    temp->prev = right;
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
		ptr->next = start;
		if(start)
			start->prev = ptr;
		start = ptr;
	}
	else
	{
		position = position - 1;
		temp = start;
		for(i=1; i<position && temp != NULL; i++)
			temp = temp->next;
		if(i == position && temp != NULL)
		{
			ptr = createNode(value);
			ptr->next = temp->next;
			temp->next = ptr;
			ptr->prev = temp;
			if(ptr->next)
				ptr->next->prev = ptr;
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
		start = start->next;
		if(start)
			start->prev = NULL;
		free(temp);
	}
	else
	{
		position = position - 1;
		temp = start;
		for(i=1; i<position && temp->next != NULL; i++)
			temp = temp->next;
		if(i == position && temp->next != NULL)
		{
			ptr = temp->next;
			temp->next = ptr->next;
			if(ptr->next)
				ptr->next->prev = temp;
			free(ptr);
		}
		else
			printf("\n\tInvalid Position\n");
	}
	return start;
}

void reversalUsingDataExchange(struct node *list)
{
	struct node *head = NULL;
	int val;
	head = list;
	if(list != NULL)
    {
    	while(list->next != NULL) list = list->next;
    	while(head != list && list->next != head)
    	{
    		val = head->data;
    		head->data = list->data;
    		list->data = val;
    		head = head->next;
    		list = list->prev;
    	}
    }
}

void traverse(struct node *start)
{
	printf("\nForward traversal :: ");
	traverseForward(start);
	printf("\nBackward traversal :: ");
	traverseBackward(start);
}

int main()
{
	start = createList();
	int value, position = 0, choice;

	do
	{
		printf("\n\n1.Reversal using data exchange\n2.Recursive reversal\n3.Iterative reversal\n4.Insert at position\n5.Delete at position\n6.Traverse list\n7.Exit\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				reversalUsingDataExchange(start);
				break;
			case 2:
				recursiveReversal(NULL, start);
				break;
			case 3:
				start = iterativeReversal(start);
				break;
			case 4:
    	        		printf("\nValue :: ");
    	        		scanf("%d",&value);
    	        		printf("\nPosition :: ");
    	        		scanf("%d",&position);
    	        		start = insertAtPosition(start,value,position);
    	        		break;
            		case 5:
            			printf("\nPosition :: ");
    	        		scanf("%d",&position);
    	        		start = deleteAtPosition(start,position);
    	        		break;
    	    		case 6:
    	        		traverse(start);
    	        		break;
        	}
	} while(choice != 7);
	printf("\n\n");
	return 0;
	
}
