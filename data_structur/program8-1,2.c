//링크법으로 생성된 이진트리
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

//이진트리의 3가지 순회방법
//중위 순회
void inorder(TreeNode* root);
//전위 순회
void preorder(TreeNode* root);
//후위 순회
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
		inorder(root->left);	//왼쪽서브트리 순회
		printf("[%d]", root->data);	//노드방문
		inorder(root->right);	//오른쪽서브트리 순회
	}
}

void preorder(TreeNode* root)
{
	if (root != NULL) {
		printf("[%d]", root->data);	//노드방문
		inorder(root->left);	//왼쪽서브트리 순회
		inorder(root->right);	//오른쪽서브트리 순회
	}
}

void postorder(TreeNode* root)
{
	if (root != NULL) {
		inorder(root->left);	//왼쪽서브트리 순회
		inorder(root->right);	//오른쪽서브트리 순회
		printf("[%d]", root->data);	//노드방문
	}
}
