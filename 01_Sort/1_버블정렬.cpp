#include <stdio.h>


int main()

{
	int arr[10] = {1,5,3,2,4,7,6,8,10,9};
	int i, j;
	int temp;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 9-i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j+ 1] = temp;
			}

		}

	}

	for (i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}