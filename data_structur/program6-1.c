#define MAX_LIST_SIZE 100   // 리스트의 최대 크기 정의 (100개의 요소까지 저장 가능)

#include<stdio.h>           // 표준 입출력 함수 포함
#include<stdlib.h>          // 표준 라이브러리 함수 포함 (exit 등 사용)

// element를 int로 정의하여 코드 가독성 향상
typedef int element;

// 배열 기반 리스트 구조체 정의
typedef struct {
	element array[MAX_LIST_SIZE];  // 데이터를 저장할 배열
	int size;                      // 현재 저장된 데이터의 개수
} ArrayListType;

// 오류 메시지 출력 후 프로그램 종료하는 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);  // 에러 메시지를 표준 에러로 출력
	exit(1);                           // 프로그램 비정상 종료
}

// 리스트를 초기화하는 함수
void init(ArrayListType* L) {
	L->size = 0;  // 리스트 크기를 0으로 설정
}

// 리스트가 가득 찼는지 확인 (가득 찼으면 1, 아니면 0 반환)
int is_full(ArrayListType* L) {
	return L->size == MAX_LIST_SIZE;
}

// 리스트에서 특정 위치의 값을 반환하는 함수
element get_entry(ArrayListType* L, int pos) {
	if (pos < 0 || pos >= L->size)     // 유효하지 않은 위치일 경우
		error("위치 오류");             // 오류 메시지 출력
	return L->array[pos];              // 해당 위치의 값 반환
}

// 리스트의 모든 요소를 출력하는 함수
void print_list(ArrayListType* L) {
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);  // 각 요소를 "숫자->" 형식으로 출력
	printf("\n");
}

// 리스트의 맨 마지막에 항목을 추가하는 함수
void insert_last(ArrayListType* L, element item) {
	if (L->size >= MAX_LIST_SIZE) {       // 리스트가 가득 찼다면
		error("리스트 오버플로우");         // 오류 처리
	}
	L->array[L->size++] = item;           // 마지막 위치에 값 삽입 후 size 증가
}

// 리스트의 특정 위치에 항목을 삽입하는 함수
void insert(ArrayListType* L, int pos, element item) {
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {  // 유효한 위치인지 확인
		for (int i = (L->size - 1); i >= pos; i--)        // 뒤에서부터 한 칸씩 이동
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;     // 지정된 위치에 새 항목 삽입
		L->size++;                // 크기 증가
	}
}

// 리스트의 특정 위치의 항목을 삭제하는 함수
element delete(ArrayListType* L, int pos) {
	element item;

	if (pos < 0 || pos >= L->size)    // 유효하지 않은 위치일 경우
		error("위치오류");             // 오류 처리

	item = L->array[pos];             // 삭제할 항목 저장
	for (int i = pos; i < (L->size - 1); i++)  // 뒤 항목들을 한 칸씩 앞으로 이동
		L->array[i] = L->array[i + 1];
	L->size--;                        // 크기 감소
	return item;                      // 삭제된 항목 반환
}

// 메인 함수: 리스트 사용 예제
int main(void) {
	ArrayListType list;              // 리스트 변수 선언

	init(&list);                     // 리스트 초기화

	insert(&list, 0, 10); print_list(&list);  // 0번 위치에 10 삽입 → [10]
	insert(&list, 0, 20); print_list(&list);  // 0번 위치에 20 삽입 → [20, 10]
	insert(&list, 0, 30); print_list(&list);  // 0번 위치에 30 삽입 → [30, 20, 10]
	insert(&list, 0, 40); print_list(&list);  // 0번 위치에 40 삽입 → [40, 30, 20, 10]

	insert_last(&list, 50); print_list(&list);  // 리스트 맨 끝에 50 추가 → [40, 30, 20, 10, 50]

	return 0;  // 프로그램 종료
}
