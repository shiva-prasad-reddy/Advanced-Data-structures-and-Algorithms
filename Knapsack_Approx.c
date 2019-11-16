#include<stdio.h>
#include<math.h>

#define ITEMS 4

int sum(int *array)
{
	int sum = 0;
	for(int i = 0; i < ITEMS; i++) sum += array[i];
	return sum;
}

int minimum(int a, int b)
{
	if(a < b)
		return a;
	return b;
}

float max(float *profits)
{
	int max = 0;
	for(int i = 1; i < ITEMS; i++)
		if(profits[i] > profits[max]) max = i;
	return profits[max];
}

float rounding_and_scaling(float *profits, float e)
{
	//OPT is replaced by LB which is max(profits)
	float LB = max(profits);

	float mul = (e/ITEMS)*LB;

	float temp;
	//rounding to each profit(xi) to the next larger multiple of (ε/n)·opt.
	for(int i = 0; i < ITEMS; i++)
	{
		temp = fmodf(profits[i], mul);
		if(temp != 0)
		{
			profits[i] = profits[i] + temp;
		}
	}

	//scaling
	for(int i = 0; i < ITEMS; i++)
	{
		profits[i] = profits[i] / mul;
	}

	return mul;

}


void MaXProfit(int *profits, int *weights)
{
	int max_profit = sum(profits);
	max_profit = max_profit + 1;
	int A[ITEMS][max_profit];

	for(int p = 0; p < max_profit; p++)
	{
		for(int i = 0; i < ITEMS; i++)
		{
			if(p == 0) A[i][p] = 0;
			else
			{
				if(i == 0)
				{
					if(profits[i] == p) A[i][p] = weights[i];
					else A[i][p] = 99999;
				}
				else
				{
					if(profits[i] <= p)
						A[i][p] = minimum(A[i-1][p], A[i-1][p-profits[i]] + weights[i]);
					else
						A[i][p] = A[i-1][p];
				}
			}
		}
	}
	printf("\t");
	for(int p = 0 ; p < max_profit; p++)
		printf("%d\t", p);
	printf("\n\n");
	for(int i = 0; i < ITEMS; i++ )
	{
		printf("%d\t", i);
		for(int p = 0 ; p < max_profit; p++)
		{
			if(A[i][p] >= 99999)
				printf("inf\t");
			else
				printf("%d\t", A[i][p]);
		}
		printf("\n");
	}
	printf("\n");

	//finding the items which should be included to get the maximum profit
	int i, p, capacity;
	for(int k = 0; k <= 10; k++)
	{
		i  = ITEMS - 1;
		p = max_profit - 1;
		capacity = k;

		while(A[i][p] > capacity) p--;
	
		printf("FOR CAPACITY = %d MAX PROFIT = %d\n", capacity, p);

		while(i >= 0 && p > 0)
		{
			//printf("Se---%d\n", A[i-1][p - profits[i]]);

			if(i == 0)
			{
				//printf("%d and %d\n", A[i][p], weights[i]);
				printf("Item %d included.\n", i);
				p = p - profits[i];
			}
			else
				if(weights[i] + A[i-1][p - profits[i]] < A[i-1][p])
				{
					printf("Item %d included.\n", i);
					p = p - profits[i];
				}
			
			i--;			
		}
		printf("=============================\n");
	}
}



int main()
{

	int weights[ITEMS] = {3, 1, 2, 4};
	int profits[ITEMS] = {1, 0, 4, 2};

	/*
	float profits[ITEMS] = {1.3, 0, 4.6, 2.7};
	printf("Elements ::: \n");
	for(int i = 0; i < ITEMS; i++)
	{
		printf("%f\t", profits[i]);
	}
	printf("\n");

	float e = 0.5;
	printf("VALUE USED = %f\n", rounding_and_scaling(profits, e));


	printf("Elements ::: \n");
	for(int i = 0; i < ITEMS; i++)
	{
		printf("%f\t", profits[i]);
	}
	printf("\n");

	*/
	MaXProfit(profits, weights);

	return 0;
}