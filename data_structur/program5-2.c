#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>

//=====원형큐 코드 시작=====
#define MAX_QUEUE_SIZE 5
 
typedef int element;
typedef struct {		//큐 타입
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
}QueueType;					//큐타입 구조체 큐 상태를 저장하는 구조체 큐에 저장된 데이터 배열에 저장됩니다

//오류함수
void error(char *message)
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
	printf("---데이터 추가 단계---\n");
	while (!is_full(&queue))
	{
		printf("정수를 입력하시오: ");
		scanf("%d", &element);
		enqueue(&queue, element);
		queue_print(&queue);
	}
	printf("큐는 포화상태입니다\n\n");

	printf("-----데이터 삭제 단계-----\n");
	while (!is_empty(&queue))
	{
		element = dequeue(&queue);
		printf("꺼내진 정수: %d \n", element);
		queue_print(&queue);
	}
	printf("큐는 공백상태 입니다.\n");
	return 0;
}