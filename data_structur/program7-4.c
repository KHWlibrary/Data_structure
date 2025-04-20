#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char element[100];		//최대99자리 저장할 수 있다.
typedef struct ListNode			//노드 구조체 정의
{
	element data;		//저장장소
	struct ListNode* link;	// 다음노드를 가르킬 포인터
}ListNode;

//첫 번째 삽입 함수
ListNode* insert_first(ListNode* head, element data) //head는 첫 번째 노드를 가르키는 포인터,data는 새로운 노드에 추가할 값
{
	ListNode* node = (ListNode*) malloc(sizeof(ListNode));	//node에 동적 메모리 할당
	//head가 비어있으면
	if (node == NULL)
	{
		fprintf(stderr, "메모리 할당 오류\n");
		exit(1);
	}
	strcpy_s(node->data, sizeof(node->data), data);  // data 값을 노드에 복사
	if (head == NULL)
	{  
		node->link = node;      // 자기 자신을 가리키도록 설정 (순환 연결 리스트)
		head = node;            // head에 새 노드를 넣음
	}
	else//head 비어있지 않으면 
	{
		ListNode* temp = head;
		while (temp->link != head) {
			temp = temp->link;
		}
		node->link = head;      // 새 노드의 link는 기존 head를 가리킴
		head = node;            // head를 새 노드로 업데이트
	}
	return head;	//변경된head로 반환
}

int main(void)
{
	ListNode* head = NULL;		//리스트 첫 번째 가르킬 포인터, 처음에는 head를 가르킴

	head = insert_first(head, "KIM");//KIM삽입후 head가 새 노드를 가르킴
	head = insert_first(head, "PARK");//PARK삽입후 head가 새 노드를 가르킴
	head = insert_first(head, "LEE");//LEE삽입후 head가 새 노드를 가르킴

	ListNode* p = head;	//p는 현재 노드를 가르킬 포인터, 처음에는 head를 가르킴 
	int count = 0;		//출력된 노드 숫자를 셈

	//순환 연결리스트를 순차적으로 출력
	do {
		printf("현재 차례 = %s\n", p->data);	//현재 노드의 데이터 출력
		p = p->link;
		count++;
	} while (p != head && count < 3);//p가 head로 돌아올때 까지 그리고3개의 노드를 출력할때까지
	// 동적 할당된 메모리 해제 (필수)
	if (head != NULL) {
		ListNode* current = head->link;
		ListNode* temp = NULL;
		while (current != head) {
			temp = current;
			current = current->link;
			free(temp);
		}
		free(head);
		head = NULL;
	}

	return 0;
}

