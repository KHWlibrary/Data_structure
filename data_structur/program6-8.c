//노드값 탐색 알고리즘

#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

//오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//맨 앞에 추가
ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));		//ListNode동적 할당
	p->data = value;	//값 저장
	p->link = head;		//헤드 포인터 값 복사
	head = p;			//헤드 포인터 변경
	return head;
}

//프린트 
void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);			//"%d"는 정수형 출력
	printf("NULL \n");
}

//탐색
ListNode* search_list(ListNode* head, element x)
{
	ListNode* p = head;

	while (p != NULL) {
		if (p->data == x) return p;		//만약 p가 일치하는 값이면 p->data 값으로 리턴
		p = p->link;						//아니면 다음으로 넘어가기
	}
	return NULL; // 탐색 실패
}


//메인 함수
int main(void)
{
	ListNode* head = NULL;

	head = insert_first(head, 30);
	print_list(head);
	head = insert_first(head, 20);
	print_list(head);
	head = insert_first(head, 10);
	print_list(head);

	if (search_list(head, 20) != NULL)
		printf("리스트에서 20을 찾았습니다.\n");
	else
		printf("리스트에서 20을 찾지 못 했습니다. \n");
	return 0;
}