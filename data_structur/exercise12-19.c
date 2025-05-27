#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 10

int sorted[MAX_SIZE];	//추가 공간이 필요

// i는 정렬된 왼쪽 리스트에 대한 인덱스
// j는 정렬된 오른쪽 리스트에 대한 인덱스
// k는 정렬된 리스트에 대한 인덱스
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	// 분할 정렬된 list의 합병

	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i > mid)	//남아 있는 레코드의 일괄 복사
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else//남아 있는 레코드의 일괄 복사
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
}
//
void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2;	//리스트의 균등 분할
		merge_sort(list, left, mid);	//부분 리스트 정렬
		merge_sort(list, mid + 1, right);	//부분 리스트 정렬
		merge(list, left, mid, right);	//합병
		printf("호출된 merge sort: (%d, %d)\n", left, right);
	}
}

int main(void)
{
	int list[MAX_SIZE] = { 10,20,40,50,29,48,59,28,73,91 };
	int i;

	printf("정렬 전 배열: \n");
	for (i = 0; i < MAX_SIZE; i++)
		printf("%d ", list[i]);
	printf("\n");

	merge_sort(list, 0, MAX_SIZE - 1);


	//정렬된 결과를 원래 배열에 복사
	for (i = 0; i < MAX_SIZE; i++)
		list[i] = sorted[i];
	printf("정렬 후 배열: \n");
	for (i = 0; i < MAX_SIZE; i++)
		printf("%d ", list[i]);
	printf("\n");

	return 0;
	
}
