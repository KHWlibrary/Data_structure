#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//=====원형큐 코드 시작=====
#define MAX_QUEUE_SIZE 5

typedef struct {   // 큐에 들어갈 고객 정보 구조체
    int id;
    int arrival_time;
    int service_time;
} element;

typedef struct {   // 큐 상태를 관리하는 구조체
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;

// 오류 함수
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
    return q->front == q->rear;
}

// 포화 상태 검출 함수
int is_full(QueueType* q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// 원형 큐 출력 함수
void queue_print(QueueType* q) {
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("고객 %d (도착시간: %d, 서비스시간: %d) | ", q->data[i].id, q->data[i].arrival_time, q->data[i].service_time);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
}

// 삽입 함수
void enqueue(QueueType* q, element item) {
    if (is_full(q))
        error("큐가 포화상태입니다.");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q) {
    if (is_empty(q))
        error("큐가 공백입니다");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 삭제 함수 (Peek)
element peek(QueueType* q) {
    if (is_empty(q))
        error("큐가 공백상태입니다");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
//=====원형큐 코드 끝 =====

// 은행 서비스 시뮬레이션 프로그램
int main(void) {
    int minutes = 60;         // 시뮬레이션 시간 (60분)
    int total_wait = 0;       // 총 대기 시간
    int total_customers = 0;  // 총 고객 수
    int service_time = 0;     // 현재 서비스 시간
    int service_customer = -1; // 현재 서비스 중인 고객의 ID
    QueueType queue;
    init_queue(&queue);

    srand(time(NULL));

    for (int clock = 0; clock < minutes; clock++) {
        printf("현재시각: %d분\n", clock);

        // 랜덤으로 고객이 도착할 확률 (30% 확률로 고객 도착)
        if ((rand() % 10) < 3) {
            element customer;
            customer.id = total_customers++;
            customer.arrival_time = clock;
            customer.service_time = rand() % 3 + 1;  // 서비스 시간은 1~3분 사이로 랜덤 설정
            enqueue(&queue, customer);
            printf("고객 %d이 %d분에 도착. 업무처리 시간: %d분\n", customer.id, customer.arrival_time, customer.service_time);
        }

        // 서비스 중인 고객 처리
        if (service_time > 0) {
            printf("고객 %d 업무 처리 중입니다. 남은 시간: %d분\n", service_customer, service_time);
            service_time--;
        }
        else {
            // 서비스 중인 고객이 없다면, 큐에서 다음 고객을 처리
            if (!is_empty(&queue)) {
                element customer = dequeue(&queue);
                service_customer = customer.id;
                service_time = customer.service_time;
                printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간: %d분\n",
                    customer.id, clock, clock - customer.arrival_time);
                total_wait += clock - customer.arrival_time;
            }
        }

        // 현재 큐 상태 출력
        queue_print(&queue);
    }

    // 시뮬레이션 종료 후 결과 출력
    printf("전체 대기시간: %d분\n", total_wait);
    return 0;
}

