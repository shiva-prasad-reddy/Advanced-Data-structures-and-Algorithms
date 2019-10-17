
void swap(int *array, int a, int b)
{
	int c = array[a];
	array[a] = array[b];
	array[b] = c;
}

void heapify(int *heap, int index, int len)
{
	int min = index, t;
	while( (t = (2*index)+1) < len)
	{
		if(heap[index] > heap[t])
			min = t;

		if(t+1 < len && heap[min] > heap[t+1])
			min = t+1;

		if(min == index) break;

		swap(heap, index, min);
		index = min;
	}
}


void BuildMinHeap(int *heap, int len)
{
	//not touching leaf nodes
	int internal_nodes = (len - 1) / 2;
	for(int i = (internal_nodes-1); i >= 0; i--)
		heapify(heap, i, len);
}
