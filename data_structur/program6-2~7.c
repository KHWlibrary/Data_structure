#include<stdio.h>
#include<stdlib.h>

// 정수형 요소를 저장하는 타입 정의
typedef int element;

// 연결 리스트의 노드 정의
typedef struct Listnode
{
	element data;             // 데이터 필드
	struct Listnode* link;   // 다음 노드를 가리키는 포인터
} Listnode;

// 오류 발생 시 메시지 출력 후 프로그램 종료
void error(char* message)
{
	fprintf(stderr, "%s", message);
	exit(1);
}

// 리스트의 맨 앞에 노드를 삽입하는 함수
Listnode* insert_first(Listnode* head, element data)
{
	Listnode* newnode = (Listnode*)malloc(sizeof(Listnode)); // 새 노드 생성
	newnode->data = data;    // 값 할당
	newnode->link = head;     // 새 노드가 기존 head를 가리키게 함
	head = newnode;           // head를 새 노드로 업데이트
	return head;        // 새로운 head 반환
}

// 지정한 노드(pre) 뒤에 새 노드를 삽입하는 함수
Listnode* insert(Listnode* head, Listnode* pre, element data)
{
	Listnode* newnode = (Listnode*)malloc(sizeof(Listnode)); // 새 노드 생성
	newnode->data = data;        // 값 할당
	newnode->link = pre->link;    // pre가 가리키던 다음 노드를 새 노드가 가리킴
	pre->link = newnode;          // pre는 새 노드를 가리키게 함
	return head;            // head는 그대로 반환
}

// 리스트의 첫 번째 노드를 삭제하는 함수
Listnode* delete_first(Listnode* head)
{
	Listnode* removed;
	if (head == NULL) return NULL; // 리스트가 비어있으면 NULL 반환
	removed = head;          // 삭제할 노드를 지정
	head = removed->link;    // head를 다음 노드로 이동
	free(removed);           // 기존 head 메모리 해제
	return head;             // 새로운 head 반환
}

// pre가 가리키는 노드의 다음 노드를 삭제하는 함수
Listnode* delete_node(Listnode* head, Listnode* pre)
{
	Listnode* removed;
	if (head == NULL) return NULL; // 리스트가 비어있으면 NULL 반환
	removed = pre->link;           // 삭제할 노드는 pre의 다음 노드
	pre->link = removed->link;     // pre는 삭제할 노드의 다음 노드를 가리킴
	free(removed);                 // 삭제할 노드 메모리 해제
	return head;                   // head 그대로 반환
}

// 리스트의 모든 노드를 출력하는 함수
void print_list(Listnode* head)
{
	for (Listnode* p = head; p != NULL; p = p->link)  // 끝(NULL)까지 순회
		printf("%d->", p->data);  // 노드 데이터 출력
	printf("NULL\n");            // 리스트 끝 표시
}

// 메인 함수: 리스트 삽입/삭제 테스트
int main()
{
	Listnode* head = NULL; // 초기 리스트는 비어 있음

	// 값 0부터 4까지 리스트 앞에 삽입
	for (int i = 0; i < 5; i++) {
		head = insert_first(head, i); // 앞에 삽입
		print_list(head);             // 리스트 상태 출력
	}

	// 리스트의 모든 노드를 앞에서부터 삭제
	for (int i = 0; i < 5; i++) {
		head = delete_first(head); // 앞 노드 삭제
		print_list(head);          // 리스트 상태 출력
	}
	return 0;
}
