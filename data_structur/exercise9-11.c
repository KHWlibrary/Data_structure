#include<stdio.h>      // 표준 입출력 함수 사용을 위한 헤더
#include<stdlib.h>     // malloc, free 등 동적 메모리 관련 함수 사용
#include<string.h>     // 문자열 함수 (strcspn 등) 사용

// 해야 할 일과 우선순위를 담을 구조체 정의
typedef struct {
    char list[30];     // 해야 할 일 내용을 저장하는 문자열 (최대 29자 + '\0')
    int priority;      // 일의 우선순위 (작을수록 우선순위 높음)
} element;

// 최소 힙(우선순위 큐)을 구현하기 위한 구조체 정의
typedef struct {
    element heap[50];  // 최대 50개의 요소 저장 가능
    int heap_size;     // 현재 힙에 저장된 요소의 개수
} Heap;

// 힙 구조체를 동적으로 생성하고 그 주소를 반환
Heap* create()
{
    return (Heap*)malloc(sizeof(Heap));  // Heap 구조체만큼 메모리 할당
}

// 힙을 초기화 (요소 개수 0으로 설정)
void init(Heap* h)
{
    h->heap_size = 0;
}

// 힙에 새로운 요소(item)를 삽입하는 함수
void insert_heap(Heap* h, element item)
{
    int i;
    i = ++(h->heap_size);   // 새 요소를 삽입할 위치 (힙 크기 증가)

    // 부모 노드와 우선순위를 비교하며 위로 올라감 (작을수록 우선)
    while ((i != 1) && (item.priority < h->heap[i / 2].priority)) {
        h->heap[i] = h->heap[i / 2]; // 부모 노드를 아래로 내림
        i /= 2;                      // 인덱스를 부모로 이동
    }
    h->heap[i] = item;              // 새 요소 삽입
}

// 힙에서 우선순위가 가장 높은요소 삭제 및 반환
element delete_heap(Heap* h)
{
    int parent, child;      //int와 element차이는 int는 단순히 정수형을 의미하는 것이고,
    element item, temp;     //element는 위에 구조체를 형성해서 만들어진 것 이다.

    item = h->heap[1];              // 루트 노드가 가장 우선순위 높은 요소
    temp = h->heap[(h->heap_size)--]; // 마지막 요소를 temp에 저장하고 힙 크기 감소
    parent = 1;
    child = 2;

    // 자식 노드들과 우선순위를 비교하며 아래로 내려감
    while (child <= h->heap_size) {
        // 두 자식 중 우선순위가 더 높은 자식을 선택
        if ((child < h->heap_size) && (h->heap[child].priority > h->heap[child + 1].priority))
            child++;

        // temp가 자식보다 우선순위 높으면 멈춤
        if (temp.priority <= h->heap[child].priority) break;

        // 자식을 부모 위치로 올림
        h->heap[parent] = h->heap[child];
        parent = child;             // 한 단계 아래로 이동
        child *= 2;                 // 왼쪽 자식 인덱스로 이동
    }

    h->heap[parent] = temp;         // 적절한 위치에 temp 삽입
    return item;                    // 삭제한 요소 반환
}

// 사용자에게 가능한 명령어를 알려주는 함수
void help()
{
    printf("삽입(i), 삭제(d), 종료(q): ");
}

int main(void)
{
    Heap* heap;                     // 힙을 가리킬 포인터 선언
    heap = create();                // 힙 생성, 동적 메모리 할당
    init(heap);                     // 힙 초기화
    element e;                      // 사용자 입력을 받을 구조체 변수

    char command = '\0';            // 사용자 명령 초기화

    // 사용자가 종료(q)를 누를 때까지 반복
    while (command != 'q') {
        help();                     // 사용자에게 명령어 안내
        command = getchar();        // 명령어 1글자 입력 받기
        getchar();                  // 엔터(\n) 제거 (버퍼 비우기)

        switch (command)            // 입력된 명령어에 따라 분기
        {
        case 'i':                   // 삽입 명령
            printf("해야할 일: ");
            fgets(e.list, sizeof(e.list), stdin);           // 할 일 문자열 입력,  fget(문자열 저장할 배열, 입력가능한 최대의 길이, 표준입력)
            e.list[strcspn(e.list, "\n")] = '\0';           // 문자열 끝 개행 제거
            printf("우선순위: ");
            scanf_s("%d", &e.priority);                     // 우선순위 숫자 입력
            while (getchar() != '\n');                      // 입력 버퍼 비우기
            insert_heap(heap, e);                           // 힙에 삽입
            break;

        case 'd':                   // 삭제 명령
            if (heap->heap_size == 0) {                     // 힙이 비었는지 확인
                printf("할 일이 없습니다!\n");
                break;
            }
            e = delete_heap(heap);                          // 가장 우선순위 높은 일 제거
            printf("제일 우선순위가 높은 일은 %s\n", e.list); // 제거된 일 출력
            break;
        }
    }
    return 0;                       // 프로그램 종료
}
