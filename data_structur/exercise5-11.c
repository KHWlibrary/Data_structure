// 회문 판별 프로그램

#include <stdio.h>     // 표준 입출력 함수
#include <string.h>    // 문자열 처리 함수
#include <ctype.h>     // 문자 검사 및 변환 함수 (ex. isalnum, tolower)

#define MAX 100        // 큐에 저장할 수 있는 최대 문자 수

// 큐 구조체 정의
typedef struct {
	char items[MAX];  // 큐에 저장될 문자 배열
	int front;        // 큐의 시작 인덱스
	int rear;         // 큐의 마지막 인덱스
} Queue;

// 큐 초기화 함수
void initQueue(Queue* q) {
	q->front = 0;     // front는 0
	q->rear = -1;     // rear는 -1로 시작 (비어있는 상태)
}

// 큐가 비었는지 검사
int is_empty(Queue* q) {
	return q->rear < q->front;  // rear가 front보다 작으면 비어 있음
}

// 큐에 문자 삽입
void enqueue(Queue* q, char ch) {
	if (q->rear < MAX - 1) {         // 큐가 가득 차지 않았을 경우에만 삽입
		q->items[++(q->rear)] = ch;  // rear 증가 후 해당 위치에 문자 저장
	}
}

// 큐에서 문자 제거 (앞쪽 요소 반환)
char dequeue(Queue* q) {
	if (!is_empty(q)) {              // 큐가 비어있지 않다면
		return q->items[(q->front)++];  // front 위치의 문자 반환 후 front 증가
	}
	return '\0';                     // 큐가 비어있다면 널 문자 반환
}

// 회문 여부를 검사하는 함수
int is_palindrome(const char* str) {
	Queue q;                         // 큐 선언
	initQueue(&q);                   // 큐 초기화

	// 문자열을 큐에 삽입 (공백 제거, 대소문자 구분 없이 처리)
	for (int i = 0; str[i] != '\0'; i++) {
		if (isalnum(str[i])) {                    // 문자나 숫자만 필터링
			enqueue(&q, tolower(str[i]));         // 모두 소문자로 변환 후 큐에 삽입
		}
	}

	// 큐에서 앞과 뒤의 문자를 꺼내서 비교
	for (int i = 0; i < (q.rear - q.front + 1) / 2; i++) {
		if (dequeue(&q) != dequeue(&q)) {         // 앞에서 두 개를 꺼내 비교 (❗논리상 문제 있음)
			return 0;                             // 다르면 회문이 아님
		}
	}
	return 1;  // 모두 일치하면 회문
}

// 메인 함수
int main() {
	char str[MAX];  // 사용자 입력을 받을 문자열 배열

	printf("문자열을 입력하세요: ");
	fgets(str, sizeof(str), stdin);  // 문자열 입력 받기 (개행 포함)

	str[strcspn(str, "\n")] = '\0';  // 개행 문자 제거 (fgets로 입력 받았을 경우)

	// 회문인지 판별 및 결과 출력
	if (is_palindrome(str)) {
		printf("회문입니다.\n");
	}
	else {
		printf("회문이 아닙니다.\n");
	}
	return 0;
}
