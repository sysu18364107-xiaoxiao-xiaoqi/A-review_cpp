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
#define setsize 20
#define seti 5//第i个
#define setk 5//k个
#define insertnumber 7//插入数字

typedef struct {
	int *elem;			//存储空间基址
	int length;				//当前长度
	int listsize;				//当前分配的存储容量
} SqList;						//顺序表类型

typedef struct LNode {
	int data;
	struct LNode *next;
}LNode, *LinkList;

int DeleteK(SqList *a, int i, int k) {
	//本过程从顺序存储结构的线性表a中删除第i个元素起的k个元素
	if (i < 1 || k<0 || i + k>a->length) return INFEASIBLE;		//参数不合法
	else
	{
		for (int count = 1; count <= a->length - k; count++)
		{
			if (i + count - 1 + k <= a->length)
				a->elem[i + count - 1 - 1] = a->elem[i + count - 1 - 1 + k];
			//删除第i个，一开始认为是从第i个后面开始删除
			//没有看仔细是从第i个起开始删除
			//因此此处直接再减1，即能满足要求
		}
		int beforelength = a->length;
		a->length -= k;
		return OK;
	}//DeleteK
}

int ListInsert_Sq(SqList *list, int e)
{
	//在顺序表中按照适合的顺序放入e
	//如果重复，不放入
	int record= INFEASIBLE;
	for (int i = 0; i < list->length; i++)
		if (((list->elem[i]) < e && (list->elem[i + 1] > e)) || (i == ((list->length) - 1)))
		{
			record = i+1;//记录插入位置
			i = list->length;//限制第一个条件，在满足题意点停止
		}
			
	//处理越界
	if (!record&&(list->length + 1 >= list->listsize))
	{
		printf("%d\n", 53);
		int* newbase = (int *)malloc((LISTINCREMENT + list->listsize) * sizeof(int));
		if (!newbase)exit(OVERFLOW);
		list->elem = newbase;
		list->listsize = (LISTINCREMENT + list->listsize);
	}
	//放入元素
	list->length++;
	for (int j = list->length-1; j > record; j--)
		list->elem[j] = list->elem[j - 1];
		list->elem[record] = e;
	return 1;
}

int main()
{
	SqList list;
	list.elem = (int*)malloc((setsize * sizeof(int)));
	list.length = list.listsize = setsize;
	for (int i = 0; i < setsize; i++)
		list.elem[i] = i;
	if (DeleteK(&list, seti, setk))
	ListInsert_Sq(&list,insertnumber);
		for (int i = 0; i < list.length; i++)
			printf("%d\n", list.elem[i]);

		system("pause");
	return 0;

}

