// 선형 큐 프로그램 - 정적인 크기를 가진 배열을 이용한 큐 구현
#include <stdio.h>      // 표준 입출력 함수 사용을 위한 헤더
#include <stdlib.h>     // exit() 함수를 위한 헤더

// 큐의 최대 크기 정의 (배열 크기)
#define MAX_QUEUE_SIZE 5

// 큐에 저장될 자료형을 int로 정의
typedef int element;

// 큐 구조체 정의
typedef struct {
	int front;                      // front: 데이터를 꺼낼 위치
	int rear;                       // rear: 데이터를 넣을 위치
	element data[MAX_QUEUE_SIZE];   // 큐 데이터를 저장할 배열
} QueueType;

// 에러 처리 함수: 메시지 출력 후 프로그램 종료
void error(char* message)
{
	fprintf(stderr, "%s\n", message);  // 에러 메시지를 stderr로 출력
	exit(1);                           // 비정상 종료
}

// 큐 초기화 함수: front와 rear를 -1로 설정해 빈 상태로 초기화
void init_queue(QueueType* q)
{
	q->rear = -1;
	q->front = -1;
}

// 큐 상태를 출력하는 함수 (큐 전체 배열을 보여줌)
void queue_print(QueueType* q)
{
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		if (i <= q->front || i > q->rear)   // 큐의 유효 범위 밖이면 비어있는 칸 표시
			printf("|");                    // 빈 칸
		else
			printf("%d | ", q->data[i]);    // 큐에 들어있는 데이터 출력
	}
	printf("\n");  // 줄 바꿈
}

// 큐가 가득 찼는지 확인하는 함수
int is_full(QueueType* q)
{
	if (q->rear == MAX_QUEUE_SIZE - 1)  // rear가 배열의 마지막 인덱스에 도달하면 포화
		return 1;
	else
		return 0;
}

// 큐가 비었는지 확인하는 함수
int is_empty(QueueType* q)
{
	if (q->front == q->rear)  // front와 rear가 같으면 큐가 비어 있음
		return 1;
	else
		return 0;
}

// 큐에 데이터를 추가하는 함수
void enqueue(QueueType* q, int item)
{
	if (is_full(q)) {                   // 큐가 가득 차면 오류 발생
		error("큐가 포화상태입니다.");
		return;
	}
	q->data[++(q->rear)] = item;       // rear를 증가시키고 해당 위치에 데이터 삽입
}

// 큐에서 데이터를 꺼내는 함수
int dequeue(QueueType* q)
{
	if (is_empty(q)) {                 // 큐가 비었으면 오류 발생
		error("큐가 공백입니다");
		return -1;
	}
	int item = q->data[++(q->front)];  // front를 증가시키고 해당 위치의 데이터 반환
	return item;
}

// 메인 함수: 큐의 삽입/삭제를 테스트
int main(void)
{
	int item = 0;         // 꺼낸 데이터를 저장할 변수
	QueueType q;          // 큐 변수 선언

	init_queue(&q);       // 큐 초기화

	// 큐에 데이터 삽입 후 상태 출력
	enqueue(&q, 10); queue_print(&q);  // 10 추가
	enqueue(&q, 20); queue_print(&q);  // 20 추가
	enqueue(&q, 30); queue_print(&q);  // 30 추가

	// 큐에서 데이터 제거 후 상태 출력
	item = dequeue(&q); queue_print(&q);  // 10 제거
	item = dequeue(&q); queue_print(&q);  // 20 제거
	item = dequeue(&q); queue_print(&q);  // 30 제거

	return 0;  // 프로그램 정상 종료
}
	