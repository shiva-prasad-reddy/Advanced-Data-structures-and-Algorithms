#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int build(int *arr, int *tree, int start, int end, int i)
{
	if(start == end)
	{
		tree[i] = arr[start];
		return tree[i];
	}
	else
	{
		int mid = (start + end) / 2;
		tree[i] =  build(arr, tree, start, mid, 2*i) + build(arr, tree, mid+1, end, (2*i) + 1);
		return tree[i];
	}

}

void update(int *arr, int *tree, int start, int end, int i, int index, int valuetoAdd)
{
	if(index < start || index > end) printf("\n\tIndex not in bounds\n");
	else if(start == end && start == index)
	{
		//update
		arr[index] += valuetoAdd;
		tree[i] += valuetoAdd;
	}
	else
	{
		int mid = (start + end) / 2;
		if(index <= mid) //left
			update(arr, tree, start, mid, 2*i, index, valuetoAdd);
		else //right
			update(arr, tree, mid+1, end, 2*i + 1, index, valuetoAdd);
		tree[i] += valuetoAdd;
	}
}


int findSum(int ds, int de, int *tree, int start, int end, int i)
{
	//printf("[%d, %d]\n", ds, de);
	if(ds < start || de > end) return 0;
	else if(ds == start && de == end) return tree[i];
	else
	{
		int mid = (start + end) / 2;
		
		if(de <= mid) //sum is on left side
		{
			return  findSum(ds, de, tree, start, mid, 2*i);
			
		} 
		else if(ds > mid) //sum is on right side
		{
			return findSum(ds, de, tree, mid+1, end, 2*i + 1);
			
		}
		else if(ds >= start && de <= end)
		{
			//sum is in middle somewhere
			return findSum(ds, mid, tree, start, mid, 2*i) + findSum(mid+1, de, tree, mid+1, end, 2*i + 1);
			
		}

	}
}


int main()
{

	int i, n, *arr = NULL, *tree = NULL;

	//no of array elements 
	printf("\nNo. of elements :: ");
	scanf("%d",&n);

 	//starts from 1 so take one node extra in array and in tree
 	//create a full binary tree

	int height = (int)ceil(log(2*n)/log(2));
	printf("height --> %d\n", height);
	int nodes = pow(2, height) ; //2**H - 1

	printf("nodes --> %d\n", nodes);

	arr = (int *)calloc(n+1, sizeof(int)); 
	tree = (int *)calloc(nodes, sizeof(int)); //n+n-1+1


	
	printf("\nEnter array elements\n");
	for(i=1; i<n+1; i++) scanf("%d",arr+i);


	printf("\nBuilding the tree\n");
	build(arr, tree, 1, n, 1);
	
	printf("\nArray elements\n");
	for(i=1; i<nodes; i++) printf("[ %d --> %d ]\n ", i, tree[i]);


	int index, valuetoAdd, ds, de;
	do
	{
		printf("\nChoose an option :: \n1.Update\n2.Find Sum\n3.Exit\n");
		scanf("%d",&i);
		switch(i)
		{
			case 1:
				
				printf("\nEnter index :: ");
				scanf("%d",&index);
				printf("Value to add :: ");
				scanf("%d",&valuetoAdd);
				update(arr, tree, 1, n, 1, index, valuetoAdd);
				break;
			case 2:
				
				printf("\nEnter desired start :: ");
				scanf("%d",&ds);
				printf("Enter desired end :: ");
				scanf("%d",&de);
				ds = findSum(ds, de, tree, 1, n, 1);
				if(ds != -1000) printf("sum -->  %d\n", ds);
				else printf("\n\tInvalid input range\n");
				break;
			case 3:
				break;
			default:
				printf("\n\tInvalid Choice\n");
		}
	} while(i != 3);

	
	//printf("\nArray elements\n");
	//for(i=1; i<nodes; i++) printf("[ %d --> %d ] , ", i, tree[i]);
	
	printf("\n\n");
	return 0;
	
}
