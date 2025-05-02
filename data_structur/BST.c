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
treeNode* searchNode(treeNode* t, int target);
treeNode* getMaxNode(treeNode* t);
treeNode* getMinNode(treeNode* t);
treeNode* removeNode(treeNode* t, int target);
int main()
{
	treeNode* findNode;
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
			printf("\n\n������ ����� �� �Է� : ");
			scanf("%d", &data);

			root = removeNode(root, data);
			break;
		case 3:
			printf("\n\n�˻��� ���� �Է� : ");
			scanf("%d", data);

			findNode = searchNode(root, data);

			if (findNode == NULL)
				printf("\n\n\t\t�˻��� ���� �������� �ʽ��ϴ�.\n");
			else
				printf("\n\n\t\t�˻��� ���� �����մϴ�.\n");
			break;
		case 4:
			findNode = getMaxNode(root);
			if (findNode != NULL)
				printf("\n\n\n\t\t�ִ��� %d�Դϴ�.\n", findNode->value);
			break;
		case 5:
			findNode = getMinNode(root);
			if (findNode != NULL)
				printf("\n\n\n\t\t�ּڰ��� %d�Դϴ�.\n", findNode->value);
			break;
		case 6:
			printf("\n\n������ȸ ���(��������) : ");
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
		return t;	//ã�� �� ����� �ּҸ� ����
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
	return t; //�ִ� ��带 ����
}

treeNode* getMinNode(treeNode* t)
{
	if (t == NULL)
		return NULL; 

	if (t->left != NULL)
	{
		return getMaxNode(t->right);
	}
	return t; //�ּڰ� ��带 ����
}

treeNode* removeNode(treeNode* t, int target)
{
	treeNode* temp;

	if (t->value == target)
	{	
		//��带 �����ϴ� �ڵ�
		if (t->left == NULL && t->right == NULL);	//case1. �ڽ� ��尡 ���� ���
		{
			free(t);//��� ����
			return NULL;
		}
		else if (t->left == NULL) // case2. ������ �ڽ� ��常 �ִ� ���
		{
			temp = t->right;
			free(t);
			return temp;	//������ �ڽ� ����� ���� ����
		}
		else if (t->right == NULL) // case3. ���� �ڽ� ��常 �ִ� ���
		{
			temp = t->left;
			free(t);
			return temp;	//���� �ڽ� ����� ���� ����
		}
		else
		{
			temp = getMaxNode(t->left);//������ �ڽ� ��� �� �ִ��� ã��
		}
	}
	else if (t->value > target)
	{
		t->left = removeNode(t->left, target); //���ȣ��
	}
	else
	{
		t->right = removeNode(t->right, target); //���ȣ��
	}
	return t;
}
