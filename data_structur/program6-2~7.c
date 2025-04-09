#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct Listnode
{
	element data;
	struct Listnode* link;
}Listnode;

//오류처리 함수
void error(char* meassage)
{
	fprintf(stderr, "%s", meassage);
	exit(1);
}
Listnode *insert_first(Listnode *head, int value)
{
	Listnode* p = (Listnode*)malloc(sizeof(Listnode));
	p->data = value;		//값을 할당
	p->link = head;			//주소값을 할당
	head = p;				//헤드 포인트 변경
	return head;			//변경된 헤드 포인트값 반환
}

//노드 pre 뒤에 새로운 노드삽입
Listnode* insert(Listnode* head, Listnode* pre, element value)
{
	Listnode *p = (Listnode*)malloc(sizeof(Listnode));
	p->data = value;
	p->link - pre->link;
	pre->link = pr
}