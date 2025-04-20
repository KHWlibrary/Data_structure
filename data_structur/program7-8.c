#include<stdio.h>   // 표준 입출력 함수 사용을 위한 헤더 파일
#include<stdlib.h>  // 동적 메모리 할당을 위한 헤더 파일
#include<string.h>  // 문자열 처리 함수 사용을 위한 헤더 파일

// element를 char 배열(문자열)로 정의, 길이는 100
typedef char element[100];

// 이중 연결 리스트의 노드 구조체 정의
typedef struct DoubleListNode
{
	element data;                     // 노드에 저장될 데이터(문자열)
	struct DoubleListNode* left_link;   // 왼쪽(이전) 노드를 가리키는 포인터
	struct DoubleListNode* right_link;  // 오른쪽(다음) 노드를 가리키는 포인터
} DoubleListNode;

// 현재 선택된 노드를 가리키는 전역 포인터
DoubleListNode* current;

// 리스트 헤더 노드 초기화 함수
void init(DoubleListNode* pointhead)
{
	pointhead->left_link = pointhead;  // 왼쪽 포인터가 자기 자신을 가리킴 (원형 구조)
	pointhead->right_link = pointhead; // 오른쪽 포인터도 자기 자신을 가리킴 (원형 구조)
}

// 리스트의 모든 노드를 출력하는 함수
void print_DoubleListNode(DoubleListNode* pointhead)
{
	DoubleListNode* p;
	// 헤더 노드의 오른쪽부터 시작하여 다시 헤더로 돌아올 때까지 반복
	for (p = pointhead->right_link; p != pointhead; p = p->right_link) {
		if (p == current)  // 현재 노드인 경우 표시
			printf("<-| #%s# |->", p->data);
		else               // 그렇지 않으면 일반 출력
			printf("<-| %s |->", p->data);
	}
	printf("\n");  // 줄바꿈
}

// 새 노드를 특정 노드의 오른쪽에 삽입하는 함수
void insert_DoubleListNode(DoubleListNode* before, element data)	//before 기존 노드 표현
{
	// 새 노드를 위한 메모리 할당
	DoubleListNode* newnode = (DoubleListNode*)malloc(sizeof(DoubleListNode));
	// 문자열 복사 (안전하게 크기 명시)
	strcpy_s(newnode->data, sizeof(newnode->data), data);
	// 새 노드의 왼쪽 포인터는 삽입 위치 기준 노드를 가리킴
	newnode->left_link = before;
	// 새 노드의 오른쪽 포인터는 삽입 위치 기준 노드의 다음 노드를 가리킴
	newnode->right_link = before->right_link;
	// 삽입 위치 기준 노드의 다음 노드가 새 노드를 가리키게 함
	before->right_link->left_link = newnode;
	// 삽입 위치 기준 노드의 오른쪽이 새 노드를 가리키게 함
	before->right_link = newnode;
}

// 특정 노드를 리스트에서 제거하는 함수
void delete(DoubleListNode* head, DoubleListNode* removed)
{
	if (removed == head) return; // 헤더 노드는 삭제하지 않음
	// 삭제할 노드의 왼쪽 노드가 삭제할 노드의 오른쪽 노드를 가리키게 함
	removed->left_link->right_link = removed->right_link;
	// 삭제할 노드의 오른쪽 노드가 삭제할 노드의 왼쪽 노드를 가리키게 함
	removed->right_link->left_link = removed->left_link;
	// 삭제할 노드의 메모리 해제
	free(removed);
}

// 메인 함수 - 이중 연결 리스트 테스트
int main(void)
{
	char ch;  // 사용자 입력을 저장할 문자 변수
	// 헤더 노드를 위한 메모리 동적 할당
	DoubleListNode* head = (DoubleListNode*)malloc(sizeof(DoubleListNode));
	// 헤더 노드 초기화
	init(head);

	// 데이터 삽입 (리스트의 맨 앞으로 삽입되므로 역순으로 보일 수 있음)
	insert_DoubleListNode(head, "아니길");
	insert_DoubleListNode(head, "sheesh");
	insert_DoubleListNode(head, "forever");
	insert_DoubleListNode(head, "drip");

	// current 포인터를 첫 번째 실제 노드로 설정
	current = head->right_link;
	// 리스트 출력
	print_DoubleListNode(head);

	// 사용자 입력을 받아 반복 처리
	do {
		printf("\n명령어를 입력하시오(<,>,q): ");  // 명령어 안내
		ch = getchar();  // 사용자 입력 받기

		if (ch == '<') {  // 왼쪽으로 이동
			current = current->left_link;
			if (current == head)  // 헤더에 도달한 경우, 다시 왼쪽(마지막 노드)로 이동
				current = current->right_link;
		}
		else if (ch == '>') {  // 오른쪽으로 이동
			current = current->right_link;
			if (current == head)  // 헤더에 도달한 경우, 다시 오른쪽(첫 노드)로 이동
				current = current->right_link;
		}
		// 리스트 출력 (현재 위치 포함)
		print_DoubleListNode(head);
		getchar();  // 입력 버퍼 정리용 (Enter 처리)
	} while (ch != 'q');  // 'q' 입력 시 종료

	// 헤더 노드 메모리 해제
	free(head);
	return 0;  // 프로그램 종료
}
