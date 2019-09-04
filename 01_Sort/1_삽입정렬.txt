#include <stdio.h>



void printArr(int *arr,int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf(" %d",arr[i]);
	}
}



void insertSort(int *arr, int n)
{
	int i, j, k;
	int temp;
	int index;
	int count = 0;

	for (i = 0; i < n; i++)
	{
		temp = arr[i];

		if (i - 1 >= 0)
		{
			for (j = (i - 1); j >= 0; j--)
			{
				if (temp < arr[j])
				{
					count++;
					index = j;
				}
			}
		}

		if (count != 0)
		{
			for (k = i; k > index; k--)
			{
				{
					arr[k] = arr[k-1];
				}
				
			}
			arr[index] = temp;
			count = 0;
		}
	}


}



int main()
{
	int *arr;
	int n;
	
	scanf("%d",&n);
	getchar();

	arr = (int*)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d",&arr[i]);
	}

	insertSort(arr,n);

	printArr(arr,n);

	return 0;
}