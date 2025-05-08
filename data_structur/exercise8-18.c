//다음 배열에 숫자들을 정렬시키는 함수작성
//중위순회 출력, 중복없음

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

// 노드 생성
TreeNode* new_node(int data) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

// 이진 탐색 트리 삽입
TreeNode* insert(TreeNode* root, int data) {
	if (root == NULL) return new_node(data);

	if (data < root->data)
		root->left = insert(root->left, data);
	else if (data > root->data)
		root->right = insert(root->right, data);
	return root;
}

// 중위 순회
void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

// 트리 메모리 해제 
void free_tree(TreeNode* root) {
	if (root != NULL) {
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

int main(void) {
	int arr[] = { 11, 3, 4, 1, 56, 5, 6, 2, 98, 32, 23 };
	int n = sizeof(arr) / sizeof(arr[0]);

	TreeNode* root = NULL;
	for (int i = 0; i < n; i++) {
		root = insert(root, arr[i]);
	}

	printf("정렬된 숫자들: ");
	inorder(root);
	printf("\n");

	free_tree(root);  // 메모리 해제

	return 0;
}
