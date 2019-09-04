#include <stdio.h>

typedef struct node
{
	int data; // 데이터 값
	int weight; // 무게
	struct node *next; // 다음 노드

}node;

node *g; // 그래프 관련 노드
int M, N, S = 0;

int *dist;
int *distCheck;
int count = 0;
int *answer;
int answerCount = 0;
int answerStart = -1;


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


void bellman()
{
	node *q;
	int i, j, k;

	int *distTemp = (int*)malloc(sizeof(int)*N + 1);
	for (int i = 0; i < N + 1; i++)
	{
		distTemp[i] = 999;
	}

	answerStart++;
	if (answerStart >= answerCount)
	{
		return;
	}
	q = &g[answer[answerStart]];

	/*(while (q->next == NULL)
	{
		answerStart++;
		q = &g[answer[answerStart]];
		if (answerStart >= answerCount || answerStart >= N) return;

	}*/

	
	while (q != NULL)
	{
		if (q->data != answer[answerStart])
		{
			distTemp[q->data] = q->weight + dist[answer[answerStart]];

			if (distCheck[q->data] != -1)
			{
				answer[answerCount] = q->data;
				answerCount++;
				distCheck[q->data] = -1;
			}
		}
		q = q->next;
	}

	for (i = 1; i < N + 1; i++)
	{
		if (dist[i] > distTemp[i])
		{
			dist[i] = distTemp[i];
			answer[answerCount] = i;
			answerCount++;
		} // 변경된 경로에 대해 새로고침!
	}
	/*
	printf("\n");
	for (k = 1; k < N + 1; k++)
	{
		printf("%d ",distTemp[k]);
	}*/

	//printf("an counter %d\n",answerCount);
	//printf("an start %d\n", answerStart);



	bellman();
}




int main()

{
	node *q = NULL;
	int a, b, c;
	int i, j, k;
	int temp = 0;

	//첫 줄에 정점의 개수 N, 간선의 개수 M, 순회 시작 정점 번호 S

	scanf("%d %d %d", &N, &M, &S);

	if (N < S)
		return;
	g = (node*)malloc(sizeof(node)*(N + 1));

	for (i = 0; i < N + 1; i++)
	{
		memset(&g[i], NULL, sizeof(node));
	}

	dist = (int*)malloc(sizeof(int)*N + 1);
	distCheck = (int*)malloc(sizeof(int)*N + 1);
	answer = (int*)malloc(sizeof(int)*200);

	for (i = 0; i < N + 1; i++)
	{
		dist[i] = 999;
		distCheck[i] = 1;
	}

	for (i = 0; i < M; i++)
	{
		scanf("%d %d %d", &a, &b, &c);

		q = optimalNode(&g[a], q);
		// 배열로부터 리스트를 받아옴

		if (check(q, a) == 0)
		{
			q = insertG(q, a, c);
		}
		if (check(q, b) == 0)
		{
			q = insertG(q, b, c);
		}

		g[a].data = q->data;
		g[a].next = q->next;
		g[a].weight = q->weight;
		// 계산 완료된 노드를 배열로 추가


	}
	distCheck[S] = -1;
	q = &g[S];
	while (q != NULL)
	{
		if (q->data != S)
		{
			dist[q->data] = q->weight;
			answer[answerCount] = q->data;
			answerCount++;
			distCheck[q->data] = -1;
			q = q->next;
		}
		else
		{
			dist[q->data] = 0;
			q = q->next;
		}
	}

	/*
	for (i = 1; i < N + 1; i++)
	{
		printf("%d ",dist[i]);
	}
	printf("\n");
	for (i = 0; i < answerCount; i++)
	{
		printf("%d ", answer[i]);
	}
	printf("\n");*/

	/*for (i = 1; i < N + 1; i++)
	{
		printf("%d ", distCheck[i]);
	}
	printf("\n");*/
	/*
	if (answer[0] == NULL)
		return;
*/

	bellman();


	/*
	printf("아래는 임시출력\n");
	k = 2;
	while (&g[k] != NULL)
	{
		printf("%d %d\n", g[k].data, g[k].weight);
		if (g[k].next != NULL)
		{
			g[k].data = g[k].next->data;
			g[k].weight = g[k].next->weight;
			g[k].next = g[k].next->next;
		}
		else
			break;
	}
	*/
	/*
	for (i = 1; i < N + 1; i++)
	{
		if (dist[i] >= 999)
		{
			return;
		}
	}
	*/
	for (i = 1; i < N + 1; i++)
	{
		if (i != S) {
			if (dist[i] != 999)
				printf("%d %d\n", i, dist[i]);
		}
	}
	return 0;
}