#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char element[100];		//최대99자리 저장할 수 있다.
typedef struct ListNode			//노드 구조체 정의
{
	element data;		//저장장소
	struct Listnode* link;	// 다음노드를 가르킬 포인터
}Listnode;

//첫 번째 삽입 함수
ListNode* insert_first(ListNode* head, element data) //head는 첫 번째 노드를 가르키는 포인터,data는 새로운 노드에 추가할 값
{
	ListNode* node = (Listnode*)malloc(sizeof(ListNode));	//node에 동적 메모리 할당
	//head가 비어있으면
	if (head == NULL)
	{
		head = node;	//head에 노드 넣고
		node->link = head;	//link에 head주소 넣기
	}
	else//head 비어있지 않으면 
	{
		node->link = head->link;//head 주소를 새로운 node에 넣기
		head->link = node;		//
	}
}