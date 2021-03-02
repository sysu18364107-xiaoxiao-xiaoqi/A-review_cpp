using namespace std;
#include<ctype.h>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#define theRowNumOfTheA 7
#define theColumnNumTheA 8
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAXROW 1000
#define MAXCOLUMN 1000
#define MAXSIZE 12500  // 假设非零元个数的最大值为12500
using namespace std;
/*
1. 试将下列递推过程改写为递归过程。要求用主程序测试，并在注释中描述程序功能、预期结果
	void ditui(int n)
	{
		int i;
		i = n;
		while(i>1)
			printf(i--);
}
*/
/*int ditui(int n)//递推函数
{
	if (n == 0)return 0;//如果递推到底,退出递推过程;
	else printf("%d\n", n);//print the answers
	return ditui(--n);//递推的核心，把下一次递推函数return,实现递推，直到n=0;
}
int main()
{
	int n = 4;
	ditui(n);
	system("pause");
	return 0;
}*/
/*
2. 试将下列递归过程改写为非递归过程。要求用主程序测试，并在注释中描述程序功能、预期结果
	void test(int &sum)
	{
		int x;
		scanf(x);
		if(x==0)
			sum=0;
		else
		{
			test(sum);
			sum+=x;
		}
		printf(sum);
}
*/
/*
void unditui(int &sum)//非递推的函数实现
{
	int x;//设置要加的数字
	scanf_s("%d", &x);//输入要加的数字
	int i = 0;	//设置递推条件
	while (i<=x)//非递推以实现递推效果
		printf("%d\n",sum + i++);
	if (i == x+1) {
		printf("the final sum is:");
		printf("%d\n", sum+i-1);
	}

}
int main()
{
	int sum = 5;
	unditui(sum);
	system("pause");
}
*/
/*
4. 试编写一个以三元组形式输出用十字链表表示的稀疏矩阵中非零元素及其下标的算法，
要求该算法先将十字链表转换成一个新的三元组，然后将三元组输出在命令行。
（三元组，十字链表实现方式见教材P98、P104）
用主程序测试、输入的十字链表如下
*/
/*
typedef struct OLNode {
	int i, j;  // 该非零元的行下标和列下标
	int e;
	struct OLNode *right, *down;
}OLNode, *OLink;
typedef struct {
	OLink *rhead, *chead;
	int mu, nu, tu;  // 稀疏矩阵的行数、列数和非零元个数
//	int rcount[MAXROW], ccount[MAXCOLUMN];//方便调试
}CrossList;

typedef struct {
	int i, j, e;
}Triple;
typedef struct {
	Triple data[MAXSIZE + 1];//data[0]不用
	int mu, nu, tu;
}TSMatrix;

//生成十字链表
int CreateSMatrix_OL(CrossList *M) {
	// 创建稀疏矩阵M。采用十字链表存储表示
	int m, n, t;//输入的行，列，非零元个数
	scanf_s("%d %d %d", &m, &n, &t);
	M->mu = m; M->nu = n; M->tu = t;
	if (!(M->rhead = (OLink *)malloc((m + 1) * sizeof(OLink)))) exit(OVERFLOW);//分配存储空间
	if (!(M->chead = (OLink *)malloc((n + 1) * sizeof(OLink)))) exit(OVERFLOW);
	for (int i = 0; i < m + 1; ++i) M->rhead[i] = NULL;//将头结点都设为0
	for (int i = 0; i < n + 1; ++i) M->chead[i] = NULL;
//	for (int i = 0; i < m + 1; ++i)M->rcount[i] = 0;
//	for (int i = 0; i < n + 1; ++i)M->ccount[i] = 0;
	int i, j, e;
	for (scanf_s("%d%d%d", &i, &j, &e); i != 0; scanf_s("%d%d%d", &i, &j, &e)) {
		OLNode *p;
		if (!(p = (OLNode *)malloc(sizeof(OLNode)))) exit(OVERFLOW);
		p->i = i; p->j = j; p->e = e;
		if (M->rhead[i] == NULL || M->rhead[i]->j > j) {//如果为空/顺序应当排在当前j的前面
			p->right = M->rhead[i];//插入p所带的i，j，e
			M->rhead[i] = p;
//			M->rcount[i]++;
		}
		else {
			OLNode *q;
			for (q = M->rhead[i]; (q->right) && q->right->j < j; q = q->right);
			p->right = q->right;
			q->right = p;
//			M->rcount[i]++;
		}
		if (M->chead[j] == NULL || M->chead[j]->i > i) {
			p->down = M->chead[j];
			M->chead[j] = p;
//			M->ccount[j]++;
		}
		else {
			OLNode *q;
			for (q = M->chead[j]; (q->down) && q->down->i < i; q = q->down)
				p->down = q->down;
			q->down = p;
///			M->ccount[j]++;
		}
	}
	return OK;
}// CreateSMatrix_OL

//十字链表转三元组
int SMatrix_OL_To_TSMatrix(CrossList *M, TSMatrix *TSM){
	TSM->mu = M->mu; TSM->nu = M->nu; TSM->tu = M->tu;
	int count = 1;//data[0]不用
	for (int i = 1; i <= M->mu && count <= TSM->tu; ++i) {
		if (!(M->rhead[i])) continue;//如果遇到空行，跳过
		for (OLNode *q = M->rhead[i]; q; q = q->right) {//向右走
			Triple p;
			p.i = q->i; p.j = q->j; p.e = q->e;//找到一个三元元素
			TSM->data[count] = p;//把三元元素放入到三元组中
//			cout << TSM->data[count].e << endl;//打印检查
			count++;
		}
	}
	return count;
}
//转成三原组，嗯，在这里遇到一个问题，就是TSM.data[count].e=p->e,不能够赋值，
//如果我直接将q.i，q.j,q.e赋值给TSM.data[count].i/j/e=p->i/j/e,i,j都可以成功赋值
//但是TSM.data[count].e=p->e,不能够赋值，出现了初始化的问题，
//但是我初始化之后又没有办法再次赋值，就是原来一开始初始化的值
//我试了好久，不知道怎么解决这个问题
//助教有时间可以帮我康康吗qwqq
//我已经把图发在群里了qwq

//三元组输出
int Cout_TSMatrix(TSMatrix *TSM,int count){
	for (int i = 1; i < count; i++)
		printf("i is%d\tj is%d\tvalue is%d\t\n", TSM->data[i].i,TSM->data[i].j,TSM->data[i].e);
	return OK;
}
g
int main()
{
	CrossList *M = (CrossList *)malloc(sizeof(CrossList));
	CreateSMatrix_OL(M);
	TSMatrix *TSM = (TSMatrix *)malloc(sizeof(TSMatrix));
	int count=SMatrix_OL_To_TSMatrix(M,TSM);
	Cout_TSMatrix(TSM, count);
	system("pause");
	return 1;
}*/
/*
3. 编写算法，求得所有包含在串s中而不包含在串t中的字符（s中重复的字符只选一个）构成的新串r，
以及r中每个字符在s中第一次出现的位置。
要求1：用串的定长顺序存储结构来实现，涉及到的其他串操作函数自己实现
要求2：“r中每个字符在s中第一次出现的位置”以数组形式输出。
要求3：用主程序测试，s，t自由定义，在注释中写明预期结果并printf输出
*/
#define MAX_STRLEN  256
#define s_length 15
#define t_length 4
#define empty 0
#define full 1
typedef  struct
{
	char  str[MAX_STRLEN];
	int  length;
} StringType;
int main()
{
	StringType s = { "abcdefg1abcdefg" , s_length };
	StringType t = { "efg1",t_length };
	int SA[s_length] = { empty };
	for (int i = 0; i < s_length; i++)
		for (int j = 0; j < t_length; j++)
			if (s.str[i] == t.str[j]) SA[i] = full;
	//与t相同表标full，与t不同标empty
	for (int i = 0; i < s_length; i++)
	{
		if (SA[i] == full) continue;
		for (int j = i + 1; j < s_length; j++)
		{
			if (SA[j] == full)continue;
			if (s.str[i] == s.str[j])SA[j] = full;

		}
	}
	//s中相同表full,s中不相同标empty
	int record[s_length] = { empty };
	int count = 0;
	for (int i = 0; i < s_length; i++)if (SA[i] == empty) {
		cout << i << endl;
	}
	system("pause");

}

