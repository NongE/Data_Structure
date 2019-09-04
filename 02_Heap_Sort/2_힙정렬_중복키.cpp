#include <stdio.h>

int H[100];
int n; // 크기 입력
int index;

void downHeap(int num);
void buildHeap(int num)
{
	if (num > n)
		return;
	else
	{
		buildHeap(2 * num); // 트리의 왼쪽
		buildHeap(2 * num + 1); // 오른쪽
		downHeap(num);// 정렬
	}
}

void downHeap(int num) // 다운힙 시작
{
	int temp;

	while (1)
	{
		if ((num * 2) == n)
		{
			if (H[num] < H[2 * num])
			{
				temp = H[num];
				H[num] = H[2 * num];
				H[2 * num] = temp;
				num = num * 2;
			}
			else
			{
				break;
			}
		}
		else if ((num * 2) + 1 <= n)
		{
			if (H[2 * num] < H[2 * num + 1])
			{
				if (H[num] < H[2 * num + 1])
				{
					temp = H[num];
					H[num] = H[2 * num + 1];
					H[2 * num + 1] = temp;
					num = num * 2 + 1;
				}
				else
					break;
			}
			else
			{
				if (H[num] < H[2 * num])
				{
					temp = H[num];
					H[num] = H[2 * num];
					H[2 * num] = temp;
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



void inPlaceHeapSort() // 순차적으로 배열 정리, 제자리 정렬
{
	int i = 0;

	while (n > 0)
	{
		int temp;

		temp = H[1];
		H[1] = H[n];
		H[n] = temp;
		n--;

		downHeap(1);
	}
	

}

void printHeap()
{
	int i;

	for (i = 1; i <= index; i++)
	{
		printf(" %d", H[i]);
	}
	printf("\n");

}

int main()

{
	int i, j, k;

	do
	{
		scanf("%d", &n); // 배열 크기 입력받기
		getchar();
	} while (n>100);

	index = n;

	for (i = 1; i <= n; i++)
	{
		do
		{
			scanf("%d", &H[i]); // 크기 만큼 숫자 입력
			getchar();
		} while (H[i]<=0);
	}

	buildHeap(1);
	//printHeap();
	inPlaceHeapSort();
	printHeap();


	return 0;
}