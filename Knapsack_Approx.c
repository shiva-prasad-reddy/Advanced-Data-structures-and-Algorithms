#include<stdio.h>
#include<math.h>
#include<stdlib.h>

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
	float temp = 0, a, b;

	//rounding to each profit(xi) to the next larger multiple of (ε/n)·opt.
	printf("\nRounding each profits to the next larger multiple of (ε/n)·opt = [ %f ] where ε = [ %f ]\n", mul, e);
	//printf("Scaling profits\n");
	for(int i = 0; i < ITEMS; i++)
	{
		temp = ceil(profits[i] / mul);
		a = profits[i] - ((temp-1) * mul);
		b = (temp * mul) - profits[i];
		printf("Rounding -- %f  <  %f  <  %f >>>>>  %f\n", (temp-1)*mul, profits[i], (temp) * mul, a < b ? (temp-1)*mul : temp*mul);
		profits[i] = a < b ? (temp-1)*mul : temp*mul;

	}

	printf("\nRounded Profits >>\t");
	for(int i = 0; i < ITEMS; i++) printf("%f\t", profits[i]);
	printf("\n");

	//scaling
	printf("\nScaling the profits to fall in 1 .... n/ε\n");
	for(int i = 0; i < ITEMS; i++)
	{
		printf("%f --> %f\n", profits[i], ceil(profits[i]/mul));
		profits[i] = ceil(profits[i]/mul);
	}

	return mul;
}


void MaXProfit(float y, int *profits, int *weights)
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

	printf("ITEMS\t\t============== PROFITS ===========\n");
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
	
		printf("FOR CAPACITY = %d MAX PROFIT = %f\n", capacity, ((float)p) * y);

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
	float profits[ITEMS] = {2.1, 3.2, 1.5, 1.7};


	float e = 5; // CHANGE ε to see different results
	printf("\n\nEnter the value of ε >>> ");
	scanf("%f", &e);



	printf("\nProfits >>\t");
	for(int i = 0; i < ITEMS; i++)
	{
		printf("%f\t", profits[i]);
	}
	printf("\n");


	float mul = rounding_and_scaling(profits, e);
	

	int profitsNew[ITEMS];
	for(int i = 0; i < ITEMS; i++) profitsNew[i] = (int)profits[i];
	

	MaXProfit(mul, profitsNew, weights);

	return 0;
}