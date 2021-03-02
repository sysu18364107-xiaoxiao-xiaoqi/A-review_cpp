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
#define setsize 25
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

/*int DeleteK(SqList *a, int i, int k) {
	//本过程从顺序存储结构的线性表a中删除第i个元素起的k个元素
	if (i < 1 || k<0 || i + k>a->length) return INFEASIBLE;		//参数不合法
	else
	{
		for (int count = 1; count <= a->length - k; count++)
		{
			if (i + count - 1 + k <= a->length)
				a->elem[i + count - 1] = a->elem[i + count - 1 + k];
		}
		int beforelength = a->length;
		a->length -= k;
		return OK;
	}//DeleteK
}
*/

/*int ListInsert_Sq(SqList *list, int e)
{
	//在顺序表中按照适合的顺序放入e
	//如果重复，不放入
	int record = INFEASIBLE;
	for (int i = 0; i < list->length; i++)
		if (((list->elem[i]) < e && (list->elem[i + 1] > e)) || (i == ((list->length) - 1)))
		{
			record = i + 1;//记录插入位置
			i = list->length;//限制第一个条件，在满足题意点停止
		}

	//处理越界
	if (!record && (list->length + 1 >= list->listsize))
	{
		printf("%d\n", 53);
		int* newbase = (int *)malloc((LISTINCREMENT + list->listsize) * sizeof(int));
		if (!newbase)exit(OVERFLOW);
		list->elem = newbase;
		list->listsize = (LISTINCREMENT + list->listsize);
	}
	//放入元素
	list->length++;
	for (int j = list->length - 1; j > record; j--)
		list->elem[j] = list->elem[j - 1];
	list->elem[record] = e;
	return 1;
}*/

int main()
{
	LNode mynode;
	//LNode *lastnode = (LNode*)malloc(sizeof(LNode));
	//lastnode = NULL;
	mynode.next = NULL;
	mynode.data = INFEASIBLE;
	LNode *tagnode = &mynode;//游标
	for (int i = 0; i < setsize; i++)
	{
		LNode *creatnode=(LNode*)malloc(sizeof(LNode));
		LNode *q = tagnode;//游标
		creatnode->next = tagnode->next;//mynode.next;
		creatnode->data = i;
		tagnode->next = creatnode;
		tagnode = q->next;
	}

	LNode *testnode = &mynode;
	while (testnode->next != NULL)
	{	
		LNode *q = testnode->next;
		if (((testnode->next->data) >= mink)&&((testnode->next->data)<=maxk))
		{
			
			testnode->next = testnode->next->next;
			free(q);
		}
		else 
		{
			testnode = q;
		}		
	}
	LNode *test1node = &mynode;
	while (test1node->next != NULL)
	{
		LNode *q = test1node->next;
		printf("%d\n", test1node->next->data);
		test1node = q;
	}
	system("pause");
}

