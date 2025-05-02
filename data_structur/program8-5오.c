//레벨 순회 프로그램
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//==========원형큐 코드 시작================
// 큐의 최대 크기 정의 (배열 크기)
#define MAX_QUEUE_SIZE 100

typedef TreeNode* element;

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
TreeNode* dequeue(QueueType* q)
{
	if (is_empty(q)) {                 // 큐가 비었으면 오류 발생
		error("큐가 공백입니다");
		return NULL;
	}
	return q->data[++(q->front)];  // front를 증가시키고 해당 위치의 데이터 반환
}

//레벨 순회 함수
void level_order(TreeNode* ptr)
{
	QueueType q;
	init_queue(&q);	//큐 초기화
	if (ptr == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf(" [%d] ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}
//			15
//		4		20
//	  1		  16   25
TreeNode n1 = { 1,NULL,NULL };
TreeNode n2 = { 4,&n1,NULL };
TreeNode n3 = { 16,NULL,NULL };
TreeNode n4 = { 25,NULL,NULL };
TreeNode n5 = { 20,&n3,&n4 };
TreeNode n6 = { 15,&n2,&n5 };
TreeNode* root = &n6;

int main(void)
{
	printf("레벨 순회=");
	level_order(root);
	printf("\n");
	return 0;
}