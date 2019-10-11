#include<stdio.h>
#include<stdlib.h>

//Polynomial time solution approach for Rod Cut problem


void rod_cut(int *price_map, int rod_length)
{

	int temp, *val, *set;
	val = (int *)malloc((rod_length + 1) * sizeof(int)); //Memoization 
	set = (int *)malloc((rod_length + 1) * sizeof(int)); //to track what rod_length included when a max is found

	for(int i = 1; i <= rod_length; i++)
	{
		val[i] = price_map[i];
		set[i] = i;
		for(int j = 1; j < i; j++)
		{
			temp = price_map[j] + val[i-j];
			if(temp > val[i])
			{
				val[i] = temp;
				set[i] = j;
			}
		}
	}

	

	printf("Price Map\n");
	for(int i = 1; i <= rod_length; i++) printf("[ %d --- %d ]\n", i, price_map[i]);

	printf("Max Profit Can be [ %d ] by including rods of length\n", val[rod_length]);
	int x = rod_length;
	do
	{
		printf("[ %d ]\n", set[x]);
		x = x - set[x];
	} while(x != 0);

	free(val);
	free(set);
}


int main()
{

	int price_map[] = {0,1,5,8,9,10,17,17,20};
	rod_cut(price_map, 8);

	return 0;
}