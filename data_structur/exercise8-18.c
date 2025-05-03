//숫자들이 들어 있는 이진 탐색 트리를 중위 순회하면 정렬된 숫자가 얻어진다.
//이를 이용하여 다음 배열에 들어있는 숫자들을 정렬시키는 함수를 작성하자.
//중위 순회하면서 숫자를 출력. 단 숫자들은 중복되지 않는다는 가정함

#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//중위순회함수
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