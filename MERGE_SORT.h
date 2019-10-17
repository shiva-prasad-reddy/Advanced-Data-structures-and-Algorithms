void merge(int *array, int start, int end)
{
	int *aux = (int *)malloc( (end - start) * sizeof(int) );
	int i, j, mid, count = 0;
	
	i = start;
	mid = (start + end) / 2;
	j = mid;

	while(i < mid && j < end)
	{
		if(array[i] < array[j])
		{
			aux[count++] = array[i];
			i++;
		}
		else
		{
			aux[count++] = array[j];
			j++;
		}
	}

	while(i < mid) aux[count++] = array[i++];
	while(j < end) aux[count++] = array[j++];
	
	for(i = 0; start < end; start++)
		array[start] = aux[i++];

	free(aux);
}


void MergeSort(int *array, int start, int end)
{
	if(start+1 < end)
	{
		int mid = (start + end) / 2;
		MergeSort(array, start, mid);
		MergeSort(array, mid, end);
		merge(array, start, end);
	}
}
