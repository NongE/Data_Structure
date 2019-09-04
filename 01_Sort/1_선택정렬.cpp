#include <stdio.h>

void selectArr2(int arr[], int n) 
{
	int max;
	int temp;
	int index;
	int i, j;

	for (i = n-1; i >=0; i--)
	{
		int max = arr[0];

		for (j = i; j >=0; j--)
		{
			if (max <= arr[j])
			{
				max = arr[j];
				index = j;
			}
		}

		temp = arr[i];
		arr[i] = arr[index];
		arr[index] = temp;
		

	}

}


int main()
{
	int i;
	int input;
	int *arr;

	scanf("%d",&input);
	arr = (int*)malloc(sizeof(int)*input);

	for (i = 0; i < input; i++)
	{
		scanf("%d",&arr[i]);
	}

	selectArr2(arr, input);

	for (i = 0; i < input; i++)
	{
		printf(" %d ",arr[i]);
	}


	return 0;
}