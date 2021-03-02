#include<iostream>
//#include<stack>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NUM 10//定义输入的元素个数
#define STACK_INIT_SIZE 10 //定义栈的初始大小
//using namespace std;
#pragma warning(disable : 4996)

//-----因为C语言没有栈的定义,所以要自己定义栈-----

//-----定义栈结构-----
typedef struct _Stack {	
	char* base;//栈底指针	
	char* top;//栈顶指针	
	int size;//栈大小
	int usage;//栈已经使用的范围
	void init(_Stack* s);
	void push(char data);
	void pop();
}stack,s;

//-----栈的初始化-----
void _Stack::init(_Stack* s) {
	s->base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	if (!s->base) exit(0);	// 存储分配失败
	s->top = s->base;
	s->size = STACK_INIT_SIZE;	
	s->top = s->base;
	s->size = STACK_INIT_SIZE;	//将数据域置为空	
	s->usage = NULL;//被使用的置为0
}

//-----定义栈的PUSH操作-----
void _Stack::push(char data) {
	if (usage == size) 
		printf("this stack is full\n");	
	//开始压栈	
	*top++=data;
	usage++;
}

//-----定义栈的POP操作-----
void _Stack::pop()
{
	if (usage != 0)
	{
		top--;//栈顶减1	
		usage--;
	}
}

//-----二叉树的二叉链存储表示-----
typedef struct BiTNode {
	int data;
	struct BiTNode *lchild, *rchild;//左右孩子指针
}BiTNode,*BiTree;

//-----利用递归的方法建立二叉树-----
void CreateBiTree(BiTree &T,int &rootnumber,BiTNode &root)
{	
	char data;
	printf("请输入数据:\n");
	scanf(" %c", &data);//注意...带空格...
	if (data == '0') T = NULL;	
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		T->data = data;
		if (rootnumber == 0)
		{
			root.data = data;
			rootnumber++;
		}
		printf("请输入%c的左孩子:\n",T->data);
		CreateBiTree(T->lchild,rootnumber,root);
		printf("请输入%c的右孩子:\n",T->data);
		CreateBiTree(T->rchild,rootnumber, root);
	}
}

//-----利用递归的方法销毁二叉树------
void FreeBiTree(BiTree *T)
{
	if (*T != NULL) {
		FreeBiTree(&(*T)->lchild);
		FreeBiTree(&(*T)->rchild);
		FreeBiTree(T);
		*T = NULL;
	}
}

//-----定位目标点-----
bool Locate(BiTree T, int findnumber, stack *s)
{	
	if (T == NULL)return false;
	s->push(T->data);
	printf("push%c\n",T->data);
	if (T->data == findnumber)return true;
	bool judge = false;
	//先去左子树找
	if (T->lchild != NULL)
		judge = Locate(T->lchild, findnumber, s);
	//左子树找不到并且右子树不为空的情况下才去找
	if (!judge && T->rchild != NULL)
		judge = Locate(T->rchild, findnumber, s);
	//左右都找不到，弹出栈顶元素
	if (!judge)
	{
		s->pop();
		printf("pop%c\n", T->data);
	}		
	return judge;
}

//-----展示路径-----
void ShowPath(stack *s)
{
	char A[NUM] = {0};
	int number = 0;
	int usage_ = s->usage;
	while ((usage_--)+1)//因为指针上指一位
	{
		A[number++] = *s->top;
		s->pop();
	}
	for (int i = number-1; i > 0; i--)
		if(i!=1)
		printf("%c->", A[i]);	
		else printf("%c\n", A[i]);
}

//-----主函数-----
int main()
{
	stack s;
	s.init(&s);
	BiTree T;
	BiTNode root;
	BiTNode *p;
	int rootnumber = 0;
	char findnumber;
	printf("请输入要寻找结点信息:\n");
	scanf_s("%c", &findnumber);
	printf("\n");
	printf("SHOW HOW TO CREATE A BITREE\n");
	printf("请输入建立的二叉树的信息:\n");
	CreateBiTree(T, rootnumber,root);
	printf("\n");
	printf("SHOW HOW TO LOCATE THE POINT\n");
	Locate(T, findnumber, &s);
	printf("\n");
	printf("SHOW THE PATH TO THE POINT\n");
	ShowPath(&s);
	system("pause");
}
