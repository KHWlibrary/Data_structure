#include<stdio.h>
#include<stdlib.h>

typedef int element;	//element를 int형으로 사용할 수 있게함
typedef struct ListNode	//연결리스트 노드 구조체 정의
{
	element data;	//노드에 data값 저장
	struct ListNode* link;	//다음 노드를 가리키는 포인터
}ListNode;	//구조체 이름

//리스트의 모든 항목을 출력하는 항목
void print_list(ListNode* head)
{
	if (head == NULL) return;	//리스트가 비어있다면 출력하지 않고 종료
	ListNode* p = head;		//현재 노드를 가리키는 포인터, head부터 시작
	do {
		printf("%d->", p->data);	//현재 노드 데이터 출력
		p = p->link;	//다음 노드로 이동
	} while (p != head);	//한 바퀴 볼때까지 반복
	printf("(head)\n");	//순환 끝 표시
}
//리스트 맨 앞에 새 노드를 삽입하는 함수
ListNode* insert_first(ListNode* head, element data)
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	if (newnode == NULL)
	{
		fprintf(stderr,"메모리 할당 실패\n");
		exit(1);
	}
	newnode->data = data;  //새 노드에 데이터값 저장

	if (head == NULL)
	{	//첫 노드인 경우 자기 자신을 가르킴
		newnode->link = newnode;	//자기 자신을 가리키는 원형리스트
		head = node;	//head가 새 노드를 가리키게함
	}
	else
	{
		newnode->link = head->link;		//새 노드가 기존 첫 번째 노드를 가리킴
		head->link = newnode;		//기존 노드가 새 노드를 가리킴
	}
	return head;
}

//get_size를 이용해 데이터 개수를 반환하는 함수를 만들자
int get_size(ListNode* head) {
	if (head == NULL) return 0;	//리스트가 비어있다면 0반환
	int count = 0;
	ListNode* p = head;
	do {
		count++;		//1번 순회 할때마다 count 1씩 증가 
		p = p->link;	//다음노드로 이동
	} while (p != head);	//한 바퀴 돌때까지 반복
	return count;
}

// 원형 연결 리스트의 모든 노드를 해제하는 함수
void free_list(ListNode* head) {
	if (head == NULL) return;  // 리스트가 비어 있으면 바로 종료

	ListNode* p = head->link;  // 두 번째 노드부터 시작
	ListNode* temp;

	while (p != head) {
		temp = p;          // 현재 노드를 임시로 저장
		p = p->link;       // 다음 노드로 이동
		free(temp);        // 현재 노드 메모리 해제
	}

	free(head);  // 마지막으로 head 노드 해제
}

//프로그램 실행하는 메인 함수
int main(void)
{
	ListNode* head = NULL;	//head포인터 NULL로 초기화
	int count = 0;//count 값 초기화

	//노드 맨 앞에 삽입
	head = insert_first(head, 20);	//20삽입
	head = insert_first(head, 10);	//10삽입
	head = insert_first(head, 230);	//230삽입
	head = insert_first(head, 5);	//5삽입
	head = insert_first(head, 123);	//123삽입

	//리스트 출력
	printf("원형 연결 리스트 출력:\n");
	print_list(head);

	//데이터 개수 확인
	int size = get_size(head);
	printf("데이터 개수 : %d\n", size);

	free_list(head);	//모든 메모리 해제
	return 0;	//프로그램 종료
}