#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//���� Ž��Ʈ������ �ܸ���� ���� ���ϱ�
int get_leaf_count(TreeNode* node);
//���� Ž��Ʈ������ ���� ���ϱ�
int get_height(TreeNode* node);


int main(void)
{

}

int get_leaf_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_leaf_count(node->left) + get_leaf_count(node->right);
	}
	return count;
}

int get_height(TreeNode* node)
{
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right);
	return height;
}
