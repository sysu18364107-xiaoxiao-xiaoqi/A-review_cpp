#include <ostream>
#include <string>
#include <iostream>
#include <stack>
using namespace std;
#pragma warning(disable:4996)
#define MAX_VERTEX_NUM 10
#define STACK_INIT_SIZE 100

typedef struct ArcNode {
	int adjvex;//该弧所指向的顶点
	struct ArcNode *nextarc;//指向下一条弧的指针
	int *info;//该弧相关信息的指针
}ArcNode;

typedef struct VNode {
	int data;//顶点信息
	ArcNode *firstarc;//指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;
	int vexnum, arcnum;//图的当前顶点数和弧数
	int kind;//图的种类标志
}ALGraph;


//-----图的创建-----
ALGraph *Creat_Graph(ALGraph *G)
{
	G->kind = 1;//默认为有向图
	printf("请输入图的总顶点数目:\n");
	scanf(" %d", &G->vexnum);
	printf("请输入图的总弧数目:\n");
	scanf(" %d", &G->arcnum);
	ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
	int temp;
	for (int i = 1; i < G->vexnum + 1; i++)
	{
		printf("请输入第%d个顶点的信息\n", i);
		scanf(" %d", &(G->vertices[i].data));
		printf("请输入第%d个顶点第一个连接的点的信息,如果没有第一个连接的点,请输入'0'\n", i);
		G->vertices[i].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
		scanf(" %d", &temp);
		if (temp)
		{
			G->vertices[i].firstarc->adjvex = temp;
			G->vertices[i].firstarc->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
			p = G->vertices[i].firstarc->nextarc;
		}
		else G->vertices[i].firstarc = NULL;
		while (temp)
		{
			printf("请输入第%d个顶点后续连接的点的信息,如果没有后续连接的点,请输入'0'\n", i);
			scanf(" %d", &temp);
			if (temp)
			{
				p->adjvex = temp;
				p = p->nextarc;
			}
		}

	}
	return(G);
}
//------------------

//-----深度遍历确定是不是存在路径-----
void DFS(ALGraph G, int i, int j, int visited[], bool &found)
{
	ArcNode *p;
	visited[i] = 1;
	if (i == j)
		found = true;
	else
	{
		p = G.vertices[i].firstarc;
		while (!found && p != NULL)
		{
			if (visited[p->adjvex] == 0)
				DFS(G, p->adjvex, j, visited, found);
			p = p->nextarc;
		}
	}
}
bool Path(ALGraph G, int i, int j, int visited[])
{
	int m;
	int count = 0;
	bool found;
	found = false;
	DFS(G, i, j, visited, found);
	return found;
}
//------------------------------------

//-----将路径的结点看作路灯-----
void lightpath(ALGraph G, int visited[], int m, int n)
{
	//-----把连通的点看作路灯-----
	//int** matrix;
//matrix = (int**)malloc(MAX_VERTEX_NUM * sizeof(int*));
//matrix = foundmatrix(G);
	int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	printf("请再次输入连接的方式:\n");
	for (int i = 1; i < G.vexnum + 1; i++)
	{
		for (int j = 1; j < G.vexnum + 1; j++)
		{
			printf("请输入第%d个顶点的信息\n", i);
			printf("如果第%d个顶点与第%d个顶点是连接的，请输入1，本身算不连接:\n", i, j);
			printf("如果不连接，请输入0:\n");
			int temp;
			scanf("%d", &temp);
			matrix[i][j] = temp;
		}
	}

	//-----将之前有经过的路灯点成黄色-----
	//int** comparematrix;
	//comparematrix = (int**)malloc(MAX_VERTEX_NUM * sizeof(int*));
	//comparematrix = foundcomparematrix(G, visited, matrix);

	int comparematrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	for (int i = 1; i < G.vexnum + 1; i++)
		for (int j = 1; j < G.vexnum + 1; j++)
			comparematrix[i][j] = 0;
	for (int i = 1; i < G.vexnum + 1; i++)
	{
		for (int j = 1; j < G.vexnum + 1; j++)
		{
			if (visited[i] == 1 && matrix[i][j] == 1)comparematrix[i][j] = 1;
		}
	}
	//-----点亮正确路径为绿色，不正确的路径熄灭-----
	//light(G, matrix, comparematrix, visited, m, n);
	stack<int>s;
	int icount = 0;
	int jcount = 0;
	int count = 0;
	bool b = false;
	do
	{
		for (int i = m; i < G.vexnum + 1; i++)
		{
			for (int j = i; j < G.vexnum + 1; j++)
			{
				if (comparematrix[i][j] == 1)
				{
					icount = i;
					jcount = j;
					s.push(i);
					if (i != G.vexnum)
						i = j - 1;//从对应行开始点亮						
					else i = G.vexnum + 1;
					break;
				}
				;
			}
		}
		if (jcount != n)
		{
			comparematrix[icount][jcount] = 0;//路径错误，熄灭
			while (!s.empty())s.pop();//清空栈
			icount = jcount = 0;//还原
		}
		else if (jcount == n)
		{
			s.push(jcount);
			b = true;
			stack<int>temp;
			while (!s.empty())
			{
				temp.push(s.top());
				s.pop();
			}
			printf("\n");
			while (!temp.empty())
			{
				printf("%d\n", temp.top());
				temp.pop();
			}
		}
	} while (!b);

}
//------------------------------

int main()
{
	ALGraph G = *Creat_Graph(&G);
	int visited[MAX_VERTEX_NUM] = { 0 };
	int m, n;
	printf("请输入连接结点信息:\n");
	scanf(" %d %d", &m, &n);
	bool found = Path(G, m, n, visited);
	if (found)
		lightpath(G, visited, m, n);
	system("pause");
}
