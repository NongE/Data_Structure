#include <stdio.h>

int count = 0;
int number = 0;
char order;
int arr[100];

void upHeap(int num);
void printHeap();
void insertHeap(int num);
void upHeap(int num);
void removeMax();
void downHeap(int num);

void insertHeap(int num)
{
	count++;

	if (count == 1)
	{
		arr[count] = num;
		printf("0\n");
	}
	else
	{
		arr[count] = num;
		printf("0\n");
		upHeap(count);
	}

}

void upHeap(int num)
{
	int i;
	int root;
	int temp;

	for (i = 2; i <= num; i++)
	{
		root = i / 2;

		if (arr[root] < arr[i]) // 좌우측 자식과 크기 비교, 루트는 1부터 시작이기에 루트 0은 무시
		{
			temp = arr[i];
			arr[i] = arr[root];
			arr[root] = temp; // 부모자식 교한
	

			if (root % 2 == 0 && root != 1 && arr[root] > arr[root / 2]) // 부모 자식 교환 후 그 상위 부모와 크기 비교, 우측 확인
			{
				temp = arr[root / 2];
				arr[root / 2] = arr[root];
				arr[root] = temp;
				upHeap(root);
			}

			else if (root % 2 == 1 && root != 1 && arr[root] > arr[root / 2])// 부모 자식 교환 후 그 상위 부모와 크기 비교, 좌측 확인
			{
				temp = arr[root / 2];
				arr[root / 2] = arr[root];
				arr[root] = temp;
				upHeap(root);

			}
		}

	}

}



void removeMax()
{
	int temp;

	temp = arr[1];
	arr[1] = arr[count];
	arr[count] = temp;
	count--;

	downHeap(1);
}


void downHeap(int num)
{
	int temp;

	while (1)
	{
		if ((num * 2) == count)
		{
			if (arr[num] < arr[2 * num])
			{
				temp = arr[num];
				arr[num] = arr[2 * num];
				arr[2 * num] = temp;
				num = num * 2;
			}
			else
			{
				break;
			}
		}
		else if ((num * 2) + 1 <= count)
		{
			if (arr[2 * num] < arr[2 * num + 1])
			{
				if (arr[num] < arr[2 * num + 1])
				{
					temp = arr[num];
					arr[num] = arr[2 * num + 1];
					arr[2 * num + 1] = temp;
					num = num * 2 + 1;
				}
				else
					break;
			}
			else
			{
				if (arr[num] < arr[2 * num])
				{
					temp = arr[num];
					arr[num] = arr[2 * num];
					arr[2 * num] = temp;
					num = num * 2;
				}
				else
				{
					break;
				}
			}
		}
		else
			break;
	}
}


void printHeap()
{
	int i;

	for (i = 1; i <= count; i++)
	{
		printf(" %d", arr[i]);
	}
	printf("\n");

}

int main()
{

	while (1)
	{
		scanf("%c", &order);
		getchar();

		if (order == 'i')
		{
			scanf("%d", &number);
			getchar();
			insertHeap(number);
		}

		else if (order == 'd' && count > 0)
		{
			printf("%d\n", arr[1]);
			removeMax();

		}
		else if (order == 'p')
		{
			if (count >= 1)
			{
				printHeap();
			}

		}

		else if (order == 'q')
		{
			return 0;
		}


	}



	return 0;

}