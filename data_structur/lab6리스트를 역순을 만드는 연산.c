#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct ListNode
{
	element data;
	struct ListNode* link;
}ListNode;

ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}
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
//리스트 역순으로 만들기
ListNode* reverse(ListNode* head)
{
	//순회 포인터로 p, q, r을 사용
	ListNode* p, * q, * r;

	p = head;		//p는 역순으로 만들 리스트
	q = NULL;		//q는 역순을 만들 노드
	while (p != NULL) {
		r = q;	//r은 역순이 된 리스트.
				//r은 q,q는 p를 차례로 따라간다.
		q = p;
		p = p->link;
		q->link = r;	//q의 링크 방향을 바꾼다
	}
	return q;
}

//테스트 프로그램
int main(void)
{
	ListNode* head1 = NULL;
	ListNode* head2 = NULL;

	head1 = insert_first(head1, 10);
	head1 = insert_first(head1, 20);
	head1 = insert_first(head1, 30);
	print_list(head1);

	head2 = reverse(head1);
	print_list(head2);
	return 0;
}