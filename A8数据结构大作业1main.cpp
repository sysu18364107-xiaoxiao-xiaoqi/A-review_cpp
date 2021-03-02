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
#define seti 5
#define setk 5

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
				a->elem[i + count - 1] = a->elem[i + count - 1 + k];
		}
		int beforelength = a->length;
		a->length -= k;
		return OK;
	}//DeleteK
}

int main()
{
	SqList list;
	list.elem = (int*)malloc((setsize * sizeof(int)));
	list.length = list.listsize = setsize;

	for (int i = 0; i < setsize; i++)
		list.elem[i] = i;
	if (DeleteK(&list, seti, setk))
		for (int i = 0; i < list.length; i++)
			printf("%d\n", list.elem[i]);
	system("pause");
	return 0;

}

