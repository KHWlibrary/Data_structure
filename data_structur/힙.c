/*
* [���� - �ִ��� ����]
* 1. �迭 ���� �� ���Ҹ� �߰��Ѵ�.
* 2. ��Ʈ�� �����ϱ� ���̰�, �߰� �� ���� �θ��� ������ ũ�ٸ� shiftUp�Ѵ�.
* 3.0(logN)�� �ð� ���⵵�� ���´�.
* 
* [����]
* 1. ��Ʈ���� �ӽ� ������ �����Ѵ�.
* 2. ���� ������ ���� ��Ʈ�� ������ �� ���� ũ�⸦ 1 ���� ��Ų��.
* 3. �� ������ �ǵ��� shiftDown�Ѵ�.
* 4. 0(lonN)�� �ð� ���⵵�� ���´�.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct heap
{
	int* arr;	//�� �޸�(�迭)�� �ּ� ����
	int size;	//����� ������ ����
	int capacity;	//��(�迭)�� �ִ� �뷮
}Heap;

void createHeap(Heap* php, int count)	//�� ����
{
	php->arr = (int*)malloc(sizeof(int) * count);
	php->size = 0;
	php->capacity = count;
}

void shiftup(int* arr, int childindex)
{
	int temp;
	int parentindex = (childindex - 1) / 2;

	//�θ��ε����� 0����ũ�ų� ����, �ڽ��ε����� �θ𺸴� Ŭ�� �ڸ� �ٲ�
	if (parentindex >= 0 && arr[parentindex] < arr[childindex])	
	{
		temp = arr[parentindex];
		arr[parentindex] = arr[childindex];
		arr[childindex] = temp;

		shiftup(arr, parentindex);
	}
}

void addHeap(Heap* php, int value)	//�� �߰�
{
	if (php->capacity == php->size)	//�ִ�뷮 == ���尳��
	{
		printf("�޸𸮰� �������ֽ��ϴ�, ���̻� ������ �� �����ϴ�.");
		return;
	}
	php->arr[php->size] = value;
	shiftup(php->arr, php->size);	//shift up - �ڽĳ�� ���忡�� �θ� ���� ��
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
	int largeindex = -1;	//�迭�� �ε����� �� �� ���� ��(0~size - 1)
	int temp;

	if(leftindex < size)	// left�ε����� size���� �۾ƾ���
		largeindex = leftindex;

	if (rightindex < size && arr[largeindex] < arr[rightindex])	//right�ε����� size���� �۾ƾ���
		largeindex = rightindex;

	if (largeindex != -1 && arr[largeindex] > arr[parentindex])
	{
		//�� ���� ���� ��ȯ
		temp = arr[largeindex];
		arr[largeindex] = arr[parentindex];
		arr[parentindex] = temp;

		return shiftdown(arr, largeindex, size);	//���ȣ�� : largeindex�� parentindex�� �Ǹ� ���ȣ���Ѵ�
	}
}

int extractMax(Heap* php)
{
	int maxValue = php->arr[0];
	php->arr[0] = php->arr[php->size - 1];
	php->size--;

	shiftdown(php->arr, 0, php->size);

	return maxValue;	//�ִ� ����
}

int main()	//�����Լ�
{
	Heap heap;	//����ü ���� ����
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
	printf("�ִ�: %d\n", max);

	max = extractMax(&heap);
	printf("�ִ�: %d\n", max);

	max = extractMax(&heap);
	printf("�ִ�: %d\n", max);

	displayHeap(&heap);
	return 0;
}