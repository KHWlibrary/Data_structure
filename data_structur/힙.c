#include<stdio.h>
#include<stdlib.h>

typedef struct heap
{
	int* arr;	//힙 메모리(배열)의 주소 저장
	int size;	//저장된 원소의 개수
	int capacity;	//힙(배열)의 최대 용량
}Heap;

void createHeap(Heap* php, int count)	//힙 생성
{
	php->arr = (int*)malloc(sizeof(int) * count);
	php->size = 0;
	php->capacity = count;
}

void shiftup(int* arr, int childindex)
{
	int temp;
	int parentindex = (childindex - 1) / 2;

	if (parentindex >= 0 && arr[parentindex] < arr[childindex])
	{
		temp = arr[parentindex];
		arr[parentindex] = arr[childindex];
		arr[childindex] = temp;

		shiftup(arr, parentindex);
	}
}

void addHeap(Heap* php, int value)	//힙 추가
{
	if (php->capacity == php->size)	//최대용량 == 저장개수
	{
		printf("메모리가 가득차있습니다, 더이상 저장할 수 없습니다.");
		return;
	}
	php->arr[php->size] = value;
	shiftup(php->arr, php->size);	//shift up - 자식노드 입장에서 부모 노드와 비교
	php->size++;
}

void displayHeap(Heap* php)
{
	int i;
	printf("Heap display: ");

	for (i = 0; i < php->size; i++)
		printf("%d ", php->arr[i]);
	printf("\n");
}

void shiftdown(int* arr,int parentindex, int size)
{
	int leftindex = 2 * parentindex + 1;
	int rightindex = leftindex + 1;
	int largeindex = -1;	//배열의 인덱스로 쓸 수 없는 값(0~size - 1)
	int temp;

	if(leftindex < size)	// left인덱스가 size보다 작아야함
		largeindex = leftindex;

	if (rightindex < size && arr[largeindex] < arr[rightindex])	//right인덱스가 size보다 작아야함
		largeindex = rightindex;

	if (largeindex != -1 && arr[largeindex] > arr[parentindex])
	{
		//두 개의 값을 교환
		temp = arr[largeindex];
		arr[largeindex] = arr[parentindex];
		arr[parentindex] = temp;

		return shiftdown(arr, largeindex, size);	//재귀호출 : largeindex가 parentindex가 되며 재귀호출한다
	}
}

int extractMax(Heap* php)
{
	int maxValue = php->arr[0];
	php->arr[0] = php->arr[php->size - 1];
	php->size--;

	shiftdown(php->arr, 0, php->size);

	return maxValue;	//최댓값 리턴
}

int main()	//메인함수
{
	Heap heap;	//구조체 변수 선언
	int max;

	createHeap(&heap, 10);

	addHeap(&heap, 57);
	addHeap(&heap, 32);
	addHeap(&heap, 48);
	addHeap(&heap, 10);
	addHeap(&heap, 15);
	addHeap(&heap, 25);
	addHeap(&heap, 20);
	addHeap(&heap, 9);
	addHeap(&heap, 60);

	displayHeap(&heap);

	max = extractMax(&heap);
	printf("최댓값: %d\n", max);

	max = extractMax(&heap);
	printf("최댓값: %d\n", max);

	max = extractMax(&heap);
	printf("최댓값: %d\n", max);

	displayHeap(&heap);
	return 0;
}