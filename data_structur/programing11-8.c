// Kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�

#include<stdio.h>   // ǥ�� ����� �Լ� ����� ���� ���
#include<stdlib.h>  // ���� �޸� �Ҵ�, qsort ���� ���� ���

// ��� ����
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100  // �ִ� ���� ��
#define INF 1000          // ���Ѵ� ���� �ǹ��ϴ� ���

int parent[MAX_VERTICES];  // ���μ� ����(Union-Find)���� �� ������ �θ� ����

// ���μ� ���� �ʱ�ȭ �Լ�: ��� ������ �θ� -1�� ���� (�ڱ� �ڽ��� ��Ʈ)
void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

// Ư�� ��� curr�� ��Ʈ(�ֻ��� �θ�)�� ã�� �Լ� (Find ����)
// �� ������ ��� ������ ���� �⺻ ������
int set_find(int curr)
{
	if (parent[curr] != -1)     // ��Ʈ�� �ƴ϶��
		return curr;            // ���� ��尡 ��Ʈ�� ��� �״�� ��ȯ
	while (parent[curr] != -1)   // ��Ʈ ��带 ã�� ���� �θ� ���� �ö�
		curr = parent[curr];
	return curr;                // ��Ʈ ��� ��ȯ
}

// �� ������ ��ġ�� �Լ� (Union ����)
// a�� b�� ���� ������ �ϳ��� ��ħ
void set_union(int a, int b)
{
	int root1 = set_find(a);   // ���� a�� ��Ʈ�� ã��
	int root2 = set_find(b);   // ���� b�� ��Ʈ�� ã��
	if (root1 != root2)        // ���� �ٸ� �����̶��
		parent[root1] = root2; // root1�� �θ� root2�� ���� �� ���� ��ħ
}

// ������ ��Ÿ���� ����ü
struct Edge {
	int start;   // ������ ���� ����
	int end;     // ������ �� ����
	int weight;  // ������ ����ġ
};

// �׷��� ����ü: ���� ����Ʈ�� ǥ����
typedef struct GraphType {
	int n;                         // ���� ������ ��
	struct Edge edges[2 * MAX_VERTICES]; // ���� �迭 (�ִ� 200������ ���� ����)
} GraphType;

// �׷��� �ʱ�ȭ �Լ�: ���� ���� 0, ���� �迭 �ʱ�ȭ
void graph_init(GraphType* g)
{
	g->n = 0;  // ���� �� �ʱ�ȭ
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;  // �⺻������ ���� ����ġ�� ���Ѵ�� �ʱ�ȭ
	}
}

// ������ �׷����� �߰��ϴ� �Լ�
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;  // ���� ���� ����
	g->edges[g->n].end = end;      // �� ���� ����
	g->edges[g->n].weight = w;     // ����ġ ����
	g->n++;                        // ���� �� 1 ����
}

// qsort�� ���� �� �Լ�: ������ ����ġ �������� �������� ����
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);  // ����ġ ���� ����
}

// Kruskal �˰��� ���� �Լ�
void kruskal(GraphType* g)
{
	int edge_accepted = 0;  // ���õ� ������ ����
	int uset, vset;         // ������ �� �� ������ ���� ���� ��ȣ
	struct Edge e;          // ���� ���õ� ����

	set_init(g->n);  // ���μ� ���� �ʱ�ȭ
	qsort(g->edges, g->n, sizeof(struct Edge), compare);  // ���� ����

	printf("ũ�罺Į  �ּ� ���� Ʈ�� �˰��� \n");

	int i = 0;  // ���� �迭 �ε��� �ʱ�ȭ
	// ���� Ʈ���� ���� �� - 1���� ������ �ʿ��ϹǷ�, �׸�ŭ �ݺ�
	while (edge_accepted < (g->n - 1))
	{
		e = g->edges[i];           // ���� ���� ����
		uset = set_find(e.start); // ���� ������ ���� ����
		vset = set_find(e.end);   // �� ������ ���� ����

		if (uset != vset) {  // �� ������ �ٸ� ���տ� ���Ѵٸ� ����Ŭ�� �ƴ�
			printf("���� (%d, %d) %d ����\n", e.start, e.end, e.weight);
			edge_accepted++;         // ���� ���� �� ����
			set_union(uset, vset);  // �� ������ ��ħ
		}
		i++;  // ���� �������� �̵�
	}
}

// ���� �Լ�: ���α׷� ������
int main(void)
{
	GraphType* g;  // �׷��� ������ ����
	g = (GraphType*)malloc(sizeof(GraphType));  // ���� �޸� �Ҵ�
	graph_init(g);  // �׷��� �ʱ�ȭ

	// �׷����� ���� ���� (����, ��, ����ġ)
	insert_edge(g, 0, 1, 29);
	insert_edge(g, 1, 2, 16);
	insert_edge(g, 2, 3, 12);
	insert_edge(g, 3, 4, 22);
	insert_edge(g, 4, 5, 27);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 6, 1, 15);
	insert_edge(g, 6, 3, 18);
	insert_edge(g, 6, 4, 25);

	kruskal(g);  // Kruskal �˰��� �����Ͽ� MST ����

	free(g);     // ���� �Ҵ�� �޸� ����
	return 0;    // ���α׷� ����
}
