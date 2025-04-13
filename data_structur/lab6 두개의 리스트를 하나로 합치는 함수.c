#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct ListNode
{
	element data;
	struct ListNode* link;
}ListNode;

//오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);	//오류 메시지 출력
	exit(1);		//나가는 함수 -> 프로그램 종료
}

//맨 앞에 추가
ListNode* insert_first(ListNode* head, element value)		//(포인터, 값)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));		//동적메모리에 ListNode 할당
	p->data = value;		//data에 value값 넣기
	p->link = head;			//주소값 head변경
	head = p;
	return head;
}

//리스트 출력
void print_list(ListNode* head)
{
	ListNode* p = head;  // 리스트의 첫 번째 노드를 가리키는 포인터
	while (p != NULL)  // 리스트가 끝날 때까지 반복
	{
		printf("%d->", p->data);  // 현재 노드의 데이터를 출력
		p = p->link;  // 다음 노드를 가리킴
	}
	printf("NULL\n");  // 리스트의 끝을 나타내는 NULL 출력
}

//리스트 연결
ListNode* concat_list(ListNode* head1, ListNode* head2)
{
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else {
		ListNode* p;
		p = head1;
		while (p->link != NULL)
			p = p->link;
		p->link = head2;
		return head1;
	}
}
//테스트 프로그램
int main(void)
{
	ListNode* head1 = NULL;
	ListNode* head2 = NULL;

	head1 = insert_first(head1, 10);
	head1 = insert_first(head1, 15);
	head1 = insert_first(head1, 20);

	print_list(head1);

	head2 = insert_first(head2, 300);
	head2 = insert_first(head2, 140);

	print_list(head2);

	ListNode* total = concat_list(head1, head2);
	print_list(total);
	return 0;
}