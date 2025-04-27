//이중 연결 리스트를 역순으로 순회하면서 저장된 데이터 값을 출력하는 프로그램
#include <stdio.h>  //printf함수에 쓰임
#include <stdlib.h> //malloc, free, exit함수에 쓰임

typedef int element;	//element를 int형으로 사용할 수 있게함
typedef struct ListNode	//연결리스트 노드 구조체 정의
{
	element data;	//노드에 저장할 data 값 
	struct ListNode* link;	//다음 노드를 가리키는 포인터
}ListNode;	//구조체 이름

//리스트의 모든함수를 출력하는 함수
void print_list(ListNode* head)
{
	if (head == NULL) return;	//리스트가 비어있다면 출력하지 않고 종료
	ListNode* p = head;		//현재 노드를 가리키는 포인터, head부터 시작
	//데이터 출력,다음노드 이동은 무조건 1번은 실행됨
	//다음으로 p가 head아니면 실행 head이면 반복문을 빠져나옴
	do {
		printf(" %d ", p->data);	//현재 노드 데이터 출력
		p = p->link;	//다음 노드로 이동
	} while (p != head);	//한 바퀴 볼때까지 반복
}

//맨 앞에 삽입하는 새 노드를 삽입하는 함수
ListNode* insert_first(ListNode* head, element data)
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	if (newnode == NULL) {     //메모리 할당 실패시  에러 메시지 출력
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);        //종료
	}
	newnode->data = data;	//새 노드에 데이터 저장
	
	if (head == NULL) {	//리스트가 비어있으면
		head = newnode;	//head를 새 노드로 설정
		newnode->link = head; //새 노드가 자기 자신을 가리키게 설정
	}
	else
	{
		ListNode* tail = head;	//tail 노드 할당
		while (tail->link != head) {  // 마지막 노드 찾기
			tail = tail->link;	//다음 노드를 가리키는 포인터
		}
		tail->link = newnode;	//마지막 노드가 새 노드를 가리키게 설정
		newnode->link = head;	 //새 노드가 head를 가리킴
		head = newnode; // 새 노드를 head로 지정
	}
	return head; //변경된 head로 반환
}

//원형 연결리스트의 모든 노드를 해제하는 함수
void free_list(ListNode* head) {
	if (head == NULL) return;	//리스트가 비어있으면 바로 종료

	ListNode* p = head->link;	//두 번째 노드부터 시작
	ListNode* temp;

	while (p != head) {
		temp = p;	//현재노드를 임시로 저장
		p = p->link;	//다음 노드로 이동
		free(temp);	//현재 노드 메모리 해제
	}
	free(head);	//마지막으로 head노드 해제
}

//메인함수
int main(void)
{
	ListNode* head = NULL;		//head리스트 초기화

	int count, data;	//count, data 정수형으로 표현
	int i;	//for문에 사용될 변수
	
	printf("데이터 개수를 입력하세요: ");
	scanf_s("%d", &count);		//데이터 개수 입력

	for (i = 1; i < count+1; i++) {
		printf("노드#%d의 데이터를 입력하세요: ", i);
		scanf_s("%d", &data);	//데이터 입력
		head = insert_first(head, data);
	}
	printf("데이터 역순으로 출력: ");
	print_list(head);	//데이터 역순으로 출력
	
	free_list(head);	//모든 메모리 해제
	
	return 0;//프로그램 종료
}