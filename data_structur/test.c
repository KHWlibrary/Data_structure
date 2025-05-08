#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct {
	int key;
} element;

typedef struct {
	element heap[MAX_ELEMENT]; // heap 배열 선언
	int heap_size;             // 현재 힙에 저장된 요소 수
} HeapType;

// 힙 생성 함수
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// 힙 초기화 함수
void init(HeapType* h) {
	h->heap_size = 0;
}

// 최대 힙에 요소 삽입
void insert_max_heap(HeapType* h, element item) {
	int i = ++(h->heap_size);  // 힙 크기 증가 후 해당 위치부터 시작

	// 트리를 거슬러 올라가면서 부모 노드와 비교
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];  // 부모를 자식으로 내림
		i /= 2;
	}
	h->heap[i] = item;  // 알맞은 위치에 item 삽입
}

// 최대 힙에서 요소 삭제
element delete_max_heap(HeapType* h) {
	int parent = 1, child = 2; 
	element item = h->heap[1];           // 루트 노드 저장
	element temp = h->heap[h->heap_size--]; // 마지막 노드를 임시 저장하고 힙 크기 감소

	// 자식 노드와 비교하면서 재배치
	while (child <= h->heap_size) {
		// 두 자식 중 더 큰 자식 선택
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
			child++;
		}
		// 제자리에 들어가면 반복 종료
		if (temp.key >= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];  // 자식을 부모로 끌어올림
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;  // 최종 위치에 temp 삽입
	return item;
}

int main(void) {
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 }; // 요소 3개 선언
	element e4, e5, e6;
	HeapType* heap;

	heap = create();	// 힙 생성
	init(heap);			// 힙 초기화

	// 요소 삽입
	insert_max_heap(heap, e1);
	insert_max_heap(heap, e2);
	insert_max_heap(heap, e3);

	// 요소 삭제 및 출력
	e4 = delete_max_heap(heap);
	printf("< %d >", e4.key);
	e5 = delete_max_heap(heap);
	printf("< %d >", e5.key);
	e6 = delete_max_heap(heap);
	printf("< %d >\n", e6.key);

	free(heap); // 동적 메모리 해제
	return 0;
}
