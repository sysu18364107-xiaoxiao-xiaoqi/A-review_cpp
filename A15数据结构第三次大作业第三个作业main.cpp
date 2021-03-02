#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_TREE_SIZE 10//定义输入的元素个数
#pragma warning(disable : 4996)

//-----树的孩子链表存储表示-----
typedef struct CTNode
{//孩子结点
	char child;
	struct CTNode *next;
}*ChildPtr;
typedef struct {
	char data;
	ChildPtr firstchild;//孩子链表头指针
}CTBox;
typedef struct {
	CTBox nodes[MAX_TREE_SIZE];
	int n, r;//结点数和根的位置
}CTree;

void LinkChange(CTree *T, int *rootnumber, int* recorddegree)
{
	printf("请输入要处理的结点数:\n");
	scanf(" %d", &T->n);
	int n = T->n;
	ChildPtr p = (ChildPtr)malloc(sizeof(ChildPtr));
	for (int i = 0; i < n; i++)
	{
		printf("请输入第%d个结点的数据信息:\n", i);
		scanf(" %c", &T->nodes[i].data);
		int degree = 0;
		T->nodes[i].firstchild = (ChildPtr)malloc(sizeof(ChildPtr));
		printf("请输入第%d个结点第一个孩子的信息，如果没有第一个孩子，输入‘0’\n", i);
		scanf(" %c", &(T->nodes[i].firstchild->child));
		if (T->nodes[i].firstchild&&T->nodes[i].firstchild->child!='0')
		{
			if(i==0)(*rootnumber)++;
			degree++;	
			//T->nodes[i].firstchild->next = (CTNode*)(sizeof(CTNode));
			p = (T)->nodes[i].firstchild;
			char tempchild;
			do
			{
				printf("请输入第%d个结点第一个孩子后续孩子的的信息，如果没有后续的孩子，输入‘0’\n", i);
				scanf(" %c", &tempchild);
				if (tempchild == '0')
				{
					p->next = NULL;
					*recorddegree = (*recorddegree > degree) ? *recorddegree : degree;
				}
				else if (tempchild != '0')
				{
					if(i==0)(*rootnumber)++;
					degree++;
					p->next= (ChildPtr)malloc(sizeof(ChildPtr));
					p->next->child = tempchild;
					p = p->next;
				}
			}while (p->next);
		}
		
		
		
	}
}

//-----输出想要的表格-----
void CreateTable(CTree *T, int recorddegree, int rootnumber)
{//想法是想利用想计算矩阵行列式中按行展开的方法来列出表格
	//就是按照第一行展开从root所接的第一层孩子开始一列列向下探索
		//直至将整棵树都打印出来
	printf("%c\n", T->nodes[0].data);
	int count = 0;
	int nowlocation = 0;//在T.nodes[0]第一个孩子处
	int printnumber = 1;
	ChildPtr p =(ChildPtr)malloc(sizeof(ChildPtr));
	p=T->nodes[0].firstchild;
	for (int i = 0; i < rootnumber; i++)
	{
		count = 0;
		printf(" %c\n", p->child);
		printnumber++;
		for (int j = 0; j < T->n; j++)
		{
			if (T->nodes[j].data == p->child)
			{
				p = T->nodes[j].firstchild;
				nowlocation++;
				count = 1;
				j = T->n;
			}
		}
		while (p&&count&&printnumber<T->n)
		{
			printf("  %c\n", p->child);
			printnumber++;
			p = p->next;
		}
		p = T->nodes[0].firstchild;
		for (int k = 0; k < nowlocation; k++)
		{
			p = p->next;
		}

	}
}

void main()
{
	CTree T;
	int rootnumber=0;//根所接孩子
	int recorddegree = 0;//度
	LinkChange(&T,&rootnumber,&recorddegree);
	printf("rootnumber is %d\n", rootnumber);
	printf("recorddegree is %d\n", recorddegree);;
	CreateTable(&T, recorddegree, rootnumber);
	printf("RIGHT HERE!\n");
	system("pause");
}
