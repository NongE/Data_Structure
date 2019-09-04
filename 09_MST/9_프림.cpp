#include <stdio.h>

int **g;

int *dist;
int cost=0;

int *answer;
int answerCount = 0;

int N, M;

void prim()
{
	int i, j, k;
	int min = 999;
	int index;
	int find = 0;
/*
	printf("현재 dist\n");
	for (j = 0; j < N; j++)
	{
		printf("%d ", dist[j]);
	}
	printf("\n");
*/
	for (i = 0; i < N; i++)
	{
		if ((dist[i] < min) && (dist[i] != 0))
		{
			min = dist[i];
			index = i;
		}
	}
	
	answer[answerCount] = index + 1;
	answerCount++;
	cost += min;

	for (i = 0; i < N; i++)
	{
		if (g[index][i] < dist[i] && (g[index][i] != 0))
		{
			dist[i] = g[index][i];
		}
	}

	dist[index] = 0;
/*
	printf("현재 dist\n");
	for (j = 0; j < N; j++)
	{
		printf("%d ", dist[j]);
	}
	printf("\n");

	


	printf("현재 answer\n");
	for (j = 0; j < answerCount; j++)
	{
		printf("%d ", answer[j]);
	}
	printf("\n");

*/

	if (answerCount == N)
	{
		//printf("\n");
		for (j = 0; j < N; j++)
		{
			printf("%d ", answer[j]);
		}
		printf("\n");
		printf("%d\n",cost);
		return;
	}
	
	
	prim();

}


int main()
{

	int i, j, k;
	int a, b, c;

	scanf("%d %d", &N, &M);


	g = (int**)malloc(sizeof(int*) * (N));

	for (i = 0; i < N; i++)
	{
		g[i] = (int*)malloc(sizeof(int) * (N));
	}


	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			g[i][j] = 999;
		}
	}


	dist = (int*)malloc(sizeof(int)*(N));

	for (i = 0; i < N; i++)
	{
		dist[i] = 999;
	}


	answer = (int*)malloc(sizeof(int)*(N));
	
	for (i = 0; i < N; i++)
	{
		answer[i] = 0;
	}
/*
	printf("\n행렬 초기화 완료\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%d ", g[i][j]);
		}
		printf("\n");
	}
*/
	for (i = 0; i < M; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		getchar();
		g[a-1][b-1] = c;
		g[b-1][a-1] = c;

	}

	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (i == j) 
			{
				g[i][j] = 0;
			}
		}

	}

/*
	printf("\n인접행렬 현황 \n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%3d ", g[i][j]);
		}
		printf("\n");
	}
*/
	answer[answerCount] = 1;
	answerCount++;

	for (i = 0; i < N; i++)
	{
		dist[i] = g[0][i];
	}

	prim();

	return 0;
}