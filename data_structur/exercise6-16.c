//단순 연결 리스트의 헤드 포인터가 주어져 있을 때 첫 번째 노드에서부터 하나씩 건너서 있는
//노드를 전부 삭제하는 함수를 작성하라. 즉 홀수번째 있는 노드들이 전부 삭제된다.
#include<stdio.h>
#include<stdlib.h>

typedef struct LinkNode
{
	int data;
	struct LinkNode* link;
}LinkNode;

//노드추가

LinkNode *insert_node(LinkNode* head, int value)
{
	LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
	p->data = value;
	p->link = head;
	head = p;

	return head;
}
//홀수번째 노드 삭제
LinkNode* delete_odd(LinkNode* head)
{
	if (head == NULL || head->link == NULL) {
		return head;	//첫 번째 노드나 두 번째 노드가 없으면 삭제할 노드가 없음
	}
	LinkNode* temp = head;
	LinkNode* prev = NULL;

	//첫 번째 노드 건너 뛰고 두 번째 노드부터
	temp = temp->link;
	head = temp;	//두 번째 노드를 head로 설정

	//홀수번째 노드 삭제
	while (temp != NULL && temp->link != NULL)
	{
		prev = temp;
		temp = temp->link->link;	//두칸 건너 뛰기
		prev->link = temp;			//이전노드가 현재 노드를 가리키게함	
	}
	return head;
}
//출력
void print_list(LinkNode* head) {
	LinkNode* temp = head;
	while (temp != NULL) {
		printf("%d -> ", temp->data);
		temp = temp->link;
	}
	printf("NULL\n");
}

// 메모리 free 함수
void free_list(LinkNode* head) {
	LinkNode* temp;
	while (head != NULL) {
		temp = head;
		head = head->link;
		free(temp);
	}
}

int main(void)
{
	LinkNode* head = NULL;
	head = insert_node(head, 1);
	head = insert_node(head, 2);
	head = insert_node(head, 3);
	head = insert_node(head, 4);
	head = insert_node(head, 5);
	head = insert_node(head, 6);
	head = insert_node(head, 7);
	head = insert_node(head, 8);

	printf("변경전 리스트 : \n");
	print_list(head);

	head = delete_odd(head);

	printf("변경후 리스트 : \n");
	print_list(head);

	//메모리 해제
	free_list(head);

	return 0;
}