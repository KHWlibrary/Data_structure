#define _CRT_SECURE_NO_WARNING
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ListNode
{
	char name[20];
	int age;
	float height;
	struct ListNode* link;
}ListNode;

//리스트 새로운 사람 추가
ListNode* insert(ListNode* head, char* name, int age, double height)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	strcpy_s(p->name, sizeof(p->name), name);
	p->age = age;
	p->height = height;
	p->link = NULL;

	//리스트가 비어있으면 새로운 사람을 첫 번째로 지정
	if (head == NULL) {
		head = p;
	}
	//그렇지 않으면 마지막에 추가
	else
	{
		ListNode* temp = head;
		while (temp->link != NULL)
		{
			temp = temp->link;
		}
		temp->link = p;
	}
	return head;
}
// 내용 출력함수
void print_list(ListNode* head) {
	ListNode* temp = head;
	while (temp != NULL) {
		printf("이름:%s, 나이:%d, 키:%.2f\n", temp->name, temp->age, temp->height);
		temp = temp->link;
	}
}
//메모리 해제함수
void free_list(ListNode* head)
{
	ListNode* temp;
	while (head != NULL) {
		temp = head;
		head = head->link;
		free(temp);
	}
}
//테스트
int main(void)
{
	ListNode* head = NULL;

	//데이터 삽입
	head = insert(head, "김도영", 23, 183.0f);
	head = insert(head, "김선빈", 37, 165.0f);
	head = insert(head, "박찬호", 31, 178.0f);

	//연결리스트 출력
	printf("선수 인적사항:\n");
	print_list(head);

	//연결리스트 메모리헤제
	free_list(head);

	return 0;
}