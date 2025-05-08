//이진 탐색 트리의 가장 큰 용도가 map이라는 자료구조를 구현한 것
//단어장을 구현하였다.
//친구 연락처를 저장하고 탐색하는 프로그램을 작성하자
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

#pragma warning(disable : 4996)

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

//데이터 형식
typedef struct {
	char name[MAX_WORD_SIZE];
	char number[MAX_MEANING_SIZE];
}element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//만약 e1 < e2 이면 -1 반환
//만약 e1 == e2 이면 0 반환
//만약 e1 > e2 이면 1 반환
int compare(element e1, element e2)
{
	return strcmp(e1.name, e2.name);
}
//이진 탐색 트리 출력 함수
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

//이진 트리 탐색 함수
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
	return p; //탐색에 실패했을 경우 NULL 반환
}

//새 노드를 만들기
TreeNode* new_node(element item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}
//노드 삽입
TreeNode* insert_node(TreeNode* node, element key)
{
	//트리가 공백이면 새로운 노드를 반환한다.
	if (node == NULL) return new_node(key);

	//그렇지 않으면 순환적으로 트리를 내려간다.
	if (compare(key, node->key) < 0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node->key) > 0)
		node->right = insert_node(node->right, key);
	//루트 포인터를 반환한다.
	return node;
}

TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	//맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;
	return current;
}

//이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고 새로운 루트노드를 반환한다.
TreeNode* delete_node(TreeNode* root, element key)
{
	if (root == NULL) return root;
	//만약 키가 루트보다 작으면 왼쪽 서브트리
	else if (compare(key, root->key) < 0)
		root->left = delete_node(root->left, key);
	//만약 키가 루트보다 크면 오른쪽 서브트리
	else if (compare(key, root->key) > 0)
		root->right = delete_node(root->right, key);
	//키가 루트와 같으면 이 노드를 삭제
	else
	{
		//첫 번째나 두 번째 경우
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
		//세 번째 경우
		TreeNode* temp = min_value_node(root->right);

		//중외 순회시 후계 노드를 복사한다.
		root->key = temp->key;
		//중외 순회시 후계 노드를 삭제한다.
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

void help()
{
	printf("\n**** 삽입(i), 탐색(s), 삭제(d), q:종료****:");
}

//이진 탐색 트리를 사용하는 영어 사전
int main(void)
{
	char command;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp;

	do {
		help();
		command = getchar();
		getchar();	//엔터키 제거
		switch (command) {
		case 'i':
			printf("이름: ");
			fgets(e.name, MAX_WORD_SIZE, stdin);
			e.name[strcspn(e.name, "\n")] = 0;
			printf("전화번호: ");
			fgets(e.number, MAX_WORD_SIZE, stdin);
			e.number[strcspn(e.number, "\n")] = 0;
			root = insert_node(root, e);
			break;
		case 'd':
			printf("이름: ");
			fgets(e.name, MAX_WORD_SIZE, stdin);
			e.name[strcspn(e.name, "\n")] = 0;
			root = delete_node(root, e);
			break;
		case 's':
			printf("이름: ");
			fgets(e.name, MAX_WORD_SIZE, stdin);
			e.name[strcspn(e.name, "\n")] = 0;
			tmp = search(root, e);	
			if (tmp != NULL)
				printf("전화번호:%s\n", e.number);
			break;
		}
	} while (command != 'q');
	return 0;
}