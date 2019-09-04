#include <stdio.h>

typedef struct node
{
	int data; // 데이터 값
	int weight; // 무게
	struct node *next; // 다음 노드

}node;

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
			//if (q->data > d)
			q->data = p->data; // 노드 정보 교환
			q->weight = p->weight;
			p->data = t1;
			p->weight = t2;

			//node *q = g;
			//node *temp = NULL;
		}
	}

	return g;
}

node *insertG(node *g, int d, int w) // 삽입 함수
{
	node * q = createNode();
	q->data = d;
	q->weight = w;

	if (g == NULL)
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


node *changeWeight(node *g, int a, int N) // 가중치 변경함수
{
	node *q = g;
	node *temp = NULL;
	int count = 0;

	if (N != 0)
	{
		if (q == NULL)
		{
			q = insertG(g, a, N);// 노드가 빈칸인 경우 바로 삽입
			return q;
		}
		else
		{
			while (q->data != a)
			{
				q = q->next; // 해당 데이터까지 이동
				if (q == NULL) // 해당 데이터가 없는 경우 삽입 
				{
					q = insertG(g, a, N);
					return q; // 수정 위치! q->g로 변경!
				}

			}

			q->weight = N; // 무게값 변경

		}

		return g;
	
	}

	else // 가중치가 0인경우
	{

		if (q == NULL) // 노드가 비어있다면 종료
		{
			return 0;
		}

	
		else
		{
			temp = q;
			while (temp->data != a)
			{
				temp = temp->next;
				count++;
				if (temp == NULL)
					break;
			}

			if (temp != NULL)
			{
				if (q->data == a)
				{
					if (q->next != NULL)
					{
						q = q->next;
						return q; // 삭제해야할 노드가 맨앞에 있고 연결된 노드가 두개 인 경우
					}

					else
					return NULL;
				}
				else
				{
					for (int i = 1; i < count; i++)
					{
						q = q->next;
					}
					q->next = temp->next;

					return g;
				}

			}

			else
			{
				return g;
			}


		}

		return g;
	}

}

void printNode(node *g)
{
	node *p = g;

	if (p == NULL)
	{
		printf("-1");
	}
	while (p != NULL)
	{
		printf(" %d", p->data);
		printf(" %d", p->weight);
		p = p->next;
	}
	printf("\n");
}

int main()

{
	node *g[7]; // 직관적으로 수정하기 위해 0~6까지 선언, 1~6만 사용
	char O;
	int N;
	int a, b;
	int i, j, k;
	int temp;


	for (i = 1; i < 7; i++)
	{
		g[i] = NULL; // 노드 초기화
	}

	g[1] = insertG(g[1], 2, 1);
	g[1] = insertG(g[1], 3, 1);
	g[1] = insertG(g[1], 4, 1);
	g[1] = insertG(g[1], 6, 2);

	g[2] = insertG(g[2], 1, 1);
	g[2] = insertG(g[2], 3, 1);

	g[3] = insertG(g[3], 1, 1);
	g[3] = insertG(g[3], 2, 1);
	g[3] = insertG(g[3], 5, 4);

	g[4] = insertG(g[4], 1, 1);

	g[5] = insertG(g[5], 3, 4);
	g[5] = insertG(g[5], 5, 4); // 본인노드
	g[5] = insertG(g[5], 6, 3);

	g[6] = insertG(g[6], 1, 2);
	g[6] = insertG(g[6], 5, 3);

	while (1)
	{
		scanf("%c", &O);

		if (O == 'a')
		{
			scanf("%d", &N);
			if (N > 6 || N <= 0) // 6이상의 값을 넣었을때 에러 발생
			{
				printf("-1\n");
			}
			else
				printNode(g[N]);

		}
		else if (O == 'm')
		{
			scanf("%d", &a);
			scanf("%d", &b);
			scanf("%d", &N);

			if (a > 6 || b > 6 || a <= 0 || b <= 0) // 가중치를 수정하는데 있어 6 이상의 값을 넣었을때 에러발생
			{
				printf("-1\n");

			}
			else
			{
				if (a != b)
				{
					g[a] = changeWeight(g[a], b, N);
					g[b] = changeWeight(g[b], a, N);
				}
				else
					g[a] = changeWeight(g[a], b, N);
			}


		}

		else if (O == 'q')
		{
			break;
		}


	}





	return 0;
}