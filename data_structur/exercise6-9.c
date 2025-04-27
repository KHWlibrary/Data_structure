//단순 연결리스트
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LIST_SIZE 100    // 리스트의 최대 크기 정의
#include <stdio.h>
#include <stdlib.h>

typedef int element;         // 리스트에 저장될 항목 타입 정의

// 배열 리스트 구조체 정의
typedef struct
{
	element array[MAX_LIST_SIZE];  // 데이터를 저장할 배열
	int size;                      // 현재 리스트에 저장된 항목 수
} ArrayListType;

// 오류 발생 시 메시지를 출력하고 프로그램 종료
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 리스트 초기화 함수
void init(ArrayListType* L)
{
	L->size = 0;  // 항목 개수를 0으로 설정
}

// 리스트가 가득 찼는지 확인
// 가득 차 있으면 1, 아니면 0 반환
int is_full(ArrayListType* L)
{
	return L->size == MAX_LIST_SIZE;
}

// 리스트에서 주어진 위치(pos)의 항목을 반환
element get_entry(ArrayListType* L, element pos)
{
	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	return L->array[pos];
}

// 리스트의 모든 항목을 출력
void print_list(ArrayListType* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("NULL\n");  // 리스트 끝 표시
}

// 리스트의 마지막에 항목을 추가
void insert_last(ArrayListType* L, element item)
{
	if (L->size >= MAX_LIST_SIZE) {
		error("리스트 오버플로우");  // 최대 크기를 초과할 경우 오류
	}
	L->array[L->size++] = item;  // 마지막에 항목 추가 후 size 증가
}

// 지정한 위치(pos)에 항목(item)을 삽입
// 삽입 위치 이후의 항목들은 한 칸씩 뒤로 이동
void insert(ArrayListType* L, int pos, element item)
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = (L->size - 1); i >= pos; i--)  // 뒤에서부터 한 칸씩 밀기
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;  // 지정된 위치에 새 항목 삽입
		L->size++;             // 항목 개수 증가
	}
}

// 지정한 위치(pos)의 항목을 삭제하고 그 값을 반환
element delete(ArrayListType* L, int pos)
{
	element item;

	if (pos < 0 || pos >= L->size)
		error("위치 오류");  // 잘못된 위치에 접근하면 오류 처리

	item = L->array[pos];  // 삭제할 항목 저장
	for (int i = pos; i < (L->size - 1); i++)  // 뒤 항목들을 앞으로 이동
		L->array[i] = L->array[i + 1];

	L->size--;  // 항목 개수 감소
	return item;  // 삭제된 항목 반환
}

// 메인 함수 - 리스트 생성 및 사용자 입력 테스트
int main(void)
{
	ArrayListType list;  // 리스트 변수 선언
	init(&list);         // 리스트 초기화

	int count, data;
	int i;

	printf("노드의 개수: ");
	scanf("%d", &count);  // 추가할 노드 수 입력

	// 사용자가 입력한 만큼 데이터를 리스트에 추가
	for (i = 0; i < count; i++)
	{
		printf("노드 #%d 데이터 : ", i + 1);
		scanf("%d", &data);
		insert_last(&list, data);  // 리스트 끝에 데이터 추가
	}

	// 최종 리스트 출력
	printf("생성된 배열리스트: ");
	print_list(&list);

	return 0;
}
