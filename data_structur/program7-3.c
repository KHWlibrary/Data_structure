#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct LinkNode
{
	element data;
	struct ListNode* link;
}ListNode;

//리스트 항목 출력