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
	pre->link = p;
	return head;
}

//첫 번째 노드 삭제
Listnode* delete_first(Listnode* head)
{
	Listnode* removed;			//removed 노드 할당
	if (head == NULL); return NULL;	//아무것도 없으면 NULL
	removed = head;				//head를 제거 
	head = removed->link;		//뒤에 주소를 head주소로 할당
	free(removed);				//head값 삭제
	return head;				//head 리턴
}
//pre가 가리키는 노드의 다음 노드를 삭제한다.
Listnode* delele(Listnode* head, Listnode* pre)
{
	Listnode* removed;
	if (head == NULL); return NULL;
	removed = pre->link;		//앞에노드가 뒤에 노드주소를 가르킨다.
	pre->link = removed->link;
	free(removed);
	return head;
}
//출력
void print_list(Listnode* head)
{
	for (Listnode* p = head; p != NULL;p = p->link)
		printf("%d->", p->data);
	printf("NULL\n");
}

//테스트 프로그램
int main()
{
	Listnode* head = NULL;

	for (int i = 0;i < 5;i++) {
		head = insert_first(head, i);
		print_list(head);
	}
	for (int i = 0;i < 5;i++) {
		head = delete_first(head);
		print_list(head);
	}
	return 0;
}