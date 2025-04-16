#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct ListNode		//노드 타입
{
	element data;			
	struct ListNode* link;	//노드 연결 매개체
}ListNode;

//리스트 항목 출력
void print_list(ListNode* head)
{
	ListNode* p;

	if (head == NULL) return;	//head값이 없으면 그냥 리턴
	p = head->link;				//
	do {						//
		printf("%d->", p->data);//while문 하기전에 일단 먼저 1회 출력
		p = p->link;			//
	} while (p != head);		//
	printf("%d", p->data);		//마지막 노드 출력
}

//맨 앞에 삽입
ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode *)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		// 리스트가 비어있는 경우: 새 노드를 자기 자신으로 연결하고 head로 설정
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;	// (1)새 노드가 기존 첫 번째 노드를 가리키도록 설정 
		head->link = node;			// (2)마지막 노드가 새로운 노드를 가리키도록 설정
	}
	return head;	//변경된 헤드 포인터 반환
}

//맨 뒤 삽입
ListNode* insert_last(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));		//node 새로운 노드
	node->data = data;
	if (head == NULL) {
		// 리스트가 비어있는 경우: 새 노드를 자기 자신으로 연결하고 head로 설정
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link; //(1) 새 노드가 첫 번째 노드를 가르키도록 설정
		head->link = node;		//(2)기존 마지막 노드가 새로운 노드를 가르킴
		head = node;			//(3)head를 새노드로 갱신
	}
	return head;	//변경도니 헤드 포인터 반환
}
//원형 연결 리스트 테스트 프로그램

int main(void)
{
	ListNode* head = NULL;

	//list 10->20->30->40
	head = insert_first(head, 20);
	head = insert_last(head, 30);
	head = insert_last(head, 40);
	head = insert_first(head, 10);

	print_list(head);
	return 0;
}