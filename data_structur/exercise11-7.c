#include <stdio.h>      // ������� ���� ��� ����
#include <stdlib.h>     // ���� �޸� �Ҵ��� ���� ��� ����
#include <limits.h>     // INT_MAX ����� ���� ��� ����

#define TRUE 1          // TRUE�� 1�� ����
#define FALSE 0         // FALSE�� 0���� ����
#define MAX_VERTICES 100 // �ִ� ���� ���� ����
#define INF 100000      // ���Ѵ� (������� ���� ��� ����� ��)

// ���� ����Ʈ�� ����� ���� ��� ����ü ����
typedef struct Node {
    int vertex;         // ����� ���� ��ȣ
    int weight;         // ������ ����ġ
    struct Node* next;  // ���� ��带 ����Ű�� ������
} Node;

// �׷��� ����ü ���� (���� ����Ʈ ���)
typedef struct GraphType {
    int n;              // ������ ����
    Node* adj[MAX_VERTICES]; // �� ������ ���� ����Ʈ�� ����Ű�� ������ �迭
} GraphType;

// ���� �������κ��� �� ���������� �ִ� �Ÿ� ���� �迭
int distance[MAX_VERTICES];

// ������ �湮�Ǿ����� ���θ� �����ϴ� �迭
int found[MAX_VERTICES];

// ���� ���� �Լ�: u���� v�� weight ����ġ�� ���� ������ �߰�
void insert_edge(GraphType* g, int u, int v, int w) {
    Node* node = (Node*)malloc(sizeof(Node)); // ���ο� ��� ���� �Ҵ�
    node->vertex = v;     // ���� ���� ��ȣ ����
    node->weight = w;     // ����ġ ����
    node->next = g->adj[u]; // ���� u�� ���� ����Ʈ�� ����
    g->adj[u] = node;     // ����Ʈ ��带 �� ���� ����
}

// ���� �湮���� ���� ���� �� ���� ���� distance ���� ���� ���� ����
int choose(int distance[], int n, int found[]) {
    int min = INT_MAX;    // �ּҰ��� ã�� ���� �ʱⰪ ����
    int minpos = -1;      // �ּ� ��ġ �ε��� ����
    for (int i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i]; // �� ���� ���� ã���� ����
            minpos = i;
        }
    }
    return minpos; // �ּ� �Ÿ� ���� ��ȯ
}

// ���� ���¸� ����ϴ� ����� �Լ�
void print_status(GraphType* g) {
    static int step = 1;  // �ܰ躰 ��¿� ����
    printf("STEP %d:\n", step++);

    // �Ÿ� �迭 ���
    printf(" distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF)
            printf("  * ");  // ���Ѵ�� *�� ǥ��
        else
            printf("%3d ", distance[i]); // ���ĵ� ���� ���
    }

    // �湮 ���� �迭 ���
    printf("\n found:    ");
    for (int i = 0; i < g->n; i++)
        printf("%3d ", found[i]);
    printf("\n\n");
}

// Dijkstra �ִ� ��� �˰��� (���� ����Ʈ ���)
void shortest_path(GraphType* g, int start) {
    // �Ÿ� �� �湮 �迭 �ʱ�ȭ
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;   // ��� �Ÿ��� ���Ѵ�� �ʱ�ȭ
        found[i] = FALSE;    // �湮 ���� �ʱ�ȭ
    }

    distance[start] = 0;     // ���� ������ �Ÿ� 0���� ����

    // ������ ����ŭ �ݺ�
    for (int i = 0; i < g->n; i++) {
        print_status(g);     // ���� ���� ���

        int u = choose(distance, g->n, found); // �ּ� �Ÿ� ���� ����
        found[u] = TRUE;      // ���õ� ������ �湮 ó��

        // ���õ� ���� u�� ��� ���� ������ ���� �Ÿ� ���� �õ�
        for (Node* p = g->adj[u]; p != NULL; p = p->next) {
            int v = p->vertex; // ���� ���� ��ȣ
            if (!found[v] && distance[u] + p->weight < distance[v]) {
                distance[v] = distance[u] + p->weight; // �Ÿ� ����
            }
        }
    }
}

// main �Լ�: �׷��� ���� �� �ִ� ��� ����
int main(void) {
    GraphType g;
    g.n = 7; // ������ ���� ����

    // ���� ����Ʈ �ʱ�ȭ
    for (int i = 0; i < g.n; i++)
        g.adj[i] = NULL;

    insert_edge(&g, 0, 1, 50); insert_edge(&g, 0, 2, 45); insert_edge(&g, 0, 3, 10);
    insert_edge(&g, 1, 3, 15); insert_edge(&g, 1, 2, 10);
    insert_edge(&g, 2, 4, 30); 
    insert_edge(&g, 3, 0, 20); insert_edge(&g, 3, 4, 15); 
    insert_edge(&g, 4, 1, 20); insert_edge(&g, 4, 2, 35); 
    insert_edge(&g, 5, 4, 3); 

    shortest_path(&g, 0); // ���� 0���� �����ϴ� �ִ� ��� ���

    return 0; // ���α׷� ����
}
    