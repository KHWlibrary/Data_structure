#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable : 4996)

typedef struct treeNode
{
	int value;	//���� ������ ����
	struct treeNode* left;	//������(8����Ʈ)
	struct treeNode* right;	//������(8����Ʈ)
}treeNode;

treeNode* addNode(treeNode* t, int data);
void displayInorder(treeNode* t);
int main()
{
	treeNode* root = NULL; //������(8����Ʈ) : ��Ʈ(�ֻ��� ���)�� �ּҸ� ����
	int choice;
	int data; 
	while (1)
	{
		system("cls");
		printf("\n\n\t\t***Binary Search Tree(BST) ***\n\n");
		printf("1. ��� ����\n");
		printf("2. ��� ����\n");
		printf("3. ��� �˻�\n");
		printf("4. �ִ� ���ϱ�\n");
		printf("5. �ּڰ� ���ϱ�\n");
		printf("6. ���� �˻� Ʈ�� ���(������ȸ)\n");
		printf("0. ���α׷� ����\n");
		printf("\n�޴� ���� : ");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			printf("\n\n������ ���� �Է� : ");
			scanf("%d", &data);

			//addNode�Լ� : ��带 ������ ��, ��Ʈ�� �ּҸ� ����
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
		t = (treeNode*)malloc(sizeof(treeNode));	//Ʈ�� ��� ����
		t->value = data;
		t->left = NULL;
		t->right = NULL;
	}
	else if (t->value > data)	//������ ������ �� ���� ���
	{
		t->left = addNode(t->left, data);
	}
	else if (t->value < data)	//������ ������ ū ���� ���
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
