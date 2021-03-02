using namespace std;
#include<ctype.h>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define INFEASIBLE -1
#define OK 1
#define setsize 35
#define seti 5
#define setk 5
#define insertnumber 7
#define mink 5
#define maxk 10

typedef struct {
	int *elem;			//存储空间基址
	int length;				//当前长度
	int listsize;				//当前分配的存储容量
} SqList;						//顺序表类型

typedef struct LNode {
	int data;
	struct LNode *next;
}LNode, *LinkList;

int main()
{
	LNode mynode;
	mynode.next = NULL;
	mynode.data = INFEASIBLE;
	LNode *tagnode = &mynode;//游标
	for (int i = 0; i < setsize; i++)
	{
		LNode *creatnode = (LNode*)malloc(sizeof(LNode));
		LNode *q = tagnode;
		creatnode->next = tagnode->next;//mynode.next;
		if((i%2)==0)creatnode->data = 0;
		else creatnode->data = i;
		tagnode->next = creatnode;
		tagnode = q->next;
	}

	LNode *testnode = &mynode;
	while (testnode->next != NULL)
	{
		LNode *q = testnode->next;
		if (((testnode->next->data) >= mink) && ((testnode->next->data) <= maxk))
		{

			testnode->next = testnode->next->next;
			free(q);
		}
		else
		{
			testnode = q;
		}
	}
	
	LNode *p = mynode.next, *s, *q;
	while (p)
	{
		q = p;
		while (q->next)				//固定p所指结点，向后遍历，寻找与之数据域相同的结点
		{
			if (q->next->data == p->data)	//在这里将q->next所指的结点存放数据与p作比较
			{
				s = q->next;
				q->next = s->next;
				free(s);
			}
			else q = q->next;
		}
		p = p->next;
	}

	LNode *test2node = &mynode;
	while (test2node->next != NULL)
	{
		LNode *q = test2node->next;
		printf("%d\n", test2node->next->data);
		test2node = q;
	}
	system("pause");
}

