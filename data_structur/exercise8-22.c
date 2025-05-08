//���� Ž�� Ʈ���� ���� ū �뵵�� map�̶�� �ڷᱸ���� ������ ��
//�ܾ����� �����Ͽ���.
//ģ�� ����ó�� �����ϰ� Ž���ϴ� ���α׷��� �ۼ�����
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

#pragma warning(disable : 4996)

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

//������ ����
typedef struct {
	char name[MAX_WORD_SIZE];
	char number[MAX_MEANING_SIZE];
}element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//���� e1 < e2 �̸� -1 ��ȯ
//���� e1 == e2 �̸� 0 ��ȯ
//���� e1 > e2 �̸� 1 ��ȯ
int compare(element e1, element e2)
{
	return strcmp(e1.name, e2.name);
}
//���� Ž�� Ʈ�� ��� �Լ�
void display(TreeNode* p)
{
	if (p != NULL) {
		printf("(");
		display(p->left);
		printf("%s:%s", p->key.name, p->key.number);
		display(p->right);
		printf(")");
	}
}

//���� Ʈ�� Ž�� �Լ�
TreeNode* search(TreeNode* root, element key)
{
	TreeNode* p = root;
	while (p != NULL) {
		int cmp = compare(key, p->key);
		if (cmp == 0)
			return p;
		else if (cmp < 0)
			p = p->left;
		else
			p = p->right;
	}
	return p; //Ž���� �������� ��� NULL ��ȯ
}

//�� ��带 �����
TreeNode* new_node(element item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}
//��� ����
TreeNode* insert_node(TreeNode* node, element key)
{
	//Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
	if (node == NULL) return new_node(key);

	//�׷��� ������ ��ȯ������ Ʈ���� ��������.
	if (compare(key, node->key) < 0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node->key) > 0)
		node->right = insert_node(node->right, key);
	//��Ʈ �����͸� ��ȯ�Ѵ�.
	return node;
}

TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	//�� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;
	return current;
}

//���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ� ���ο� ��Ʈ��带 ��ȯ�Ѵ�.
TreeNode* delete_node(TreeNode* root, element key)
{
	if (root == NULL) return root;
	//���� Ű�� ��Ʈ���� ������ ���� ����Ʈ��
	else if (compare(key, root->key) < 0)
		root->left = delete_node(root->left, key);
	//���� Ű�� ��Ʈ���� ũ�� ������ ����Ʈ��
	else if (compare(key, root->key) > 0)
		root->right = delete_node(root->right, key);
	//Ű�� ��Ʈ�� ������ �� ��带 ����
	else
	{
		//ù ��°�� �� ��° ���
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		//�� ��° ���
		TreeNode* temp = min_value_node(root->right);

		//�߿� ��ȸ�� �İ� ��带 �����Ѵ�.
		root->key = temp->key;
		//�߿� ��ȸ�� �İ� ��带 �����Ѵ�.
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

void help()
{
	printf("\n**** ����(i), Ž��(s), ����(d), q:����****:");
}

//���� Ž�� Ʈ���� ����ϴ� ���� ����
int main(void)
{
	char command;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp;

	do {
		help();
		command = getchar();
		getchar();	//����Ű ����
		switch (command) {
		case 'i':
			printf("�̸�: ");
			fgets(e.name, MAX_WORD_SIZE, stdin);
			e.name[strcspn(e.name, "\n")] = 0;
			printf("��ȭ��ȣ: ");
			fgets(e.number, MAX_WORD_SIZE, stdin);
			e.number[strcspn(e.number, "\n")] = 0;
			root = insert_node(root, e);
			break;
		case 'd':
			printf("�̸�: ");
			fgets(e.name, MAX_WORD_SIZE, stdin);
			e.name[strcspn(e.name, "\n")] = 0;
			root = delete_node(root, e);
			break;
		case 's':
			printf("�̸�: ");
			fgets(e.name, MAX_WORD_SIZE, stdin);
			e.name[strcspn(e.name, "\n")] = 0;
			tmp = search(root, e);	
			if (tmp != NULL)
				printf("��ȭ��ȣ:%s\n", e.number);
			break;
		}
	} while (command != 'q');
	return 0;
}