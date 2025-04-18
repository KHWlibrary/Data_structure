#define MAX_LIST_SIZE 100	//리스트의 최대크기
#include<stdio.h>
#include<stdlib.h>

typedef int element;		//항목의 정리
typedef struct
{
	element array[MAX_LIST_SIZE];	//배열 정의
	int size;
}ArrayListType;

//오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//리스트 초기화 함수
void init(ArrayListType* L)
{
	L->size = 0;
}
//리스트가 가득 차 있으면 1을 반환
//그렇지 않으면 0을 반환
int is_full(ArrayListType* L)
{
	return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	return L->array[pos];
}

//리스트 출력
void print_list(ArrayListType* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("\n");
}
//항목 추가 연산
void insert_last(ArrayListType* L, element item)
{
	if (L->size >= MAX_LIST_SIZE) {
		error("리스트 오버플로우");
	}
	L->array[L->size++] = item;
}
//항목 추가되어 기존에 있는 항목들 하나씩 이동
void insert(ArrayListType* L, int pos, element item)
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = (L->size - 1); i >= pos; i--)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;
		L->size++;
	}
}
//항목 삭제 연산
element delete(ArrayListType* L, int pos)
{
	element item;

	if (pos < 0 || pos >= L->size)
		error("위치오류");
	item = L->array[pos];
	for (int i = pos; i < (L->size - 1); i++)
		L->array[i] = L->array[i + 1];
	L->size--;
	return item;
}

int main(void)
{
	ArrayListType list;

	init(&list);
	insert(&list, 0, 10); print_list(&list);	//0번째 위치에 10추가
	insert(&list, 0, 20); print_list(&list);	//0번째 위치에 20추가
	insert(&list, 0, 30); print_list(&list);	//0번째 위치에 30추가
	insert(&list, 0, 40); print_list(&list);	//0번째 위치에 40추가
	insert_last(&list, 50); print_list(&list);	//맨 끝에 50추가
	return 0;
}