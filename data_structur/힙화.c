/*
*힙화(heapify) : 배열을 힙으로 변환하는 과정을 말한다
* 
* [힙 생성 과정 - 최대힙 기준]
* 1. 부모의 인덱스는 배열 중간 인덱스붜 작은 인덱스로 내려가며 shiftdown한다.
* 2. 왼쪽, 오른쪽 자식의 값 중 큰 값을 구해 부모의 값과 비교한다.
* 3. 자식 중 큰 값이 부모의 값보다 크다면 부모와 자식의 값을 교환한다.
* 4. 힙화의 시간 복잡도는 0(n/2 * lonN)으로 0(N)의 시간 복잡도를 갖는다.
*/

#include<stdio.h>
#include<stdlib.h>

void display(int* arr, int size)
{
	int i;
	printf("Heap dislpay : ");
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void shiftDown(int* arr, int parentindex, int size)	//0(logN)
{
	int leftindex = 2 * parentindex + 1;
	int rightindex = leftindex + 1;
	int largeindex = parentindex;
	int temp;

	//왼쪽 자식이 부모보다 크다면 largeindex갱신
	if (leftindex < size && arr[leftindex] > arr[largeindex])
		largeindex = leftindex;
	//오른쪽 자식이 부모보다 크다면 largeindex갱신
	if (rightindex < size && arr[rightindex] > arr[largeindex])
		largeindex = rightindex;

	//largeindex가 변경되었으면 부모와 largeindex 위치 교환 후 재귀 호출
	if (largeindex != parentindex) {
		//두 개의 값을 교한
		temp = arr[largeindex];
		arr[largeindex] = arr[parentindex];
		arr[parentindex] = temp;
		shiftDown(arr, largeindex, size);
	}
}

//heapify의 시간 복잡도: 0(N/2 * logN) => 0(N/2) => 0(N)
void heapify(int* arr, int size) {	//0(N/2)
	for (int i = size / 2 - 1; i >= 0; i--) {
		shiftDown(arr, i, size);	//0(logN)
	}
}

int main()
{
	int arr[10] = { 6, 4, 8, 2, 5, 7, 9, 1, 3, 10 };

	heapify(arr, 10);

	printf("\n original array: ");
	display(arr, 10);

	printf("\n Heapify array: ");
	display(arr, 10);
	return 0;
}