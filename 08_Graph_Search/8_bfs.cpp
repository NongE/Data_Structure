#include <stdio.h>

int **g;

int *travel;
int travelCount = 0;

int N, M, S;

int *qu;
int quStart = -1;
int quCount = 0;


void travelBFS(int S)
{

	int i = 0, j, k;
	int cc = 0;

	if (g[S][S] != 0)
	{
		cc = 0;
		for (j = 0; j < N+1; j++)
		{
			if (travel[j] == S)
			{
				cc++;
			}

		}
		if (cc == 0)
		{
			travel[travelCount] = S;
			travelCount++;
			qu[quCount] = S;
			quCount++;
		}
		g[S][S] = 0;
	}

	for (i = 1; i < N + 1; i++)
	{
		if (g[S][i] != 0)
		{
			cc = 0;
			for (j = 0; j < N+1; j++)
			{
				if (travel[j] == i)
				{
					cc++;
				}

			}
			if (cc == 0)
			{
				travel[travelCount] = i;
				travelCount++;
				g[S][i] = 0;
				g[i][S] = 0;
				qu[quCount] = i;
				quCount++;
			}
		}
	}


	//printf("\n");
	quStart++;


	if (quStart > N)
	{
		for (i = 0; i < N; i++)
		{
			printf("%d\n", travel[i]);

		}
		return;
	}
	travelBFS(qu[quStart]);


}


int main()
{
	
	int i, j, k;
	int a, b;

	scanf("%d %d %d",&N,&M,&S);


	g = (int**)malloc(sizeof(int*) * (N + 1));

	for (i = 0; i < N+1; i++)
	{
		g[i] = (int*)malloc(sizeof(int) * (N+1));
	}


	for (i = 1; i < N + 1; i++)
	{
		for (j = 1; j < N + 1; j++)
		{
			g[i][j] = 0;
		}
	}


	travel = (int*)malloc(sizeof(int)*(N + 1));

	for (i = 1; i < N + 1; i++)
	{
		travel[i] = 0;
	}


	qu = (int*)malloc(sizeof(int)*(N + 1));

	for (i = 1; i < N + 1; i++)
	{
		qu[i] = 0;
	}



	for (i = 0; i < M; i++)
	{
		scanf("%d %d",&a,&b);
		g[a][a] = 1;
		g[b][b] = 1;
		g[a][b] = 1;
		g[b][a] = 1;

	}

	travelBFS(S);

	return 0;
}