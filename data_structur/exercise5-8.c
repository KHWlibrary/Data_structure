#define _CRT_SECURE_NO_WARNINGS // Visual Studio에서 scanf 보안 경고 제거
#include<stdio.h>               // 표준 입출력 함수
#include<stdlib.h>              // exit() 등 표준 라이브러리 함수

//===== 원형 큐 코드 시작 =====
#define MAX_QUEUE_SIZE 5        // 큐의 최대 크기를 5로 지정

typedef int element;            // 큐의 데이터 타입을 int로 설정

// 원형 큐 구조체 정의
typedef struct {
	int front;                  // 큐의 앞부분 인덱스 (데이터를 꺼내는 쪽)
	int rear;                   // 큐의 뒷부분 인덱스 (데이터를 넣는 쪽)
	element data[MAX_QUEUE_SIZE];  // 큐 데이터 저장용 배열
} QueueType;

// 오류 메시지를 출력하고 프로그램 종료하는 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message); // 에러 메시지를 stderr에 출력
	exit(1);                          // 비정상 종료
}

// 큐를 초기화하는 함수 (front와 rear를 0으로 설정)
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// 큐가 비었는지 검사하는 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear); // front와 rear가 같으면 큐는 비어있음
}

// 큐가 가득 찼는지 검사하는 함수
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
	// rear가 한 칸 더 가면 front를 만나면 가득 참
}

// 큐의 내용을 출력하는 함수
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;               // front부터 시작
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;  // 인덱스 증가 (원형 구조이므로 나머지 연산)
			printf("%d | ", q->data[i]);  // 현재 위치의 값 출력
		} while (i != q->rear);         // rear까지 출력
	}
	printf("\n");
}

// 큐에 데이터를 삽입하는 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q))                 // 큐가 가득 찼다면 오류 발생
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // rear를 한 칸 이동
	q->data[q->rear] = item;       // 해당 위치에 item 삽입
}

// 큐에서 데이터를 꺼내는 함수
int dequeue(QueueType* q)
{
	if (is_empty(q))               // 큐가 비어 있다면 오류 발생
		error("큐가 공백입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; // front를 한 칸 이동
	return q->data[q->front];     // 이동한 위치의 데이터 반환
}

// 큐의 첫 번째 데이터를 확인하는 함수 (삭제는 하지 않음)
element peek(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE]; // 다음 front 위치의 데이터 반환
}

// 큐에 존재하는 데이터의 개수를 계산해서 반환하는 함수
int get_count(QueueType* q)
{
	if (q->front <= q->rear)
		return q->rear - q->front; // front 뒤에 rear가 있다면 그냥 뺌
	else
		return MAX_QUEUE_SIZE - (q->front - q->rear); // 원형으로 돌아간 경우
}

// 메인 함수: 큐를 사용해 삽입과 삭제 테스트
int main(void)
{
	QueueType queue;     // 큐 변수 선언
	int input;           // 사용자로부터 입력받을 값

	init_queue(&queue);  // 큐 초기화
	printf("--- 데이터 추가 단계 ---\n");

	// 큐가 가득 찰 때까지 데이터 삽입
	while (!is_full(&queue)) {
		printf("정수를 입력하시오: ");
		scanf("%d", &input);         // 사용자로부터 정수 입력
		enqueue(&queue, input);      // 큐에 삽입
		queue_print(&queue);         // 현재 큐 상태 출력
	}
	printf("큐는 포화상태입니다\n\n");

	// 큐에 존재하는 요소 개수 출력
	printf("현재 큐에 들어 있는 데이터 개수: %d\n", get_count(&queue));

	printf("\n--- 데이터 삭제 단계 ---\n");
	// 큐가 빌 때까지 데이터를 꺼냄
	while (!is_empty(&queue)) {
		input = dequeue(&queue);     // 데이터 꺼냄
		printf("꺼내진 정수: %d\n", input);
		queue_print(&queue);         // 현재 큐 상태 출력
	}
	printf("큐는 공백상태입니다.\n");

	// 큐가 완전히 비워졌을 때 데이터 개수 확인
	printf("현재 큐에 들어 있는 데이터 개수: %d\n", get_count(&queue));

	return 0; // 프로그램 정상 종료
}
