#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DoubleListNode {
	element data;
	struct DoubleListNode* prev;
	struct DoubleListNode* next;
} DoubleListNode;

// 이중 연결 리스트 초기화
void init(DoubleListNode* pointhead) {
	pointhead->prev = pointhead;
	pointhead->next = pointhead;
}

// 리스트 출력
void print_dlist(DoubleListNode* pointhead) {
	DoubleListNode* p;
	for (p = pointhead->next; p != pointhead; p = p->next) {
		printf("<-| |%d| |->", p->data);
	}
	printf("\n");
}

// 노드 삽입 (before 노드 오른쪽에)
void insert_dlist(DoubleListNode* before, element data) {
	DoubleListNode* newnode = (DoubleListNode*)malloc(sizeof(DoubleListNode));
	newnode->data = data;
	newnode->prev = before;
	newnode->next = before->next;
	before->next->prev = newnode;
	before->next = newnode;
}

// 값 탐색
DoubleListNode* search(DoubleListNode* head, element found) {
	DoubleListNode* p = head->next;
	while (p != head) {  //
		if (p->data == found)
			return p;
		p = p->next;
	}
	return NULL;
}

// 메모리 해제
void free_list(DoubleListNode* head) {
	if (head == NULL) return;
	DoubleListNode* p = head->next;
	DoubleListNode* temp;
	while (p != head) {
		temp = p;
		p = p->next;
		free(temp);
	}
	free(head);
}

int main(void) {
	//헤드 노드 메모리 동적 할당 및 초기화
	DoubleListNode* head = (DoubleListNode*)malloc(sizeof(DoubleListNode));
	init(head);

	// head 기준으로 삽입 (head 오른쪽에 삽입됨)
	insert_dlist(head, 1);
	insert_dlist(head, 2);
	insert_dlist(head, 3);
	insert_dlist(head, 4);
	insert_dlist(head, 5);

	print_dlist(head);

	element key = 2;
	DoubleListNode* found = search(head, key);
	if (found != NULL) {
		printf("노드 %d를 찾았습니다.\n", key);
	}
	else {
		printf("노드 %d는 리스트에 없습니다.\n", key);
	}

	free_list(head);
	return 0;
}
