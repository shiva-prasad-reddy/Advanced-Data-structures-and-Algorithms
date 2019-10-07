#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int a;
	int b;
}node;

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


	node *a = malloc(sizeof(node));



	node *b = malloc(sizeof(node));
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



}