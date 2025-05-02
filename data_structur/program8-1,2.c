//��ũ������ ������ ����Ʈ��
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;
//		n1
//	   / |
//	  n2 n3

//����Ʈ���� 3���� ��ȸ���
//���� ��ȸ
void inorder(TreeNode* root);
//���� ��ȸ
void preorder(TreeNode* root);
//���� ��ȸ
void postorder(TreeNode* root);


int main(void)
{
	TreeNode* n1;
	TreeNode* n2;
	TreeNode* n3;
	n1 = (TreeNode*)malloc(sizeof(TreeNode));
	n2 = (TreeNode*)malloc(sizeof(TreeNode));
	n3 = (TreeNode*)malloc(sizeof(TreeNode));
	n1->data = 10;
	n1->left = n2;
	n1->right = n3;
	n2->data = 20;
	n2->left = NULL;
	n2->right = NULL;
	n3->data = 30;
	n3->left = NULL;
	n3->right = NULL;
	free(n1);
	free(n2);
	free(n3);

	return 0;
}

void inorder(TreeNode* root)
{
	if (root != NULL) {
		inorder(root->left);	//���ʼ���Ʈ�� ��ȸ
		printf("[%d]", root->data);	//���湮
		inorder(root->right);	//�����ʼ���Ʈ�� ��ȸ
	}
}

void preorder(TreeNode* root)
{
	if (root != NULL) {
		printf("[%d]", root->data);	//���湮
		inorder(root->left);	//���ʼ���Ʈ�� ��ȸ
		inorder(root->right);	//�����ʼ���Ʈ�� ��ȸ
	}
}

void postorder(TreeNode* root)
{
	if (root != NULL) {
		inorder(root->left);	//���ʼ���Ʈ�� ��ȸ
		inorder(root->right);	//�����ʼ���Ʈ�� ��ȸ
		printf("[%d]", root->data);	//���湮
	}
}
