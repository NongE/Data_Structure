#include <stdio.h>

typedef struct node
{
	int data; // 데이터 값
	int weight; // 무게
	struct node *next; // 다음 노드

}node;

node *g; // 그래프 관련 노드
int M, N, S = 0;

int *stack; // 스택 노드
int stackCount = 0;
int *travelCheck; // 해당 노드가 탐색되었었는지 유무 판단


node *createNode()
{
	node *q = (node*)malloc(sizeof(node));
	q->data = NULL;
	q->weight = NULL;
	q->next = NULL;
}

node *sortG(node *g, int d, int w)
{
	int min = g->data; // 그래프의 가장 작은값 = 맨앞에 있는 숫자
	node *q = g;
	node *p;
	int t1, t2; // data와 weight를 저장하기 위한 임시숫자

	while (q->next->data != d)
	{
		q = q->next;
	} // 맨 마지막 이전 노드까지 이동 (새로 삽입된 이전 노드까지 이동)

	p = q->next; // 새로 삽입된 노드
	t1 = q->data; // 이전 노드의 데이터와 가중치 저장
	t2 = q->weight;

	while (1)
	{
		if (q->data <= d)
			break; // 만약 이전노드의 데이터보다 새로들어온 노드의 데이터가 큰경우 탈출 (이미 오름차순)

		else
		{
			q->data = p->data; // 노드 정보 교환
			q->weight = p->weight;
			p->data = t1;
			p->weight = t2;
		}
	}

	return g;
}

node *insertG(node *g, int d, int w) // 삽입 함수
{
	node * q = createNode();
	node * checkNode = g;
	q->data = d;
	q->weight = w;
	int cc = 0;

	if (g == NULL)
	{
		g = q; // 만약 빈노드라면 q 삽입
		return g;
	}

	else if (g->data == NULL)
	{
		g = q; // 만약 빈노드라면 q 삽입
		return g;

	}
	else
	{
		g->next = insertG(g->next, d, w); // 빈 노드가 아니라면 재귀함수를 통해 다음 노드로 이동 후 삽입
	}

	g = sortG(g, d, w); // 정렬

	return g;

}


node * optimalNode(node *copy, node *paste)
{

	if (copy->data == NULL || paste == NULL)
	{
		paste = copy;
	}
	else
	{
		paste->data = copy->data;
		paste->next = copy->next;
		paste->weight = copy->weight;
	}


	return paste;
}

int check(node*g, int n)
{
	node *q = g;
	int i;
	int cc = 0;
	while (1)
	{
		if (q->data == n)
		{
			cc++;
			break;
		}
		q = q->next;

		if (q == NULL)
		{
			break;
		}
		else if (q->data == NULL)
		{
			break;
		}

	}

	return cc;
}

void travelDFS(node *q, int point)
{
	int i, j, k;
	int cc = 0;
	node *temp = q;

	while (1)
	{
		if (travelCheck[temp->data] == 0)
		{
			cc++;
			temp = temp->next;
			if (temp == NULL)
			{
				stackCount--;
				stack[stackCount] = 0;

				if ((stackCount - 1) < 0)
					return 0;

				temp = optimalNode(&g[stack[stackCount - 1]], temp);
				travelDFS(temp, temp->data);
			}
		}
		else
			break;


	}


	if (cc == 0)
	{
		if (travelCheck[point] != 0)
		{
			printf("%d\n", point);
			travelCheck[point] = 0;
			stack[stackCount] = point;
			stackCount++;
		}
		travelDFS(&g[point], temp->data);

	}
	else
	{

		if (travelCheck[temp->data] != 0)
		{
			printf("%d\n", temp->data);
			travelCheck[temp->data] = 0;
			stack[stackCount] = temp->data;
			stackCount++;
		}
		travelDFS(&g[temp->data], temp->data);
	}
}


int main()

{
	int a, b;
	int i, j, k;

	//첫 줄에 정점의 개수 N, 간선의 개수 M, 순회 시작 정점 번호 S

	scanf("%d %d %d", &N, &M, &S);


	g = (node*)malloc(sizeof(node)*(N + 1));
	stack = (int*)malloc(sizeof(int)*(N + 1));
	travelCheck = (int*)malloc(sizeof(int)*(N + 1));

	node *q = NULL;

	for (i = 0; i < N + 1; i++)
	{
		memset(&g[i], NULL, sizeof(node));
	}

	for (i = 0; i < N + 1; i++)
	{
		travelCheck[i] = 0;
		stack[i] = 0;
	}


	for (i = 0; i < M; i++)
	{
		scanf("%d %d", &a, &b);
		travelCheck[a] = a;
		travelCheck[b] = b;


		q = optimalNode(&g[a], q);
		// 배열로부터 리스트를 받아옴

		if (check(q, a) == 0)
		{
			q = insertG(q, a, 1);
		}
		if (check(q, b) == 0)
		{
			q = insertG(q, b, 1);
		}

		g[a].data = q->data;
		g[a].next = q->next;
		g[a].weight = q->weight;
		// 계산 완료된 노드를 배열로 추가



		// 무방향 그래프로 반대 방향도 추가
		q = optimalNode(&g[b], q);

		if (check(q, b) == 0)
		{
			q = insertG(q, b, 1);
		}
		if (check(q, a) == 0)
		{
			q = insertG(q, a, 1);
		}

		g[b].data = q->data;
		g[b].next = q->next;
		g[b].weight = q->weight;

	}

	travelDFS(&g[S], S);

	return 0;
}