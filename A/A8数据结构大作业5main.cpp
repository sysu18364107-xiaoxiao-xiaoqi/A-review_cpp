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
#define setsize 5
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
	LNode mynode,mynode1;
	mynode.next =mynode1.next= NULL;
	mynode.data =mynode1.data= INFEASIBLE;
	LNode *tagnode = &mynode;//游标
	LNode *tagnode1 = &mynode1;//游标1
	for (int i = 0; i < setsize; i++)
	{
		LNode *creatnode = (LNode*)malloc(sizeof(LNode));
		LNode *creatnode1 = (LNode*)malloc(sizeof(LNode));
		LNode *q = tagnode;
		LNode *q1 = tagnode1;
		creatnode->next = tagnode->next;//mynode.next;
		creatnode1->next = tagnode1->next;//mynode.next;
		creatnode->data = i;
		
		creatnode1->data = i+6;
		tagnode->next = creatnode;
		tagnode1->next = creatnode1;
		tagnode = q->next;
		tagnode1 = q1->next;
	}

	LNode *test2node = &mynode;
	printf("this is A\n");
	while (test2node->next != NULL)
	{
		LNode *q = test2node->next;
		printf("%d\n", test2node->next->data);
		test2node = q;
	}
	printf("\n");
	printf("this is B\n");
	LNode *test3node = &mynode1;
	while (test3node->next != NULL)
	{
		LNode *q = test3node->next;
		printf("%d\n", test3node->next->data);
		test3node = q;
	}
	printf("\n");

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

	LNode *pa = mynode.next, *pb = mynode1.next;
	LNode *pc = &mynode;
	int p = 0;
	while (pa&&pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
			p = 0;//控制连接
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
			p = 1;//控制连接
		}
	}
	
	if (p)
		pc->next = pa;
	else pc->next = pb;
	LNode *test4node = &mynode;
	printf("this is C\n");
	while (test4node->next != NULL)
	{
		LNode *q = test4node->next;
		printf("%d\n", test4node->next->data);
		test4node = q;
	}
	system("pause");
}


//struct node first;//头结点，头结点有*next，但是data可以为空，或者为特殊的预设值
//struct node *head = &first;//head即是头指针，有头结点时指向头结点，没有头结点时指向第一个结点
//头指针一定要有，是访问链表的必要条件，不然找不到链表的位置
//头结点不一定要有，但是头结点的存在能够方便后续的一系列操作
