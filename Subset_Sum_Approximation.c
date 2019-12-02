#include<stdio.h>
#include<stdlib.h>
#define NO_OF_ELEMENTS 5

struct node 
{
	int data;
	int setSize;
	struct node *next;
};

struct node *newNode(int data, int setSize)
{
	struct node *temp = NULL;
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = data;
	temp->setSize = setSize;
	temp->next = NULL;
	return temp;
}

struct node *addNode(struct node *list, int nodeData, int setSize)
{
	if(list)
	{
		struct node *head = NULL;
		head = list;
		while(list->next != NULL)
		{
			list = list->next;
		}
		list->next = newNode(nodeData, setSize);
		return head;
	}
	else
	{
		return newNode(nodeData, setSize);
	}
}

struct node *merge(struct node *one, struct node *two, int T)
{
	if(!one) return two;
	if(!two) return one;

	struct node *head = NULL, *last = NULL, *temp = NULL;
	//ordered merged list to be returned
	while(one && two)
	{
		//if(one->data > T || two->data > T) break;

		if(one->data < two->data)
		{
			if(last == NULL) head = one;
			else last->next = one;

			last = one;
			one = one->next;
		}
		else
		{
			if(last == NULL) head = two;
			else last->next = two;

			last = two;
			two = two->next;
		}
		
		if(one && one->data == last->data)
		{
			temp = one;
			one = one->next;
			free(temp);
		}
	}
	/*
	while(one && one->data < T)
	{
		last->next = one;
		last = one;
		one = one->next;
	}
	while(two && two->data < T)
	{
		last->next = two;
		last = two;
		two = two->next;
	}
	*/
	if(one) last->next = one;
	if(two) last->next = two;
	//last->next = NULL;

	return head;
}

//no ordering needed here
struct node *createListByAddingElement(struct node *list, int element, int T)
{
	struct node *newList = NULL;
	while(list != NULL)
	{	
		if( !((list->data + element) > T) )
		{
			newList = addNode(newList, list->data + element, list->setSize + 1);
		}
		list = list->next;
	}
	return newList;
}

struct node *TRIM(struct node *list, float delta)
{
	struct node *head = NULL, *last = NULL, *temp = NULL;
	//add first node
	head = last = list;
	list = list->next;

	while(list != NULL)
	{
		if(list->data > (last->data * (1 + delta)))
		{
			last->next = list;
			last = list;
			list = list->next;
		}
		else
		{
			temp = list;
			list = list->next;
			free(temp);
		}
	}
	last->next = NULL;
	return head;
}

struct node *findSumSet(struct node *sumList, int *U, int size, float delta, int T)
{	
	int element = 0;
	struct node *newList = NULL;
	for(int i = 0; i < size; i++)
	{
		element = U[i];
		newList = NULL;
		newList = createListByAddingElement(sumList, element, T);
		sumList = merge(sumList, newList, T); //remove duplicates and order the elements
		sumList = TRIM(sumList, delta);

	}
	return sumList;
}

int main()
{
	int U[] = {1, 4, 5, 8, 11};
	int e = 0.40;
	int n = 5;
	int delta = e / (2 * n);
	struct node *set = findSumSet(newNode(0, 0), U, 5, delta, 20);
	printf("Elements in SumSet >>> \n");
	while(set)
	{
		printf("sum = [ %d ]\tSet Size = [ %d ]\n", set->data, set->setSize);
		set = set->next;
	}
	return 0;
}
