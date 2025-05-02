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
treeNode* searchNode(treeNode* t, int target);
treeNode* getMaxNode(treeNode* t);
treeNode* getMinNode(treeNode* t);
treeNode* removeNode(treeNode* t, int target);
int main()
{
	treeNode* findNode;
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
			printf("\n\n삭제할 노드의 값 입력 : ");
			scanf("%d", &data);

			root = removeNode(root, data);
			break;
		case 3:
			printf("\n\n검색할 정수 입력 : ");
			scanf("%d", data);

			findNode = searchNode(root, data);

			if (findNode == NULL)
				printf("\n\n\t\t검색한 값이 존재하지 않습니다.\n");
			else
				printf("\n\n\t\t검색한 값은 존재합니다.\n");
			break;
		case 4:
			findNode = getMaxNode(root);
			if (findNode != NULL)
				printf("\n\n\n\t\t최댓값은 %d입니다.\n", findNode->value);
			break;
		case 5:
			findNode = getMinNode(root);
			if (findNode != NULL)
				printf("\n\n\n\t\t최솟값은 %d입니다.\n", findNode->value);
			break;
		case 6:
			printf("\n\n중위순회 출력(오름차순) : ");
			displayInorder(root);
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
	return t;
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

treeNode* searchNode(treeNode* t, int target)
{
	if (t->value == target)
		return t;	//찾는 값 노드의 주소를 리턴
	else if (t->value > target)
		return searchNode(t->left, target);	
	else
		return searchNode(t->right, target);
}

treeNode* getMaxNode(treeNode* t)
{
	if(t == NULL)
		return NULL;

	if (t->right != NULL)
	{
		return getMaxNode(t->right);
	}
	return t; //최댓값 노드를 리턴
}

treeNode* getMinNode(treeNode* t)
{
	if (t == NULL)
		return NULL; 

	if (t->left != NULL)
	{
		return getMaxNode(t->right);
	}
	return t; //최솟값 노드를 리턴
}

treeNode* removeNode(treeNode* t, int target)
{
	treeNode* temp;

	if (t->value == target)
	{	
		//노드를 삭제하는 코드
		if (t->left == NULL && t->right == NULL);	//case1. 자식 노드가 없는 경우
		{
			free(t);//노드 제거
			return NULL;
		}
		else if (t->left == NULL) // case2. 오른쪽 자식 노드만 있는 경우
		{
			temp = t->right;
			free(t);
			return temp;	//오른쪽 자식 노드의 값을 리턴
		}
		else if (t->right == NULL) // case3. 왼쪽 자식 노드만 있는 경우
		{
			temp = t->left;
			free(t);
			return temp;	//왼쪽 자식 노드의 값을 리턴
		}
		else
		{
			temp = getMaxNode(t->left);//오른쪽 자식 노드 중 최댓값을 찾아
		}
	}
	else if (t->value > target)
	{
		t->left = removeNode(t->left, target); //재귀호출
	}
	else
	{
		t->right = removeNode(t->right, target); //재귀호출
	}
	return t;
}
