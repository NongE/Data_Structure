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
int *answer;
int answerCount = 0;
int *answerMin;
int answerMinCount = 0;

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
	

void DijkstraSP()
{
	node *q = &g[S];
	node *p;
	int i, j, k;
	
	int temp;
	int *distTemp = (int*)malloc(sizeof(int)*N + 1);
	for (int i = 0; i < N + 1; i++)
	{
		distTemp[i] = 999;
	}
	int temp2 = 0;
	int min = 999;
	int index=0;

	/*printf("현재 dist현황 총 갯수 %d\n",temp);
	for (i = 0; i < temp; i++)
	{
		printf("%d ",dist[i]);
	}
	printf("\n");*/

	for (i = 0; i < N + 1; i++)
	{
		if (min > dist[i] && distCheck[i]!=-1)
		{
			min = dist[i];
			index = i;
		}

	}
	//printf("min is %d // index is %d\n",min,index);

	answer[answerCount] = index;
	answerCount++;
	answerMin[answerMinCount] = min;
	answerMinCount++;

	distCheck[index] = -1;
	p = &g[index];
	while (p != NULL)
	{
		if (distCheck[p->data] != -1)
		{
			distTemp[p->data] = p->weight+min;
			p = p->next;
		}

		else // q->data == S
		{
			dist[p->data] = 0;
			p = p->next;
		}

	}

	/*printf("현재 distTemp현황 ");
	for (i = 0; i < N+1; i++)
	{
		printf("%d ", distTemp[i]);
	}
	printf("\n");*/


	for (i = 0; i < N+1; i++)
	{
		if (dist[i] > distTemp[i])
		{
			dist[i] = distTemp[i];
		}
	}

	/*printf("변경후 dist현황 총 갯수 %d\n", temp);
	for (i = 0; i < temp; i++)
	{
		printf("%d ", dist[i]);
	}
	printf("\n");*/

	distTemp = NULL;
	free(distTemp);

	if (min == 999)
		return;


	DijkstraSP();
}


int main()

 {
	int a, b, c;
	int i, j, k;
	int temp=0;

	//첫 줄에 정점의 개수 N, 간선의 개수 M, 순회 시작 정점 번호 S

	scanf("%d %d %d", &N, &M, &S);

	if (N < S)
		return;
	g = (node*)malloc(sizeof(node)*(N+1));

	node *q = NULL;

	for (i = 0; i < N + 1; i++)
	{
		memset(&g[i], NULL, sizeof(node));
	}

	dist = (int*)malloc(sizeof(int)*N+1);

	for (int i = 0; i < N + 1; i++)
	{
		dist[i] = 999;
	}

	distCheck = (int*)malloc(sizeof(int)*N+1);
	for (int i = 0; i < N + 1; i++)
	{
		distCheck[i] = 1;
	}
	answer = (int*)malloc(sizeof(int)*N + 1);
	answerMin = (int*)malloc(sizeof(int)*N + 1);
	for (i = 0; i < M; i++)
	{
		scanf("%d %d %d", &a, &b, & c);
		
		distCheck[a] = 1;
		distCheck[b] = 1;
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

		

		// 무방향 그래프로 반대 방향도 추가
		q = optimalNode(&g[b], q);

		if (check(q, b) == 0)
		{
			q = insertG(q, b, c);
		}
		if (check(q, a) == 0)
		{
			q = insertG(q, a, c);
		}

		g[b].data = q->data;
		g[b].next = q->next;
		g[b].weight = q->weight;

	}

	distCheck[S] = -1;
	/*printf("초기 distCheck ");
	for (i = 0; i < N + 1; i++)
	{
		printf("%d ", distCheck[i]);
	}
	printf("\n");
	*/

	q = &g[S];
	while (q != NULL)
	{
		if (distCheck[q->data] != -1)
		{
			dist[q->data] = q->weight;
			q = q->next;
		}
		else // q->data == S
		{
			dist[q->data] = 0;
			q = q->next;
		}
	}

	/*printf("dist 현황 \n");
	for (i = 0; i < N + 1; i++)
	{
		printf("%d ", dist[i]);
	}
	printf("\n");*/


	DijkstraSP();

	/*
	while (&g[1] != NULL)
	{
		printf("%d %d\n", g[1].data, g[1].weight);
		if (g[1].next != NULL)
		{
			g[1].data = g[1].next->data;
			g[1].weight = g[1].next->weight;
			g[1].next = g[1].next->next;
		}
		else
			break;
	}*/
	
	for (i = 0; i < answerCount-1; i++)
	{
		for (j = 0; j < (answerCount-2) - i; j++)
		{
			if (answer[j] > answer[j + 1])
			{
				temp = answer[j];
				answer[j] = answer[j + 1];
				answer[j + 1] = temp;

				temp = answerMin[j];
				answerMin[j] = answerMin[j + 1];
				answerMin[j + 1] = temp;
			}

		}

	}
	

	for (i = 0; i < answerCount-1; i++)
	{
		printf("%d %d\n", answer[i], answerMin[i]);
	}

	return 0;
}