#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//=====����ť �ڵ� ����=====
#define MAX_QUEUE_SIZE 5

typedef struct {   // ť�� �� �� ���� ����ü
    int id;
    int arrival_time;
    int service_time;
} element;

typedef struct {   // ť ���¸� �����ϴ� ����ü
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;

// ���� �Լ�
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
    return q->front == q->rear;
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// ���� ť ��� �Լ�
void queue_print(QueueType* q) {
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("�� %d (�����ð�: %d, ���񽺽ð�: %d) | ", q->data[i].id, q->data[i].arrival_time, q->data[i].service_time);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
}

// ���� �Լ�
void enqueue(QueueType* q, element item) {
    if (is_full(q))
        error("ť�� ��ȭ�����Դϴ�.");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q) {
    if (is_empty(q))
        error("ť�� �����Դϴ�");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// ���� �Լ� (Peek)
element peek(QueueType* q) {
    if (is_empty(q))
        error("ť�� ��������Դϴ�");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
//=====����ť �ڵ� �� =====

// ���� ���� �ùķ��̼� ���α׷�
int main(void) {
    int minutes = 60;         // �ùķ��̼� �ð� (60��)
    int total_wait = 0;       // �� ��� �ð�
    int total_customers = 0;  // �� �� ��
    int service_time = 0;     // ���� ���� �ð�
    int service_customer = -1; // ���� ���� ���� ���� ID
    QueueType queue;
    init_queue(&queue);

    srand(time(NULL));

    for (int clock = 0; clock < minutes; clock++) {
        printf("����ð�: %d��\n", clock);

        // �������� ���� ������ Ȯ�� (30% Ȯ���� �� ����)
        if ((rand() % 10) < 3) {
            element customer;
            customer.id = total_customers++;
            customer.arrival_time = clock;
            customer.service_time = rand() % 3 + 1;  // ���� �ð��� 1~3�� ���̷� ���� ����
            enqueue(&queue, customer);
            printf("�� %d�� %d�п� ����. ����ó�� �ð�: %d��\n", customer.id, customer.arrival_time, customer.service_time);
        }

        // ���� ���� �� ó��
        if (service_time > 0) {
            printf("�� %d ���� ó�� ���Դϴ�. ���� �ð�: %d��\n", service_customer, service_time);
            service_time--;
        }
        else {
            // ���� ���� ���� ���ٸ�, ť���� ���� ���� ó��
            if (!is_empty(&queue)) {
                element customer = dequeue(&queue);
                service_customer = customer.id;
                service_time = customer.service_time;
                printf("�� %d�� %d�п� ������ �����մϴ�. ���ð�: %d��\n",
                    customer.id, clock, clock - customer.arrival_time);
                total_wait += clock - customer.arrival_time;
            }
        }

        // ���� ť ���� ���
        queue_print(&queue);
    }

    // �ùķ��̼� ���� �� ��� ���
    printf("��ü ���ð�: %d��\n", total_wait);
    return 0;
}

