#include <stdio.h>


int isPrime(int num)
{
	if (num <= 1)
	{
		return 0; // 소수가 아닌 경우 << 1은 소수 아님
	}

	for (int i = 2; i * i <= num; i++)
	{
		if (num % i == 0)
		{
			return 0; // 소수가 아닌 경우
		}
	}

	return 1; // 소수 일 경우
}

int getHash(int data, int M,int q)
{
	return data % M; 
}
int reGetHash(int data, int M, int q)
{
	return q-(data%q);

}


int main()
{
	int M = 0;// 해시 크기
	int N = 0; // 최대 삽입 갯수
	int q = 0;
	char order;
	int data; // 입력 받을 숫자

	int *arr;
	int *arrTemp;
	int i=0, j, k=0;

	int printCount = 0;
	int crachCount = 0;
	int max = 0;
	int index;


	do
	{
		scanf("%d", &M);
	} while (isPrime(M) == 0 && M <= 0);
	scanf("%d", &N);
	scanf("%d", &q);

	arr = (int*)malloc(sizeof(int)*M); //M 사이즈 만큼 배열 선언

	for (i = 0; i < M; i++)
	{
		arr[i] = 0;
	}

	while (1)
	{
		scanf("%c", &order);

		if (order == 'i')
		{
			crachCount = 0;
			scanf("%d", &data);
			index = getHash(data, M, q);
			while (arr[index] != 0)
			{
				index = index + reGetHash(data,M,q);

				if (index >= M)
				{
					index = index - M;
				}
				crachCount++;
			}

			if (crachCount != 0)
			{
				for (i = 0; i < crachCount; i++)
				{
					printf("C");
				}
			}
			printf("%d\n", index);
			arr[index] = data;
			max++;
			if (max == N)
			{
				for (i = 0; i < M; i++)
				{
					printf(" %d", arr[i]);
				}
				printf("\n");
			}

		}

		if (order == 's')
		{
			k = 0;
			scanf("%d", &data);

			for (i = 0; i < M; i++)
			{
				if (arr[i] == data)
				{
					printf(" %d", i);
					k++;
					break;
				}

			}

			if (k != 0)
			{
				printf(" %d\n", data);
			}
			else
				printf("%d\n", -1);
	
			

		}

		else if (order == 'p')
		{
			for (i = 0; i < M; i++)
			{
				printf(" %d", arr[i]);		
			}
			printf("\n");
			
		}


		else if (order == 'e')
		{
			break;
		}
		


	}
	return 0;
}