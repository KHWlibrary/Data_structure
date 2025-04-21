#define _CRT_SECURE_NO_WARNINGS // Visual Studio���� scanf ���� ��� ����
#include<stdio.h>               // ǥ�� ����� �Լ�
#include<stdlib.h>              // exit() �� ǥ�� ���̺귯�� �Լ�

//===== ���� ť �ڵ� ���� =====
#define MAX_QUEUE_SIZE 5        // ť�� �ִ� ũ�⸦ 5�� ����

typedef int element;            // ť�� ������ Ÿ���� int�� ����

// ���� ť ����ü ����
typedef struct {
	int front;                  // ť�� �պκ� �ε��� (�����͸� ������ ��)
	int rear;                   // ť�� �޺κ� �ε��� (�����͸� �ִ� ��)
	element data[MAX_QUEUE_SIZE];  // ť ������ ����� �迭
} QueueType;

// ���� �޽����� ����ϰ� ���α׷� �����ϴ� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message); // ���� �޽����� stderr�� ���
	exit(1);                          // ������ ����
}

// ť�� �ʱ�ȭ�ϴ� �Լ� (front�� rear�� 0���� ����)
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// ť�� ������� �˻��ϴ� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear); // front�� rear�� ������ ť�� �������
}

// ť�� ���� á���� �˻��ϴ� �Լ�
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
	// rear�� �� ĭ �� ���� front�� ������ ���� ��
}

// ť�� ������ ����ϴ� �Լ�
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;               // front���� ����
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;  // �ε��� ���� (���� �����̹Ƿ� ������ ����)
			printf("%d | ", q->data[i]);  // ���� ��ġ�� �� ���
		} while (i != q->rear);         // rear���� ���
	}
	printf("\n");
}

// ť�� �����͸� �����ϴ� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q))                 // ť�� ���� á�ٸ� ���� �߻�
		error("ť�� ��ȭ�����Դϴ�.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // rear�� �� ĭ �̵�
	q->data[q->rear] = item;       // �ش� ��ġ�� item ����
}

// ť���� �����͸� ������ �Լ�
int dequeue(QueueType* q)
{
	if (is_empty(q))               // ť�� ��� �ִٸ� ���� �߻�
		error("ť�� �����Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; // front�� �� ĭ �̵�
	return q->data[q->front];     // �̵��� ��ġ�� ������ ��ȯ
}

// ť�� ù ��° �����͸� Ȯ���ϴ� �Լ� (������ ���� ����)
element peek(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE]; // ���� front ��ġ�� ������ ��ȯ
}

// ť�� �����ϴ� �������� ������ ����ؼ� ��ȯ�ϴ� �Լ�
int get_count(QueueType* q)
{
	if (q->front <= q->rear)
		return q->rear - q->front; // front �ڿ� rear�� �ִٸ� �׳� ��
	else
		return MAX_QUEUE_SIZE - (q->front - q->rear); // �������� ���ư� ���
}

// ���� �Լ�: ť�� ����� ���԰� ���� �׽�Ʈ
int main(void)
{
	QueueType queue;     // ť ���� ����
	int input;           // ����ڷκ��� �Է¹��� ��

	init_queue(&queue);  // ť �ʱ�ȭ
	printf("--- ������ �߰� �ܰ� ---\n");

	// ť�� ���� �� ������ ������ ����
	while (!is_full(&queue)) {
		printf("������ �Է��Ͻÿ�: ");
		scanf("%d", &input);         // ����ڷκ��� ���� �Է�
		enqueue(&queue, input);      // ť�� ����
		queue_print(&queue);         // ���� ť ���� ���
	}
	printf("ť�� ��ȭ�����Դϴ�\n\n");

	// ť�� �����ϴ� ��� ���� ���
	printf("���� ť�� ��� �ִ� ������ ����: %d\n", get_count(&queue));

	printf("\n--- ������ ���� �ܰ� ---\n");
	// ť�� �� ������ �����͸� ����
	while (!is_empty(&queue)) {
		input = dequeue(&queue);     // ������ ����
		printf("������ ����: %d\n", input);
		queue_print(&queue);         // ���� ť ���� ���
	}
	printf("ť�� ��������Դϴ�.\n");

	// ť�� ������ ������� �� ������ ���� Ȯ��
	printf("���� ť�� ��� �ִ� ������ ����: %d\n", get_count(&queue));

	return 0; // ���α׷� ���� ����
}
