// ���� ť ���α׷� - ������ ũ�⸦ ���� �迭�� �̿��� ť ����
#include <stdio.h>      // ǥ�� ����� �Լ� ����� ���� ���
#include <stdlib.h>     // exit() �Լ��� ���� ���

// ť�� �ִ� ũ�� ���� (�迭 ũ��)
#define MAX_QUEUE_SIZE 5

// ť�� ����� �ڷ����� int�� ����
typedef int element;

// ť ����ü ����
typedef struct {
	int front;                      // front: �����͸� ���� ��ġ
	int rear;                       // rear: �����͸� ���� ��ġ
	element data[MAX_QUEUE_SIZE];   // ť �����͸� ������ �迭
} QueueType;

// ���� ó�� �Լ�: �޽��� ��� �� ���α׷� ����
void error(char* message)
{
	fprintf(stderr, "%s\n", message);  // ���� �޽����� stderr�� ���
	exit(1);                           // ������ ����
}

// ť �ʱ�ȭ �Լ�: front�� rear�� -1�� ������ �� ���·� �ʱ�ȭ
void init_queue(QueueType* q)
{
	q->rear = -1;
	q->front = -1;
}

// ť ���¸� ����ϴ� �Լ� (ť ��ü �迭�� ������)
void queue_print(QueueType* q)
{
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		if (i <= q->front || i > q->rear)   // ť�� ��ȿ ���� ���̸� ����ִ� ĭ ǥ��
			printf("|");                    // �� ĭ
		else
			printf("%d | ", q->data[i]);    // ť�� ����ִ� ������ ���
	}
	printf("\n");  // �� �ٲ�
}

// ť�� ���� á���� Ȯ���ϴ� �Լ�
int is_full(QueueType* q)
{
	if (q->rear == MAX_QUEUE_SIZE - 1)  // rear�� �迭�� ������ �ε����� �����ϸ� ��ȭ
		return 1;
	else
		return 0;
}

// ť�� ������� Ȯ���ϴ� �Լ�
int is_empty(QueueType* q)
{
	if (q->front == q->rear)  // front�� rear�� ������ ť�� ��� ����
		return 1;
	else
		return 0;
}

// ť�� �����͸� �߰��ϴ� �Լ�
void enqueue(QueueType* q, int item)
{
	if (is_full(q)) {                   // ť�� ���� ���� ���� �߻�
		error("ť�� ��ȭ�����Դϴ�.");
		return;
	}
	q->data[++(q->rear)] = item;       // rear�� ������Ű�� �ش� ��ġ�� ������ ����
}

// ť���� �����͸� ������ �Լ�
int dequeue(QueueType* q)
{
	if (is_empty(q)) {                 // ť�� ������� ���� �߻�
		error("ť�� �����Դϴ�");
		return -1;
	}
	int item = q->data[++(q->front)];  // front�� ������Ű�� �ش� ��ġ�� ������ ��ȯ
	return item;
}

// ���� �Լ�: ť�� ����/������ �׽�Ʈ
int main(void)
{
	int item = 0;         // ���� �����͸� ������ ����
	QueueType q;          // ť ���� ����

	init_queue(&q);       // ť �ʱ�ȭ

	// ť�� ������ ���� �� ���� ���
	enqueue(&q, 10); queue_print(&q);  // 10 �߰�
	enqueue(&q, 20); queue_print(&q);  // 20 �߰�
	enqueue(&q, 30); queue_print(&q);  // 30 �߰�

	// ť���� ������ ���� �� ���� ���
	item = dequeue(&q); queue_print(&q);  // 10 ����
	item = dequeue(&q); queue_print(&q);  // 20 ����
	item = dequeue(&q); queue_print(&q);  // 30 ����

	return 0;  // ���α׷� ���� ����
}
	