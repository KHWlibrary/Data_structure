//이진 트리의 서브 트리 높이가 최대 1차이나는 트리를 
//균형 트리라고한다. 균형트리인지 검사하는 함수isBalanced 작성하고 테스트
#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {	//TreeNode구조체 정의
	int data;		//data 저장공간
	struct TreeNode* left;	//왼쪽 간선
	struct TreeNode* right;	//오른쪽 간선
}TreeNode;

//이진 탐색 트리에서 서브트리 높이 구하기
int get_height(TreeNode* node);
//균형트리인지 확인하는 함수
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
	printf("왼쪽 트리높이는 %d입니다\n", get_height(root->left));//왼쪽 트리 높이 구하기
	printf("오른쪽 트리높이는 %d입니다\n", get_height(root->right));	//오른쪽 트리 높이 구하기
	if (isBalanced(root))
		printf("균형 트리입니다.\n");
	else
		printf("균형 트리가 아닙니다.\n");
	return 0;
}

int get_height(TreeNode* node)
{
	if (node == NULL)
		return 0;
	int left_height = get_height(node->left);
	int right_height = get_height(node->right);

	//조건 ? 참: 거짓
	return (left_height > right_height ? left_height : right_height) + 1;
}

int isBalanced(TreeNode* node)
{
	if (node == NULL)
		return 1;
	int left_height = get_height(node->left);
	int right_height = get_height(node->right);

	if (abs(left_height - right_height) > 1)//절댓값 왼쪽 길이 오른쪽 길이 뺀값이 1이 넘으면 0으로 리턴
		return 0;

	return isBalanced(node->left) && isBalanced(node->right);
}
