#include <stdio.h>      // ǥ�� ����� �Լ� ����� ���� ��� ����
#include <stdlib.h>     // ���� �޸� �Ҵ�� exit �Լ� ����� ���� ��� ����

typedef int element;    // element Ÿ���� int�� ���� (�ڷ��� ���� �� ���ϰ� ��� ����)

// ť�� ��带 �����ϴ� ����ü
typedef struct QueueNode {
    element data;               // ť�� ������ ������
    struct QueueNode* link;    // ���� ��带 ����Ű�� ������
} QueueNode;

// ���� ť�� �����ϴ� ����ü (front, rear �����ͷ� ����)
typedef struct {
    QueueNode* front, * rear;  // ť�� ��(front)�� ��(rear)�� ����Ű�� ������
} LinkedQueueType;

// ť�� �ʱ�ȭ�ϴ� �Լ�
void init(LinkedQueueType* q) {
    q->front = q->rear = NULL; // front�� rear�� NULL�� �ʱ�ȭ
}

// ť�� ����ִ��� Ȯ���ϴ� �Լ�
int is_empty(LinkedQueueType* q) {
    return (q->front == NULL); // front�� NULL�̸� ť�� ����ִ� ����
}

// ť�� ���� á���� Ȯ���ϴ� �Լ�
int is_full(LinkedQueueType* q) {
    return 0; // ���� ����Ʈ ��� ť�� �޸𸮰� ����ϴ� �� ������ Ȯ�� �����ϹǷ� �׻� 0 ��ȯ
}

// ť�� �����͸� �����ϴ� �Լ�
void enqueue(LinkedQueueType* q, element data) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode)); // �� ��� ���� ����
    temp->data = data;       // �� ��忡 ������ ����
    temp->link = NULL;       // �� ����� ��ũ�� NULL�� ���� (������ ����̹Ƿ�)

    if (is_empty(q)) {       // ť�� ����ִٸ�
        q->front = q->rear = temp; // front�� rear�� ��� �� ��带 ����Ű���� ����
    }
    else {                   // ť�� ������� �ʴٸ�
        q->rear->link = temp; // ���� rear�� �� ��带 ����Ű���� ����
        q->rear = temp;       // rear�� �� ���� ����
    }
}

// ť���� �����͸� �����ϰ� ��ȯ�ϴ� �Լ�
element dequeue(LinkedQueueType* q) {
    QueueNode* temp = q->front; // ������ ��带 �ӽ÷� ����
    element data;

    if (is_empty(q)) {         // ť�� ���������
        fprintf(stderr, "ť�� �������\n"); // ���� �޽��� ���
        exit(1);               // ���α׷� ����
    }

    data = temp->data;         // ������ ����� �����͸� ����
    q->front = q->front->link; // front�� ���� ���� �̵�

    if (q->front == NULL)      // ���� �� ť�� ����ٸ�
        q->rear = NULL;        // rear�� NULL�� ����

    free(temp);                // ������ ��� �޸� ����
    return data;               // ������ ������ ��ȯ
}

// ť�� ��� ��Ҹ� ����ϴ� �Լ�
void print_queue(LinkedQueueType* q) {
    QueueNode* p;

    for (p = q->front; p != NULL; p = p->link) // front���� rear���� ��ȸ
        printf("%d -> ", p->data);             // �� ����� ������ ���

    printf("NULL\n");                          // �������� NULL�� ���
}

// ���� �Լ�
int main(void) {
    LinkedQueueType queue;     // ť ����ü ���� ����

    init(&queue);              // ť �ʱ�ȭ

    enqueue(&queue, 1); print_queue(&queue); // 1 ���� �� ���
    enqueue(&queue, 2); print_queue(&queue); // 2 ���� �� ���
    enqueue(&queue, 3); print_queue(&queue); // 3 ���� �� ���
    dequeue(&queue); print_queue(&queue);    // 1 ���� �� ���
    dequeue(&queue); print_queue(&queue);    // 2 ���� �� ���
    dequeue(&queue); print_queue(&queue);    // 3 ���� �� ���

    return 0; // ���α׷� ����
}
