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
	fprint(stderr, "%s\n", message);
	exit(1);
}

//맨 앞에 추가
ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode);
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

//리스트 출력
ListNode* print_list(ListNode* head)
{
	for (ListNode* p; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL\n");
}
