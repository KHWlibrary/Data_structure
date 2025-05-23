#include<stdio.h>      // ǥ�� ����� �Լ� ����� ���� ���
#include<stdlib.h>     // malloc, free �� ���� �޸� ���� �Լ� ���
#include<string.h>     // ���ڿ� �Լ� (strcspn ��) ���

// �ؾ� �� �ϰ� �켱������ ���� ����ü ����
typedef struct {
    char list[30];     // �ؾ� �� �� ������ �����ϴ� ���ڿ� (�ִ� 29�� + '\0')
    int priority;      // ���� �켱���� (�������� �켱���� ����)
} element;

// �ּ� ��(�켱���� ť)�� �����ϱ� ���� ����ü ����
typedef struct {
    element heap[50];  // �ִ� 50���� ��� ���� ����
    int heap_size;     // ���� ���� ����� ����� ����
} Heap;

// �� ����ü�� �������� �����ϰ� �� �ּҸ� ��ȯ
Heap* create()
{
    return (Heap*)malloc(sizeof(Heap));  // Heap ����ü��ŭ �޸� �Ҵ�
}

// ���� �ʱ�ȭ (��� ���� 0���� ����)
void init(Heap* h)
{
    h->heap_size = 0;
}

// ���� ���ο� ���(item)�� �����ϴ� �Լ�
void insert_heap(Heap* h, element item)
{
    int i;
    i = ++(h->heap_size);   // �� ��Ҹ� ������ ��ġ (�� ũ�� ����)

    // �θ� ���� �켱������ ���ϸ� ���� �ö� (�������� �켱)
    while ((i != 1) && (item.priority < h->heap[i / 2].priority)) {
        h->heap[i] = h->heap[i / 2]; // �θ� ��带 �Ʒ��� ����
        i /= 2;                      // �ε����� �θ�� �̵�
    }
    h->heap[i] = item;              // �� ��� ����
}

// ������ �켱������ ���� ������� ���� �� ��ȯ
element delete_heap(Heap* h)
{
    int parent, child;      //int�� element���̴� int�� �ܼ��� �������� �ǹ��ϴ� ���̰�,
    element item, temp;     //element�� ���� ����ü�� �����ؼ� ������� �� �̴�.

    item = h->heap[1];              // ��Ʈ ��尡 ���� �켱���� ���� ���
    temp = h->heap[(h->heap_size)--]; // ������ ��Ҹ� temp�� �����ϰ� �� ũ�� ����
    parent = 1;
    child = 2;

    // �ڽ� ����� �켱������ ���ϸ� �Ʒ��� ������
    while (child <= h->heap_size) {
        // �� �ڽ� �� �켱������ �� ���� �ڽ��� ����
        if ((child < h->heap_size) && (h->heap[child].priority > h->heap[child + 1].priority))
            child++;

        // temp�� �ڽĺ��� �켱���� ������ ����
        if (temp.priority <= h->heap[child].priority) break;

        // �ڽ��� �θ� ��ġ�� �ø�
        h->heap[parent] = h->heap[child];
        parent = child;             // �� �ܰ� �Ʒ��� �̵�
        child *= 2;                 // ���� �ڽ� �ε����� �̵�
    }

    h->heap[parent] = temp;         // ������ ��ġ�� temp ����
    return item;                    // ������ ��� ��ȯ
}

// ����ڿ��� ������ ��ɾ �˷��ִ� �Լ�
void help()
{
    printf("����(i), ����(d), ����(q): ");
}

int main(void)
{
    Heap* heap;                     // ���� ����ų ������ ����
    heap = create();                // �� ����, ���� �޸� �Ҵ�
    init(heap);                     // �� �ʱ�ȭ
    element e;                      // ����� �Է��� ���� ����ü ����

    char command = '\0';            // ����� ��� �ʱ�ȭ

    // ����ڰ� ����(q)�� ���� ������ �ݺ�
    while (command != 'q') {
        help();                     // ����ڿ��� ��ɾ� �ȳ�
        command = getchar();        // ��ɾ� 1���� �Է� �ޱ�
        getchar();                  // ����(\n) ���� (���� ����)

        switch (command)            // �Էµ� ��ɾ ���� �б�
        {
        case 'i':                   // ���� ���
            printf("�ؾ��� ��: ");
            fgets(e.list, sizeof(e.list), stdin);           // �� �� ���ڿ� �Է�,  fget(���ڿ� ������ �迭, �Է°����� �ִ��� ����, ǥ���Է�)
            e.list[strcspn(e.list, "\n")] = '\0';           // ���ڿ� �� ���� ����
            printf("�켱����: ");
            scanf_s("%d", &e.priority);                     // �켱���� ���� �Է�
            while (getchar() != '\n');                      // �Է� ���� ����
            insert_heap(heap, e);                           // ���� ����
            break;

        case 'd':                   // ���� ���
            if (heap->heap_size == 0) {                     // ���� ������� Ȯ��
                printf("�� ���� �����ϴ�!\n");
                break;
            }
            e = delete_heap(heap);                          // ���� �켱���� ���� �� ����
            printf("���� �켱������ ���� ���� %s\n", e.list); // ���ŵ� �� ���
            break;
        }
    }
    return 0;                       // ���α׷� ����
}
