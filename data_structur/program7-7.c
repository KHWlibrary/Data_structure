#include<stdio.h>
#include<stdlib.h>

typedef int element; // element라는 이름으로 int 자료형을 정의 (코드의 가독성 향상)
typedef struct DoubleListNode	// 이중 연결 리스트 구조체 정의
{
	element data;				// 데이터를 저장할 멤버
	struct DoubleListNode* left_link;  // 왼쪽 노드를 가리킬 포인터
	struct DoubleListNode* right_link; // 오른쪽 노드를 가리킬 포인터
}DoubleListNode;

// 이중 연결 리스트를 초기화하는 함수
void init(DoubleListNode* pointhead)
{
	pointhead->left_link = pointhead;  // 헤드 노드의 왼쪽 링크는 자기 자신을 가리킴 (빈 리스트 상태)
	pointhead->right_link = pointhead; // 헤드 노드의 오른쪽 링크는 자기 자신을 가리킴 (빈 리스트 상태)
}

// 이중 연결 리스트의 모든 노드의 데이터를 출력하는 함수
void print_DoubleList(DoubleListNode* pointhead)
{
	DoubleListNode* p; // 현재 노드를 가리킬 포인터
	// 헤드 노드의 오른쪽 노드부터 시작하여 헤드 노드에 도달할 때까지 순회
	for (p = pointhead->right_link; p != pointhead; p = p->right_link)
	{
		printf("<-| |%d| |->", p->data); // 각 노드의 데이터를 특정 형식으로 출력
	}
	printf("\n"); // 한 줄 출력 후 개행
}

// 주어진 노드 before의 오른쪽에 새로운 데이터(data)를 갖는 노드를 삽입하는 함수
void insert_DoubleNode(DoubleListNode* before, element data)
{
	DoubleListNode* newnode = (DoubleListNode*)malloc(sizeof(DoubleListNode)); // 새로운 노드를 위한 동적 메모리 할당
	newnode->data = data; // 새로운 노드에 데이터 저장
	newnode->left_link = before; // 새로운 노드의 왼쪽 링크는 before 노드를 가리킴
	newnode->right_link = before->right_link; // 새로운 노드의 오른쪽 링크는 before 노드의 원래 오른쪽 노드를 가리킴
	before->right_link->left_link = newnode; // before 노드의 원래 오른쪽 노드의 왼쪽 링크를 새로운 노드로 변경
	before->right_link = newnode; // before 노드의 오른쪽 링크를 새로운 노드로 변경하여 새로운 노드를 연결
}

// 주어진 노드 removed를 이중 연결 리스트에서 삭제하는 함수
void delete_DoubleNode(DoubleListNode* head, DoubleListNode* removed)
{
	if (removed == head) return; // 삭제할 노드가 헤드 노드라면 아무것도 하지 않고 함수 종료
	removed->left_link->right_link = removed->right_link; // 삭제할 노드의 왼쪽 노드의 오른쪽 링크를 삭제할 노드의 오른쪽 노드로 연결
	removed->right_link->left_link = removed->left_link; // 삭제할 노드의 오른쪽 노드의 왼쪽 링크를 삭제할 노드의 왼쪽 노드로 연결
	free(removed); // 삭제된 노드의 동적 메모리 해제
}

// 이중 연결 리스트를 테스트하는 메인 함수
int main(void)
{
	DoubleListNode* head = (DoubleListNode*)malloc(sizeof(DoubleListNode)); // 헤드 노드를 위한 동적 메모리 할당
	init(head); // 헤드 노드를 이용하여 이중 연결 리스트 초기화
	printf("추가 단계\n");
	for (int i = 0; i < 5; i++) {
		// 헤드 노드의 오른쪽에 새로운 노드를 삽입 (결과적으로 리스트의 앞에 추가되는 형태)
		insert_DoubleNode(head, i);
		print_DoubleList(head); // 삽입 후 현재 리스트 상태 출력
	}
	printf("\n삭제 단계\n");
	for (int i = 0; i < 5; i++) {
		print_DoubleList(head); // 삭제 전 현재 리스트 상태 출력
		delete_DoubleNode(head, head->right_link); // 헤드 노드의 오른쪽 노드를 삭제 (결과적으로 리스트의 앞에서부터 삭제)
	}
	free(head); // 프로그램 종료 전 헤드 노드의 동적 메모리 해제
	return 0; // 프로그램 정상 종료
}