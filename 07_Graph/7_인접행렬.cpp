#include <stdio.h>



void changeG(int g[7][7], int a, int b, int w)
{
	int temp;

	if (a != b)
	{
		g[a][b] = w;
		g[b][a] = w;
	}
	else
		g[a][b] = w;

}

void printG(int g[7][7], int N)
{
	int i;
	for(i =1; i<7; i++)
	{
		if (g[N][i] != 0)
		{
			printf(" %d ", i);
			printf("%d", g[N][i]);
		}
	}
	printf("\n");
	
}

int main()
{
	char O;
	int N;
	int a, b, w;
	int i, j=0;
	int g[7][7] = {0};


	g[1][2] = 1;
	g[1][3] = 1;
	g[1][4] = 1;
	g[1][6] = 2;

	g[2][1] = 1;
	g[2][3] = 1;

	g[3][1] = 1;
	g[3][2] = 1;
	g[3][5] = 4;

	g[4][1] = 1;

	g[5][3] = 4;
	g[5][5] = 4;
	g[5][6] = 3;

	g[6][1] = 2;
	g[6][5] = 3;


	while (1)
	{
		scanf("%c",&O);

		if (O == 'a')
		{
			j = 0;
			scanf("%d", &N);

			if (N >= 7 || N <= 0)
			{
				printf("-1\n");
			}

			else
			{
				for (i = 1; i < 7; i++)
				{
					if (g[N][i] == 0)
						j++;
				}

				if (j == 6)
				{
					j = 0;
					printf("-1\n");
				}

				else
				{
					printG(g, N);
				}
			}
		}

		else if (O == 'm')
		{
			scanf("%d", &a);
			scanf("%d", &b);
			scanf("%d", &w);

			if (a > 6 || b > 6)
			{
				printf("-1\n");
			}
			else
			{
				changeG(g, a, b, w);
			}

		}

		else if (O == 'q')
		{
			break;
		}

	}


	return 0;
}