//���� Ʈ���� ���� Ʈ�� ���̰� �ִ� 1���̳��� Ʈ���� 
//���� Ʈ������Ѵ�. ����Ʈ������ �˻��ϴ� �Լ�isBalanced �ۼ��ϰ� �׽�Ʈ
#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {	//TreeNode����ü ����
	int data;		//data �������
	struct TreeNode* left;	//���� ����
	struct TreeNode* right;	//������ ����
}TreeNode;

//���� Ž�� Ʈ������ ����Ʈ�� ���� ���ϱ�
int get_height(TreeNode* node);
//����Ʈ������ Ȯ���ϴ� �Լ�
int isBalanced(TreeNode* node);

//			15
//		4		26
//	   1	  16  25
TreeNode n1 = { 1,NULL,NULL };
TreeNode n2 = { 4,&n1,NULL };
TreeNode n3 = { 16,NULL,NULL };
TreeNode n4 = { 25,NULL,NULL };
TreeNode n5 = { 20,&n3,&n4 };
TreeNode n6 = { 15,&n2,&n5 };
TreeNode* root = &n6;

int main(void)
{
	printf("���� Ʈ�����̴� %d�Դϴ�\n", get_height(root->left));//���� Ʈ�� ���� ���ϱ�
	printf("������ Ʈ�����̴� %d�Դϴ�\n", get_height(root->right));	//������ Ʈ�� ���� ���ϱ�
	if (isBalanced(root))
		printf("���� Ʈ���Դϴ�.\n");
	else
		printf("���� Ʈ���� �ƴմϴ�.\n");
	return 0;
}

int get_height(TreeNode* node)
{
	if (node == NULL)
		return 0;
	int left_height = get_height(node->left);
	int right_height = get_height(node->right);

	//���� ? ��: ����
	return (left_height > right_height ? left_height : right_height) + 1;
}

int isBalanced(TreeNode* node)
{
	if (node == NULL)
		return 1;
	int left_height = get_height(node->left);
	int right_height = get_height(node->right);

	if (abs(left_height - right_height) > 1)//���� ���� ���� ������ ���� ������ 1�� ������ 0���� ����
		return 0;

	return isBalanced(node->left) && isBalanced(node->right);
}
