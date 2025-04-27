//이중 연결 리스트에서 특정한 값을 탐색하는 함수 search()를 작성하고 테스트하는 프로그램
#include <stdio.h>  //printf함수에 쓰임
#include <stdlib.h> //malloc, free, exit함수에 쓰임

typedef int element;
typedef struct DoubleListNode {
	element data;		//노드에 저장할 data값 
	struct DoubleListNode* prev;	//이전 노드 가리키는 포인터
	struct DoubleListNode* next;	//다음 노드 가리키는 포인터
} DoubleListNode;	//구조체 이름

// 이중 연결 리스트 초기화
//헤드 노드는 데이터를 저장하지 않고 리스트 처음과 끝을 연결해주는 역할을 함
void init(DoubleListNode* pointhead) {
	pointhead->prev = pointhead;	//자기 자신을 가리키는 원형리스트, 리스트가 비어있음을 뜻함	
	pointhead->next = pointhead;	//자기 자신을 가리키는 원형리스트, 리스트가 비어있음을 뜻함
}

// 헤드 노드를 제외한 모든 리스트 출력
void print_dlist(DoubleListNode* pointhead) {
	DoubleListNode* p;	//리스트를 순회할 포인터 변수 p선언
	//pointhead->next로 초기화 p가 pointhead가 아니면 p를 다음노들 넘어감
	for (p = pointhead->next; p != pointhead; p = p->next) {	
		printf("<-| |%d| |->", p->data);	//data값 출력
	}
	printf("\n");	//가독성을 높이기 위해 줄 넘김
}

// 이중연결리스트에 새로운 노드 삽입 
//before노드를 오른쪽에 삽입합니다
void insert_dlist(DoubleListNode* before, element data) {
	DoubleListNode* newnode = (DoubleListNode*)malloc(sizeof(DoubleListNode));
	newnode->data = data;	//새 노드에 데이터 값을 저장합니다
	newnode->prev = before;	//새 노드의 이전 노드는 before노드가 된다
	newnode->next = before->next;	//새 노드의 다음노드는 before노드의 다음 노드가 된다
	before->next->prev = newnode;	//before노드의 기존 다음노드의 이전 포인터가 새 노드를 가리키도록 변경한다.
	before->next = newnode; //before노드의 다음포인터가 새노드를 가리키도록 변경한다.
}

// 이중 연결 리스트에서 특정값을 찾는 함수
DoubleListNode* search(DoubleListNode* head, element found) {
	DoubleListNode* p = head->next;	//탐색할 p노드를 헤드 다음 노드로 설정
	//p가 head 같지 않을때까지 반복 같으면 반복문을 빠져나감
	while (p != head) { 
		if (p->data == found)	
			return p;		//만약 data값이 found 값이랑 같으면 p로 리턴값
		p = p->next;
	}
	return NULL;	//반복문을 통해 값을 찾지 못 할 경우 NULL로 리턴
}

// 이중 연결 리스트의 모든 노드의 메모리를 해제하는 함수
void free_list(DoubleListNode* head) {	
	if (head == NULL) return;	//head에 아무것도 없으면 종료
	DoubleListNode* p = head->next;	//삭제할 노드를 head노드의 다음 노드부터 시작하게 둠
	DoubleListNode* temp;	//임시로 저장할 노드
	//p가 head랑 같지 않으면 반복 같으면 반복문을 빠져나옴
	//모든함수를 메모리 해제함
	while (p != head) {	
		temp = p;	//temp에 p값을 넣고
		p = p->next;	//p다음 값을 p 에 넣음
		free(temp);	//temp의 들어간 메모리 해제
	}
	free(head);	//head도 메모리 해제
}

int main(void) {
	//헤드 노드 메모리 동적 할당 및 초기화
	DoubleListNode* head = (DoubleListNode*)malloc(sizeof(DoubleListNode));
	//할당된 head노드를 초기화 시킴
	init(head);

	// head 기준으로 삽입 (head 오른쪽에 삽입됨)
	insert_dlist(head, 1);	//head <-> 1 <-> head
	insert_dlist(head, 2);	//head <-> 2 <-> 1 <-> head
	insert_dlist(head, 3);	//head <-> 3 <-> 2 <-> 1 <-> head
	insert_dlist(head, 4);	//head <-> 4 <-> 3 <-> 2 <-> 1 <-> head
	insert_dlist(head, 5);	//head <-> 5 <-> 4 <-> 3 <-> 2 <-> 1 <-> head

	print_dlist(head);	
	//찾는 값 2
	element key = 2;
	//search함수를 호출하여 키 값 2를 가진 노드를 찾는다. 
	DoubleListNode* found = search(head, key);
	if (found != NULL) {
		printf("노드 %d를 찾았습니다.\n", key);	//찾는 경우
	}
	else {
		printf("노드 %d는 리스트에 없습니다.\n", key);	//못 찾은 경우
	}

	free_list(head); //모든 메모리 해제
	return 0;
}
