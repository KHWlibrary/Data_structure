#include<stdio.h>
#include<stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {			//큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}DequeType;

//오류함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//초기화
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
//공백 상태 검출 함수
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}

//포화 상태 검출 함수
int is_full(DequeType* q)
{
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

//원형큐 출력 함수
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

//삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

//삭제 함수