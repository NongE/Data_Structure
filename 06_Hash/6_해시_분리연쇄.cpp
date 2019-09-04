#include <stdio.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

node *createNode()
{
	node *newNode = (node*)malloc(sizeof(node));
	newNode->data = NULL;
	newNode->next = NULL;
	return newNode;
}

node *makeNode(int data)
{
	node *q = createNode();
	q->data = data;
	return q;
}


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

int getHash(int data, int M)
{
	return data % M;
}


int main()
{
	char order; // 명령어
	int data = 0; // 입력 숫자
	node *findNode;
	node *tempInsert;
	node *p;

	int M = 0; // 테이블의 크기
	int *arr;

	int i, j, k;
	int temp=0;
	int sub=0;

	do
	{
		scanf("%d", &M);
		//getchar();
	} while (isPrime(M) == 0 && M<=0);

	arr = (int*)malloc(sizeof(int)*M); //M 사이즈 만큼 배열 선언
	
	for (i = 0; i < M; i++)
	{
		arr[i] = NULL;
	}

	while (1)
	{
		scanf("%c",&order);
		//getchar();

		if (order == 'i')
		{
			scanf("%d", &data);
		//	getchar();


			if (arr[getHash(data, M)] == NULL)
			{
				tempInsert = makeNode(data); // 사용자가 입력한 숫자를 토대로 노드 만들기
				arr[getHash(data, M)] = tempInsert;
			}

			else
			{
				tempInsert = makeNode(data);
				findNode = arr[getHash(data, M)];

				tempInsert->next = findNode;
				arr[getHash(data, M)] = tempInsert;

			}

		}

		if (order == 's')
		{
			
			temp = 0;
			scanf("%d", &data);
		//	getchar();

			for (i = 0; i < M; i++)
			{
				k = 0;

				if (arr[i] != NULL)
				{
					findNode = arr[i];
					while (1)
					{
						if (findNode->data == data)
						{
							k++;
							temp++;
							break;
						}
						if (findNode->next != NULL)
						{
							k++;
							findNode = findNode->next;
						}
						else
						{
							break;
						}
					}
					if (temp != 0) break;
				}
			}

			
			if(temp == 0) 
			{
				printf("%d\n",0);

			}

			else
			{
				printf("%d\n", k);
			}

		}


		if (order == 'd')
		{
			k = 0;
			temp = 0;
			scanf("%d", &data);
		//	getchar();

			for (i = 0; i < M; i++)
			{
				k = 0;

				if (arr[i] != NULL)
				{
					findNode = arr[i];
					p = arr[i];
					while (1)
					{
						if (findNode->data == data)
						{
							tempInsert = arr[i];
							if (tempInsert->data==data)
							{
								findNode = findNode->next;
								arr[i] = findNode;
								k++;
								temp++;
								break;
							}
							else
							{	
								tempInsert = findNode->next;
								p->next = tempInsert;
								arr[i] = p;
								k++;
								temp++;
								break;
							}

						}
						if (findNode->next != NULL)
						{
							if (k != 0)
							{
								p = p->next;
							}
							findNode = findNode->next;
							k++;
						}
						else
						{
							break;
						}
					}
					if (temp != 0) break;
				}
			}

			if (temp == 0)
			{
				printf("%d\n", 0);

			}
			else
			{
				printf("%d\n", k);
			}

		}



		else if (order == 'p')
		{
			for (i = 0; i < M; i++)
			{
				if (arr[i] != NULL)
				{
					findNode = arr[i];
					while (1)
					{
						printf(" %d", findNode->data);
						if (findNode->next != NULL)
						{
							findNode = findNode->next;
						}
						else
						{
							break;
						}
					}
				}
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