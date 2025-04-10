#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char name[100];		//문자열 길이 설정
}element;

typedef struct ListNode {		//노드 타입
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
		printf("%s->", p->data.name);			//"%s"는 문자열 출력
	printf("NULL \n");
}

//테스트 프로그램
int main(void)
{
	ListNode* head = NULL;
	element data;

	strcpy(data.name, "APPLE");			//strcpy 문자열 공백까지 하나하나 복사함
	head = insert_first(head, data);
	print_list(head);
	strcpy(data.name, "BANANA");
	head = insert_first(head, data);
	print_list(head)	;
	strcpy(data.name, "ORANGE");
	head = insert_first(head, data);
	print_list(head);
}