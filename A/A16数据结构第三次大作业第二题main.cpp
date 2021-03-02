#include<iostream>
//#include<stack>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NUM 10//定义输入的元素个数
#define STACK_INIT_SIZE 10 //定义栈的初始大小
//using namespace std;
#pragma warning(disable : 4996)

//-----树的二叉链表(孩子-兄弟)存储表示-----
typedef struct CSNode {
	char data;
	struct CSNode *firstchild, *nextsibling;
}CSNode,*CSTree;

//-----利用递归的方法建立(孩子-兄弟)二叉树-----
void CreateCSTree(CSTree &T, int &rootnumber, CSNode &root)
{
	char data;
	printf("请输入数据:\n");
	scanf(" %c", &data);//注意...带空格...
	if (data == '0') T = NULL;
	else
	{
		T = (CSTree)malloc(sizeof(CSNode));
		T->data = data;
		if (rootnumber == 0)
		{
			root.data = data;
			rootnumber++;
		}
		printf("请输入%c的第一个孩子:\n",T->data);
		CreateCSTree(T->firstchild, rootnumber, root);
		printf("请输入%c的兄弟:\n", T->data);
		CreateCSTree(T->nextsibling, rootnumber, root);
	}
}

//-----利用递归的方法销毁(孩子-兄弟)二叉树------
void FreeCSTree(CSTree *T)
{
	if (*T != NULL) {
		FreeCSTree(&(*T)->firstchild);
		FreeCSTree(&(*T)->nextsibling);
		FreeCSTree(T);
		*T = NULL;
	}
}

//-----(孩子-兄弟)找边-----
void FindSide(CSTree T)
{
	CSTree p, q;
	if (T)
	{
		p = T;
		q = T->firstchild;
		while (q)
		{
			printf("(%c,%c)", p->data, q->data);
			q = q->nextsibling;
		}
		FindSide(T->firstchild);
		FindSide(T->nextsibling);
	}
}

//-----主函数-----
//int main()
{
	CSTree T;
	CSNode root;
	CSNode *p;
	int rootnumber = 0;
	printf("SHOW HOW TO CREATE A CSTREE\n");
	printf("请输入建立的二叉树的信息:\n");
	CreateCSTree(T, rootnumber, root);
	printf("\n");
	printf("SHOW THE SIDES\n");
	FindSide(T);
	printf("\n");
	system("pause");
}
