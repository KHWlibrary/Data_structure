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