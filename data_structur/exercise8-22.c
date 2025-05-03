//이진 탐색 트리의 가장 큰 용도가 map이라는 자료구조를 구현한 것
//단어장을 구현하였다.
//친구 연락처를 저장하고 탐색하는 프로그램을 작성하자
#include<stdio.h>
#include<Stdlib.h>

#pragma warning(disable : 4996)

typedef struct TreeNode {
	int name;
	double number;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

