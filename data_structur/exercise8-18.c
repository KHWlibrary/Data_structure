//���ڵ��� ��� �ִ� ���� Ž�� Ʈ���� ���� ��ȸ�ϸ� ���ĵ� ���ڰ� �������.
//�̸� �̿��Ͽ� ���� �迭�� ����ִ� ���ڵ��� ���Ľ�Ű�� �Լ��� �ۼ�����.
//���� ��ȸ�ϸ鼭 ���ڸ� ���. �� ���ڵ��� �ߺ����� �ʴ´ٴ� ������

#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//������ȸ�Լ�
void inorder(TreeNode* root);

int main(void)
{

}

void inorder(TreeNode* root)
{
	if (root != NULL) {
		inorder(root->left);
		printf("[%d] ", root->data);
		inorder(root->right);
	}
}