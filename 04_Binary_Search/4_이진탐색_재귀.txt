#include <stdio.h>

int *arr;
int N;

int findNum(int start, int end, int K)
{
	int mid = (start + end) / 2;


	if (start > end)
	{
		return start - 1;
	}

	else if (arr[mid] == K)
	{
		return mid;
	}

	else if (K < arr[mid])
	{
		findNum(start, mid-1, K);
	}

	else if (K > arr[mid])
	{
		findNum(mid + 1, end, K);
	}


}

int main()

{
	int K;
	
	int i;

	scanf("%d %d",&N,&K);
	getchar();

	arr = (int*)malloc(sizeof(int)*N);

	for (i = 0; i < N; i++)
	{
		scanf("%d",&arr[i]);
		getchar();
	}

	printf(" %d", findNum(0, N - 1, K));



	return 0;

}