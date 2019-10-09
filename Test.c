#include<stdio.h>
#include<stdlib.h>




// <stdio.h> predefined header file starts search from header files located directory
// "stdio.h" user-defined header file starts search from current directory



struct node;

struct node
{
	int a;
	int b;
};

void main()
{
	/*
	int i = 9, j = 10;
	int *p, *c;

	p = &i;
	c = &j;

	p = c;
	printf("%d\n", *p);

	printf("%d\n", i);
	*/


	struct node *a = malloc(sizeof(struct node));



	struct node *b = malloc(sizeof(struct node));
/*

	printf("%p\n", a);
	printf("%p\n", b);

	

	b = a;


	printf("%p\n", a);
	printf("%p\n", b);
*/





	a->a = 20;
	printf("---------------------\n");


	printf("%p\n", a);
	printf("%p\n", b);

	

	*b = *a;


	printf("%p\n", a);
	printf("%p\n", b);
	a->a = 100;  //b = a would reflect the change and creates a memory lekage problem
	printf("%d %d\n", b->a, b->b);

	
	struct node *(arr[10]);
	arr[1] = b;
	printf("Success array of pointers %d\n",arr[1]->a);
	struct node *array[10];
	array[1] = b;
	printf("Success array of pointers %d\n",array[1]->a);

//	struct node (*aarr)[10]; //ERROR DECLARATION struct node *arr;	
	//struct node aarr[10];
	//*(&aarr[1]) = *b; //########### for struct node aarr[10];
	
	//aarr[0]->a = 111;
	//printf("Success array of nodes %d\n",arr[0]->a);

	int (*A)[10]; ///  pointer which contains pointer to an array of 10 integers

	int x[] = {1,2,3};
	(*A)[1] = 2;

	int i;
	for(i=0; i<10; i++) (*A)[i] = i * i;

	for(i=0; i<10; i++) printf("Success array of nodes %d\n",(*A)[i]);



		/*

	int (*A)[10]; /// pointer which contains pointer to an array of 10 integers

int x[] = {1,2,3};

	int *pointer;
	pointer = x;

	//access 
	(*pointer)[index]


		*/

}