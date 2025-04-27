#define _CRT_SECURE_NO_WARNING     // strcpy_s 등 보안 함수 사용 시 경고 무시
#include<stdio.h>                  // 표준 입출력 함수 사용
#include<stdlib.h>                 // 동적 메모리 할당을 위한 malloc, free
#include<string.h>                 // 문자열 함수 사용을 위한 헤더

// 사람 정보를 저장할 노드 구조체 정의
typedef struct ListNode {
	char name[20];                // 이름 (문자열 최대 19자 + 널 문자)
	int age;                      // 나이
	float height;                 // 키
	struct ListNode* link;       // 다음 노드를 가리키는 포인터
} ListNode;

// 연결 리스트에 새로운 노드 추가 함수
ListNode* insert(ListNode* head, char* name, int age, double height)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));  // 새 노드 동적 메모리 할당
	strcpy_s(p->name, sizeof(p->name), name);            // 이름 복사 (보안 함수 사용)
	p->age = age;                                        // 나이 저장
	p->height = height;                                  // 키 저장
	p->link = NULL;                                      // 링크 초기화

	// 연결 리스트가 비어 있는 경우, 새 노드를 head로 설정
	if (head == NULL) {
		head = p;
	}
	// 리스트가 비어 있지 않은 경우, 마지막 노드를 찾아 새 노드를 연결
	else {
		ListNode* temp = head;                           // 순회용 포인터
		while (temp->link != NULL) {                     // 마지막 노드까지 이동
			temp = temp->link;
		}
		temp->link = p;                                  // 마지막 노드의 link에 새 노드 연결
	}
	return head;                                         // 변경된 head 반환
}

// 연결 리스트의 모든 데이터를 출력하는 함수
void print_list(ListNode* head) {
	ListNode* temp = head;                              // 순회용 포인터
	while (temp != NULL) {                              // 리스트 끝까지 순회
		printf("이름:%s, 나이:%d, 키:%.2f\n", temp->name, temp->age, temp->height);
		temp = temp->link;                              // 다음 노드로 이동
	}
}

// 연결 리스트의 모든 노드를 동적 메모리 해제하는 함수
void free_list(ListNode* head)
{
	ListNode* temp;                                     // 임시 포인터
	while (head != NULL) {                              // 노드가 남아 있을 때까지 반복
		temp = head;                                    // 현재 노드 임시 저장
		head = head->link;                              // 다음 노드로 이동
		free(temp);                                     // 현재 노드 메모리 해제
	}
}

// 프로그램 시작 지점
int main(void)
{
	ListNode* head = NULL;                              // 연결 리스트의 시작 포인터 (비어 있음)

	// 선수 정보 삽입
	head = insert(head, "김도영", 23, 183.0f);
	head = insert(head, "김선빈", 37, 165.0f);
	head = insert(head, "박찬호", 31, 178.0f);

	// 리스트 출력
	printf("선수 인적사항:\n");
	print_list(head);

	// 메모리 해제
	free_list(head);

	return 0;                                            // 프로그램 정상 종료
}
