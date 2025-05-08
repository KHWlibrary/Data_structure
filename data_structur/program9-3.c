#include<stdio.h>      // 표준 입출력 함수 사용을 위한 헤더
#include<stdlib.h>     // malloc, free 등의 동적 메모리 함수 사용을 위한 헤더

#define MAX_ELEMENT 200   // 히프에 저장할 수 있는 최대 요소 수 정의

// 힙에 저장할 요소 구조체 정의
typedef struct {
	int key;   // 우선순위(키 값)
} element;

// 히프 구조체 정의
typedef struct {
	element heap[MAX_ELEMENT];  // 요소들을 저장할 배열
	int heap_size;              // 현재 히프에 저장된 요소의 개수
} HeapType;

// 히프를 생성하는 함수 (동적 메모리 할당)
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));  // HeapType 크기만큼 메모리 할당 후 포인터 반환
}

// 히프를 초기화하는 함수
void init(HeapType* h)
{
	h->heap_size = 0;   // 히프 크기를 0으로 초기화
}

// 최대 히프에 요소를 삽입하는 함수
void insert_max_heap(HeapType* h, element item)
{
	int i = ++(h->heap_size);  // 히프 크기를 1 증가시키고, 그 인덱스를 i에 저장

	// 삽입할 위치를 찾기 위해 트리를 위로 올라가며 부모 노드와 비교
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];  // 부모 노드를 자식 위치로 내려보냄
		i /= 2;                       // i를 부모 인덱스로 이동
	}
	h->heap[i] = item;  // 적절한 위치에 삽입할 item을 저장
}

// 최대 히프에서 루트 요소를 삭제하는 함수
element delete_max_heap(HeapType* h) {
	int parent = 1;               // 부모 노드 인덱스 시작 위치
	int child = 2;                // 자식 노드 인덱스 시작 위치
	element item = h->heap[1];    // 루트 노드를 item에 저장 (삭제할 노드)
	element temp = h->heap[h->heap_size--];  // 마지막 노드를 temp에 저장 후 히프 크기 감소

	// 히프 속성을 유지하기 위해 아래로 내려가며 재배치
	while (child <= h->heap_size) {
		// 왼쪽 자식과 오른쪽 자식 중 더 큰 값을 가진 자식 노드를 선택
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
			child++;  // 오른쪽 자식이 더 크면 오른쪽 자식 선택
		}
		// temp가 자식보다 크거나 같으면 자리를 찾은 것 → 루프 종료
		if (temp.key >= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];  // 더 큰 자식 노드를 부모 위치로 끌어올림
		parent = child;                    // 한 단계 아래로 이동
		child *= 2;                        // 자식 노드 인덱스를 다시 설정
	}
	h->heap[parent] = temp;  // 적절한 위치에 temp 삽입하여 히프 속성 복구
	return item;             // 삭제된 루트 노드 반환
}

// 프로그램 실행 진입점
int main(void)
{
	// 삽입할 요소 3개 생성
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };
	element e4, e5, e6;   // 삭제 후 반환될 요소 저장용
	HeapType* heap;       // 히프 구조체 포인터 선언

	heap = create();	  // 히프 동적 생성
	init(heap);			  // 히프 초기화

	// 요소 삽입 (최대 히프 구성)
	insert_max_heap(heap, e1);  // 10 삽입
	insert_max_heap(heap, e2);  // 5 삽입
	insert_max_heap(heap, e3);  // 30 삽입

	// 요소 삭제 (최대 값부터 차례로 삭제)
	e4 = delete_max_heap(heap);    // 가장 큰 값(30) 삭제
	printf("< %d >", e4.key);      // 출력: < 30 >
	e5 = delete_max_heap(heap);    // 다음 큰 값(10) 삭제
	printf("< %d >", e5.key);      // 출력: < 10 >
	e6 = delete_max_heap(heap);    // 다음 값(5) 삭제
	printf("< %d >\n", e6.key);    // 출력: < 5 >

	free(heap);  // 동적 메모리 해제
	return 0;    // 프로그램 종료
}
