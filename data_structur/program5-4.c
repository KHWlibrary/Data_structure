#include<stdio.h>
#include<stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {			//ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}DequeType;

//�����Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//�ʱ�ȭ
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
//���� ���� ���� �Լ�
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}

//��ȭ ���� ���� �Լ�
int is_full(DequeType* q)
{
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

//����ť ��� �Լ�
void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n")
}

//���� �Լ�
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

//���� �Լ�