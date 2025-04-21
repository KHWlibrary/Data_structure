#include<stdio.h>
#include<stdlib.h>

typedef int element;	//element를 int형으로 사용할 수 있게함
typedef struct ListNode	//연결리스트 노드 구조체 정의
{
	element data;	//data 값 저장
	struct ListNode* link;	//다음 노드를 가리키는 포인터
}ListNode;	//구조체 이름

//리스트의 모든함수를 출력하는 함수
void print_list(ListNode* head)
{
	if (head == NULL) return;	//리스트가 비어있다면 출력하지 않고 종료
	ListNode* p = head;		//현재 노드를 가리키는 포인터, head부터 시작
	do {
		printf("%d", p->data);	//현재 노드 데이터 출력
		p = p->link;	//다음 노드로 이동
	} while (p != head);	//한 바퀴 볼때까지 반복
	printf("(head)\n");	//순환 끝 표시
}

//맨 뒤에 삽입하는 새 노드를 삽입하는 함수
ListNode* insert_last(ListNode* head, element data)
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	newnode->data = data;	//새 노드에 데이터 저장
	
	if (head == NULL) {	//리스트가 비어있으면
		head = newnode;	//head를 새 노드로 설정
		newnode->link = head; //새 노드가 자기 자신을 가리키게 설정
	}
	else
	{
		newnode->link = head->link;	//새 노드가 기존 첫번째 노드를 가리키도록 설정
		head->link = newnode;	//기존 마지막 노드가 새노드를 가리키도록 설정
		head = newnode;	//head를 새 노드로 변경
	}
	return head; //변경된 head로 반환
}

//원형 연결리스트의 모든 노드를 해제하는 함수
void free_list(ListNode* head) {
	if (head == NULL) return;	//리스트가 비어있으면 바로 종료

	ListNode* p = head->link;	//두 번째 노드부터 시작
	ListNode* temp;

	while (p != head) {
		temp = p;	//현재노드를 임시로 저장
		p = p->link;	//다음 노드로 이동
		free(temp);	//현재 노드 메모리 해제
	}
}

//메인함수
int main(void)
{
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	
	int count, data;	//count, data 정수형으로 표현
	int i;
	
	printf("데이터 개수를 입력하세요: ");
	scanf_s("%d", &count);

	for (i = 1; i < count+1; i++) {
		printf("노드#%d의 데이터를 입력하세요: ", i);
		scanf_s("%d", &data);
		head = insert_last(head, data);
	}
	printf("데이터 역순으로 출력: ");
	print_list(head);
	
	free_list(head);
	
	return 0;
}