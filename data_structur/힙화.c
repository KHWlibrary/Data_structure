/*
*��ȭ(heapify) : �迭�� ������ ��ȯ�ϴ� ������ ���Ѵ�
* 
* [�� ���� ���� - �ִ��� ����]
* 1. �θ��� �ε����� �迭 �߰� �ε����� ���� �ε����� �������� shiftdown�Ѵ�.
* 2. ����, ������ �ڽ��� �� �� ū ���� ���� �θ��� ���� ���Ѵ�.
* 3. �ڽ� �� ū ���� �θ��� ������ ũ�ٸ� �θ�� �ڽ��� ���� ��ȯ�Ѵ�.
* 4. ��ȭ�� �ð� ���⵵�� 0(n/2 * lonN)���� 0(N)�� �ð� ���⵵�� ���´�.
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

	//���� �ڽ��� �θ𺸴� ũ�ٸ� largeindex����
	if (leftindex < size && arr[leftindex] > arr[largeindex])
		largeindex = leftindex;
	//������ �ڽ��� �θ𺸴� ũ�ٸ� largeindex����
	if (rightindex < size && arr[rightindex] > arr[largeindex])
		largeindex = rightindex;

	//largeindex�� ����Ǿ����� �θ�� largeindex ��ġ ��ȯ �� ��� ȣ��
	if (largeindex != parentindex) {
		//�� ���� ���� ����
		temp = arr[largeindex];
		arr[largeindex] = arr[parentindex];
		arr[parentindex] = temp;
		shiftDown(arr, largeindex, size);
	}
}

//heapify�� �ð� ���⵵: 0(N/2 * logN) => 0(N/2) => 0(N)
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