#include<stdio.h>


void merge(int *array, int start, int mid, int end)
{

	

	int aux[20];
	int i, j;
	i = start;
	j = mid+1;
	int count = 0;
	while(i <= mid && j <= end)
	{
		if(array[i] > array[j])
		{
			aux[count++] = array[j];
			j++;
		}
		else
		{
			aux[count++] = array[i];
			i++;
		}
	}

	while(i <= mid) aux[count++] = array[i++];
	while(j <= end) aux[count++] = array[j++];
	i = 0;
	for(; start <= end; start++)
	{
		array[start] = aux[i++];
	}


}


void mergesort(int *array, int start, int end)
{
	if(start < end)
	{
		int mid = (start + end) / 2;
		mergesort(array, start, mid);
		mergesort(array, mid+1, end);

		merge(array, start, mid, end);

	}
}

int main()
{

	int i,n;
	printf("\nEnter the size :: ");
	scanf("%d",&n);
	int array[n];
	printf("\nEnter the elements\n");
	for(i = 0; i < n; i++) scanf("%d",array+i);


		mergesort(array, 0, n);

	printf("\nSorted Array :: \n");
	for(i = 0; i < n; i++) printf("%d,\t",array[i]);
	printf("\n");
	return 0;
}