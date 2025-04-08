#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX 100

//큐를 위한 구조체
typedef struct {
	char items[MAX];
	int front;
	int rear;
}Queue;

//큐 초기화
void initQueue(Queue* q) {
	q->front = 0;
	q->rear = -1;
}

//큐가 비어있는지 확인
int is_empty(Queue* q) {
	return q->rear < q->front;
}
//큐에 삽입
void enqueue(Queue* q, char ch) {
	if (q->rear < MAX - 1) {
		q->items[++(q->rear)] = ch;
	}
}
//큐에서 방출
char dequeue(Queue* q) {
	if (!is_empty(q)) {
		return q->items[(q->front)++];
	}
	return '\0';		// 큐가 비어 있으면 잘못된 값을 반환
}

//회문 판별 함수
int is_palindrome(const char* str) {
	Queue q;
	initQueue(&q);

	//문자열을 큐에 넣기(대소문자 구분 없음, 공백 제거)
	for (int i = 0; str[i] != '\0'; i++) {
		if (isalnum(str[i])) {		//isalnum 알파벳 또는 숫자이면 0이 아닌 값을 반환한다
			enqueue(&q, tolower(str[i]));	//소문자로 변형
		}
	}
	//큐의 앞과 뒤를 비교하여 회문 판별
	for (int i = 0; i < (q.rear - q.front + 1) / 2; i++) {
		if (dequeue(&q) != dequeue(&q)) {		//queue앞과 뒤의 문자를 각각 꺼내서 비교한다
			return 0;	//회문이 아니면 0 반환
		}
	}
	return 1;	//회문이면 1 반환
}

int main() {
	char str[MAX];
	printf("문자열을 입력하세요: ");
	fgets(str, sizeof(str), stdin);		//stdin 표준입력
	str[strcspn(str, "\n")] = '\0'; //개행문자 제거

	if (is_palindrome(str)) {
		printf("회문입니다.\n");
	}
	else {
		printf("회문이 아닙니다.\n");
	}
	return 0;
}