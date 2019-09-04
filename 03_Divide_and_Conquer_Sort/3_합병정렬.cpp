#include <stdio.h>

int i;
int n;

typedef struct node
{
	int data;
	struct node *next;
}node;

typedef struct list
{
	node * head;
	node * tail;
}list;

node *createNode()
{
	node *newNode = (node*)malloc(sizeof(node));
	newNode->data = NULL;
	newNode->next = NULL;

	return newNode;
}


node insertNode(list *list, int data)
{
	node *newData = createNode();
	newData->data = data;

	node *h = list->head;


	for (int j = 0; j < i; j++)
	{
		h = h->next;
	}

	node *t = list->tail;


	h->next = newData;
	newData->next = t;


}



void merge(list list, int start, int mid, int end)
{

	int x = start;
	int y = mid + 1;
	int z = end;

	node * findNode = list.head;
	for (int i = 0; i <= start-1; i++)
	{
		findNode = findNode->next;
	}

	node *s = list.head;
	for (int i = 0; i <= start; i++)
	{
		s = s->next;
	}

	node *sm = list.head;
	for (int i = 0; i <= mid; i++)
	{
		sm = sm->next;
	}

	node *m = list.head;
	for (int i = 0; i <= mid + 1; i++)
	{
		m = m->next;
	}


	while (x <= mid && y <= end)
	{
	
		if (s->data > m->data)
		{
			findNode->next = m;
			sm->next = m->next;
			m = m->next;
			findNode = findNode->next;
			y++;
		}

		else if(m->data >= s->data)
		{
			findNode->next = s;
			s = s->next;
			findNode = findNode->next;
			x++;
		}


		if (y > end)
		{
			findNode->next = s;
		}

		if (x > mid)
		{
			findNode->next = m;
		}


	}

}



void mergeSort(list list, int start, int end)
{
	int mid =  (start+end) / 2;

	if (start < end)
	{
		mergeSort(list, start, mid);
		mergeSort(list, mid + 1, end);
		merge(list, start, mid, end);
	}

}



void printList(list list)
{
	node *check = list.head->next;

	while (check != list.tail)
	{
		printf(" %d", check->data);
		check = check->next;
	}
	printf("\n");
}



int main()
{
	list list;

	list.head = createNode();
	list.tail = createNode();

	list.head->next = list.tail;

	int data;

	scanf("%d", &n);
	getchar();

	for (i = 0; i < n; i++)
	{
		do {
			scanf("%d", &data);
			getchar();
		} while (data<=0);
			insertNode(&list, data);
		
	}

	mergeSort(list, 0, n-1);

	printList(list);


	return 0;
}