#include <stdio.h>

int *arr;
int N;

int findNum2(int start, int end, int K)
{
	int mid = (start + end) / 2;


	while (1)
	{

		if (arr[mid] == K)
		{
			return mid;
		}

		else if (end < 0)
		{
			return start;
		}

		else if (start == N)
		{
			return N;
		}

		else if (start > end)
		{
			return start;
		}

		

		if (K < arr[mid])
		{
			end = mid - 1;
			mid = (start + end) / 2;
		}

		else if (K > arr[mid])
		{
			start = mid + 1;
			mid = (start + end) / 2;
		}

	}

}

int main()

{

	int K;

	int i, j, k;

	scanf("%d %d", &N, &K);
	getchar();

	arr = (int*)malloc(sizeof(int)*N);

	for (i = 0; i < N; i++)
	{
		scanf("%d", &arr[i]);
		getchar();
	}

	printf(" %d", findNum2(0, N - 1, K));



	return 0;

}