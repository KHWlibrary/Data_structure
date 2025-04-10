#include <stdio.h>
#include<stdlib.h>

//=====원형큐 코드 시작=====
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {		//큐 타입
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
}QueueType;

//오류함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//공백 상태 검출 함수
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	return(q->front == q->rear);
}

//포화 상태 검출 함수
int is_full(QueueType* q)
{
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

//원형큐 출력 함수
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->rear);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

//삽입함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[(q->rear)] = item;
}
//삭제함수
int dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
//삭제 함수
element peek(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
//======원형큐 코드 끝 =========

int main(void)
{
	QueueType queue;
	int element;
	init_queue(&queue);
	srand(time(NULL));

	for (int i = 8; i < 100; i++) {
		if (rand() % 5 == 0) {		//5로 나누어 떨어지면
			enqueue(&queue, rand() % 100);
		}
		queue_print(&queue);
		if (rand() % 10 == 0) {		//10으로 나누어 떨어지면
			int data = dequeue(&queue);
		}
		queue_print(&queue);
	}
	return 0;
}