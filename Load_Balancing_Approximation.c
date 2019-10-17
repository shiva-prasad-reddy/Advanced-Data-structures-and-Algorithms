#include<stdio.h>
#include<stdlib.h>

struct Machine
{
	int machine_id;
	int load_assined;
};

struct Job
{
	int job_id;
	int load;
};

//******************************** MERGE SORT ****************************

void merge(struct Job *array, int start, int end)
{
	struct Job *aux = (struct Job *)malloc( (end - start) * sizeof(struct Job) );
	int i, j, mid, count = 0;
	
	i = start;
	mid = (start + end) / 2;
	j = mid;

	while(i < mid && j < end)
	{
		if(array[i].load > array[j].load)
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


void MergeSort(struct Job *array, int start, int end)
{
	if(start+1 < end)
	{
		int mid = (start + end) / 2;
		MergeSort(array, start, mid);
		MergeSort(array, mid, end);
		merge(array, start, end);
	}
}


//************************************************************************

//************************* MIN HEAP *************************************
void swap(struct Machine *heap, int index, int min)
{
	struct Machine temp = heap[index];
	heap[index] = heap[min];
	heap[min] = temp;
}

void heapify(struct Machine *heap, int index, int len)
{
	int min = index, t;
	while( (t = (2*index)+1) < len)
	{
		if(heap[index].load_assined > heap[t].load_assined)
			min = t;

		if(t+1 < len && heap[min].load_assined > heap[t+1].load_assined)
			min = t+1;

		if(min == index) break;

		swap(heap, index, min);
		index = min;
	}
}

struct Machine ExtractMin_Insert(struct Machine *heap, int job_load, int M)
{
	heap[0].load_assined += job_load;
	struct Machine temp = heap[0];
	heapify(heap, 0, M);
	return temp;
}
//*******************************************************************


int main()
{
	struct Job jobs[] = {{1, 3}, {2, 3}, {3, 2}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 15}};	
	struct Machine machine_heap[] = {{1,0}, {2, 0}, {3, 0}, {4, 0}};

	int N = sizeof(jobs)/sizeof(struct Job); //total no. of jobs;
	int M = sizeof(machine_heap)/sizeof(struct Machine); //total no. of machines;

	MergeSort(jobs, 0, N);

	struct Machine temp;
	for(int i = 0; i < N; i++)
	{
		temp = ExtractMin_Insert(machine_heap, jobs[i].load, M);
		printf("Job -- %d(load = %d) is assigned to Machine - %d(load assined = %d)\n", jobs[i].job_id, jobs[i].load, temp.machine_id, temp.load_assined);
	}


}