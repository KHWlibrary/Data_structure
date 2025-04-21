#include <stdio.h>  //printf함수에 쓰임
#include <stdlib.h> //malloc, free, exit함수에 쓰임

typedef int element;    //element를 int형으로 사용할 수 있게함

// 연결 리스트 노드 정의
typedef struct ListNode {
    element data;   //노드에 data값 저장
    struct ListNode* link;  //다음 노드를 가리키는 포인터
} ListNode; //구조체 이름

// 리스트를 출력하는 함수
void print_list(ListNode* head) {
    if (head == NULL) return;   //head에 비어있으면 아무것도 출력하지 않고 종료

    ListNode* p = head; //현재 노드를 가리키는 포인터 ,head에서부터 시작한다
    do {
        printf("%d -> ", p->data);  //현재 데이터 출력
        p = p->link;                //다음 노드로 이동
    } while (p != head);    //다시 head로 돌아올때 까지 반복, 원형 리스트임을 알 수 있다.
    printf("(head)\n");     // 순환 끝 표시
}

// 맨 앞에 삽입하는 함수
ListNode* insert_ListNode(ListNode* head, element data) {   
    ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));  // 새 노드 동적 메모리 할당
    if (newnode == NULL) {     //메모리 할당 실패시  에러 메시지 출력
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);        //종료
    }
    newnode->data = data;  //새 노드에 데이터값 저장

    if (head == NULL) {
        // 첫 노드인 경우 자기 자신을 가리킴
        newnode->link = newnode;  //자기 자신을 가리키는 원형리스트
        head = newnode;        //head가 새 노드를 가리키게함
    }
    else {
        // 새 노드를 head 다음에 삽입
        newnode->link = head->link;    //새 노드가 기존 첫 번째 노드를 가리킴
        head->link = newnode;          //기존 마지막 노드가 새 노드를 가리킴
    }
    return head;  // 변경된 head 반환
}

// 리스트에서 데이터를 가진 노드를 찾는 함수
ListNode* search_ListNode(ListNode* head, element data) {
    if (head == NULL) return NULL;  //head값이 NULL이면 NULL반환

    ListNode* p = head;     //head에서부터 찾기 시작
    do {
        if (p->data == data)
            return p;  // 찾은 경우 해당 노드 반환
        p = p->link;    //다음 노드로 이동
    } while (p != head);

    return NULL;  // 못 찾은 경우 NULL반환
}

// 원형 연결 리스트의 모든 노드를 해제하는 함수
void free_list(ListNode* head) {
    if (head == NULL) return;  // 리스트가 비어 있으면 바로 종료

    ListNode* p = head->link;  // 두 번째 노드부터 시작 
    ListNode* temp;

    while (p != head) {
        temp = p;          // 현재 노드를 임시로 저장
        p = p->link;       // 다음 노드로 이동
        free(temp);        // 현재 노드 메모리 해제
    }

    free(head);  // 마지막으로 head 노드 해제
}

// 메인 함수
int main(void) {
    ListNode* head = NULL;      //head 포인터 NULL로 초기화

    // 노드 삽입 (맨 앞에 삽입)
    head = insert_ListNode(head, 1);        //1삽입
    head = insert_ListNode(head, 2);        //2삽입
    head = insert_ListNode(head, 3);        //3삽입
    head = insert_ListNode(head, 4);        //4삽입
    head = insert_ListNode(head, 5);        //5삽입

    // 리스트 출력
    printf("원형 연결 리스트 출력:\n");
    print_list(head);  

    // search 테스트
    element key = 3; //찾는 값: 3
    ListNode* found = search_ListNode(head, key);
    if (found != NULL) {
        printf("노드 %d를 찾았습니다:", key);   //찾으면 출력
    }
    else {
        printf("노드 %d는 리스트에 없습니다.\n", key); //못 찾으면 출력
    }
    free_list(head); //모든 메모리 해제
    return 0;   //프로그램 종료
}
