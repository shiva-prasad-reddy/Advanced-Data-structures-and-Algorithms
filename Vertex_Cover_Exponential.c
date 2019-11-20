#include<stdio.h>
#define VERTICES 4
#define EDGES 6

int checkVertexCoverOrNot(int *vertices, int edgeList[EDGES][2])
{
	int covers[EDGES] = {};

	for(int i = 0; i < VERTICES; i++)
	{
		if(vertices[i] == 1)
		{
			for(int j = 0; j < EDGES; j++)
				if(edgeList[j][0] == i || edgeList[j][1] == i) covers[j] = 1;
		}
	}

	for(int i = 0; i < EDGES; i++)
		if(covers[i] == 0) return 0;

	return 1;
}

void generateVertexCover(int i, int *vc, int edgeList[EDGES][2], float *weights)
{
	if(i < VERTICES)
	{
		int vc_[VERTICES] = {};
		for(int j = 0; j < VERTICES; j++) vc_[j] = vc[j];
		vc_[i] = 1;
		i++;
		generateVertexCover(i, vc_, edgeList, weights);
		generateVertexCover(i, vc, edgeList, weights);
	}
	else
	{
		if(checkVertexCoverOrNot(vc, edgeList) == 1)
		{
			float total_weight = 0;
			printf("\nVertices in vertex cover >>>\t");
			for(int i = 0; i < VERTICES; i++)
			{
				if(vc[i] == 1)
				{
					printf("%d, ", i);
					total_weight += weights[i];
				}
			}
			printf("\t&& Weight = [ %f ]", total_weight);
		}
	}

}




int main()
{
	float weights[VERTICES] = {2.1, 3.1, 22, 1.2};//{20, 5, 11, 2};
	int edgeList[EDGES][2] = {
		{0, 1},
		{0, 2},
		{0, 3},
		{1, 2},
		{1, 3},
		{2, 3}
	};

	int vc[VERTICES] = {};

	generateVertexCover(0, vc, edgeList, weights);
	printf("\n");
	return 0;
}