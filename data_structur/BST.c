#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable : 4996)

typedef struct treeNode
{
	int value;	//값을 저장할 공간
	struct treeNode* left;	//포인터(8바이트)
	struct treeNode* right;	//포인터(8바이트)
}treeNode;

treeNode* addNode(treeNode* t, int data);
void displayInorder(treeNode* t);
int main()
{
	treeNode* root = NULL; //포인터(8바이트) : 루트(최상위 노드)의 주소를 저장
	int choice;
	int data; 
	while (1)
	{
		system("cls");
		printf("\n\n\t\t***Binary Search Tree(BST) ***\n\n");
		printf("1. 노드 삽입\n");
		printf("2. 노드 삭제\n");
		printf("3. 노드 검색\n");
		printf("4. 최댓값 구하기\n");
		printf("5. 최솟값 구하기\n");
		printf("6. 이진 검색 트리 출력(중위순회)\n");
		printf("0. 프로그램 종료\n");
		printf("\n메뉴 선택 : ");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			printf("\n\n삽입할 정수 입력 : ");
			scanf("%d", &data);

			//addNode함수 : 노드를 생성한 후, 루트의 주소를 리턴
			root = addNode(root, data);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 0:
			exit(0);
		}
		printf("\n\n\t\t");
		system("pause");
	}
	return 0;
}

treeNode* addNode(treeNode* t, int data)
{
	if (t == NULL)
	{
		t = (treeNode*)malloc(sizeof(treeNode));	//트리 노드 생성
		t->value = data;
		t->left = NULL;
		t->right = NULL;
	}
	else if (t->value > data)	//삽입할 정수가 더 작은 경우
	{
		t->left = addNode(t->left, data);
	}
	else if (t->value < data)	//삽입할 정수가 큰 작은 경우
	{
		t->right = addNode(t->right, data);
	}
	return 0;
}

void displayInorder(treeNode* t)
{
	if (t != NULL)
	{
		displayInorder(t->left);
		printf("%d ", t->value);
		displayInorder(t->right);
	}
}
