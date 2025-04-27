#include <stdio.h>      // 표준 입출력 함수 사용을 위한 헤더 파일
#include <stdlib.h>     // 동적 메모리 할당과 exit 함수 사용을 위한 헤더 파일

typedef int element;    // element 타입을 int로 정의 (자료형 변경 시 편리하게 사용 가능)

// 큐의 노드를 정의하는 구조체
typedef struct QueueNode {
    element data;               // 큐에 저장할 데이터
    struct QueueNode* link;    // 다음 노드를 가리키는 포인터
} QueueNode;

// 연결 큐를 정의하는 구조체 (front, rear 포인터로 구성)
typedef struct {
    QueueNode* front, * rear;  // 큐의 앞(front)과 뒤(rear)를 가리키는 포인터
} LinkedQueueType;

// 큐를 초기화하는 함수
void init(LinkedQueueType* q) {
    q->front = q->rear = NULL; // front와 rear를 NULL로 초기화
}

// 큐가 비어있는지 확인하는 함수
int is_empty(LinkedQueueType* q) {
    return (q->front == NULL); // front가 NULL이면 큐가 비어있는 상태
}

// 큐가 가득 찼는지 확인하는 함수
int is_full(LinkedQueueType* q) {
    return 0; // 연결 리스트 기반 큐는 메모리가 허용하는 한 무한히 확장 가능하므로 항상 0 반환
}

// 큐에 데이터를 삽입하는 함수
void enqueue(LinkedQueueType* q, element data) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode)); // 새 노드 동적 생성
    temp->data = data;       // 새 노드에 데이터 저장
    temp->link = NULL;       // 새 노드의 링크는 NULL로 설정 (마지막 노드이므로)

    if (is_empty(q)) {       // 큐가 비어있다면
        q->front = q->rear = temp; // front와 rear가 모두 새 노드를 가리키도록 설정
    }
    else {                   // 큐가 비어있지 않다면
        q->rear->link = temp; // 기존 rear가 새 노드를 가리키도록 연결
        q->rear = temp;       // rear를 새 노드로 갱신
    }
}

// 큐에서 데이터를 삭제하고 반환하는 함수
element dequeue(LinkedQueueType* q) {
    QueueNode* temp = q->front; // 삭제할 노드를 임시로 저장
    element data;

    if (is_empty(q)) {         // 큐가 비어있으면
        fprintf(stderr, "큐가 비어있음\n"); // 에러 메시지 출력
        exit(1);               // 프로그램 종료
    }

    data = temp->data;         // 삭제할 노드의 데이터를 저장
    q->front = q->front->link; // front를 다음 노드로 이동

    if (q->front == NULL)      // 삭제 후 큐가 비었다면
        q->rear = NULL;        // rear도 NULL로 설정

    free(temp);                // 삭제한 노드 메모리 해제
    return data;               // 삭제한 데이터 반환
}

// 큐의 모든 요소를 출력하는 함수
void print_queue(LinkedQueueType* q) {
    QueueNode* p;

    for (p = q->front; p != NULL; p = p->link) // front부터 rear까지 순회
        printf("%d -> ", p->data);             // 각 노드의 데이터 출력

    printf("NULL\n");                          // 마지막은 NULL로 출력
}

// 메인 함수
int main(void) {
    LinkedQueueType queue;     // 큐 구조체 변수 선언

    init(&queue);              // 큐 초기화

    enqueue(&queue, 1); print_queue(&queue); // 1 삽입 후 출력
    enqueue(&queue, 2); print_queue(&queue); // 2 삽입 후 출력
    enqueue(&queue, 3); print_queue(&queue); // 3 삽입 후 출력
    dequeue(&queue); print_queue(&queue);    // 1 삭제 후 출력
    dequeue(&queue); print_queue(&queue);    // 2 삭제 후 출력
    dequeue(&queue); print_queue(&queue);    // 3 삭제 후 출력

    return 0; // 프로그램 종료
}
