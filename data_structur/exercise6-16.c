#include<stdio.h>              // 표준 입출력 함수 사용
#include<stdlib.h>             // malloc, free 등 동적 메모리 관련 함수 사용

// 연결 리스트 노드 구조체 정의
typedef struct LinkNode
{
	int data;                 // 노드에 저장될 데이터
	struct LinkNode* link;   // 다음 노드를 가리키는 포인터
} LinkNode;

// 연결 리스트에 노드를 앞에서부터 추가하는 함수
LinkNode* insert_node(LinkNode* head, int value)
{
	LinkNode* newnode = (LinkNode*)malloc(sizeof(LinkNode));  // 새 노드 동적 할당
	newnode->data = value;                                    // 데이터 값 설정
	newnode->link = head;                                     // 새 노드가 기존 head를 가리키도록 설정
	head = p;                                           // 새 노드를 head로 설정
	return head;                                        // 변경된 head 반환
}

// 홀수 번째 노드를 삭제하는 함수
LinkNode* delete_odd(LinkNode* head)
{
	// 노드가 없거나 하나만 있을 경우 삭제할 노드 없음
	if (head == NULL || head->link == NULL) {
		return head;
	}

	LinkNode* temp = head;       // 순회 포인터 초기화
	LinkNode* prev = NULL;       // 이전 노드를 저장할 포인터

	temp = temp->link;           // 두 번째 노드부터 시작 (첫 번째 노드는 건너뜀)
	head = temp;                 // 두 번째 노드를 새로운 head로 설정

	// 이후 짝수 위치 노드만 연결하면서 홀수 위치 노드는 건너뜀
	while (temp != NULL && temp->link != NULL)
	{
		prev = temp;             // 현재 노드를 prev에 저장
		temp = temp->link->link; // 두 칸씩 건너뜀 (홀수 노드 스킵)
		prev->link = temp;       // prev 노드의 link를 temp로 갱신하여 중간 노드 삭제 효과
	}
	return head;                 // 변경된 head 반환
}

// 연결 리스트를 출력하는 함수
void print_list(LinkNode* head) {
	LinkNode* temp = head;       // 순회 포인터
	while (temp != NULL) {
		printf("%d -> ", temp->data); // 데이터 출력
		temp = temp->link;            // 다음 노드로 이동
	}
	printf("NULL\n");                // 끝 표시
}

// 연결 리스트의 모든 노드를 동적으로 해제하는 함수
void free_list(LinkNode* head) {
	LinkNode* temp;
	while (head != NULL) {
		temp = head;             // 현재 노드를 temp에 저장
		head = head->link;       // 다음 노드로 이동
		free(temp);              // 현재 노드 메모리 해제
	}
}

// main 함수: 프로그램의 시작점
int main(void)
{
	LinkNode* head = NULL;      // 빈 리스트 생성

	// 값들을 앞쪽에 삽입하여 리스트 생성 (역순으로 삽입됨)
	head = insert_node(head, 1);  // head: 1
	head = insert_node(head, 2);  // head: 2 -> 1
	head = insert_node(head, 3);  // head: 3 -> 2 -> 1
	head = insert_node(head, 4);  // ...
	head = insert_node(head, 5);
	head = insert_node(head, 6);
	head = insert_node(head, 7);
	head = insert_node(head, 8);  // 최종 리스트: 8 -> 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1

	printf("변경전 리스트 : \n");
	print_list(head);           // 변경 전 리스트 출력

	head = delete_odd(head);    // 홀수 번째 노드 삭제

	printf("변경후 리스트 : \n");
	print_list(head);           // 변경 후 리스트 출력

	free_list(head);            // 메모리 해제

	return 0;                   // 프로그램 종료
}
