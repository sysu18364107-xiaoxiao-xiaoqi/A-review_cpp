

/*



#include <ostream>
#include <string>
#include <iostream>
#include <stack>
using namespace std;
#pragma warning(disable:4996)
#define MAX_VERTEX_NUM 10
#define STACK_INIT_SIZE 100
#define MAXVALUE 200//相当于无穷




using namespace std;
#include <ostream>
#include <string>
#include <iostream>
#include <stack>
using namespace std;
#pragma warning(disable:4996)
#define MAX_VERTEX_NUM 10
#define STACK_INIT_SIZE 100
#define MAXVALUE 200//相当于无穷
using namespace std;
typedef struct ArcNode {
	int adjvex;//该弧所指向的顶点
	struct ArcNode *nextarc;//指向下一条弧的指针
	int info;//该弧相关信息的指针
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

void FindTheShortestPath(ALGraph *G, int lightmatrixorigin[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
	for (int q = 0; q < G->vexnum; q++)//把图中每一个点都当作源点来寻找一遍路径
	{
		for (int qLink = q + 1; qLink < G->vexnum; qLink++)//源点连接的点
		{
			do
			{
				for (int i = q; i < G->vexnum; i++)//处理这个源点的信息
				{
					for (int j = i; j < G->vexnum; j++)
					{
						if (lightmatrix[i][j] != MAXVALUE)
						{
							icount = i;
							jcount = j;
							path.push(i);
							value.push(lightmatrix[i][j]);
							if (i != G->vexnum - 1)
								i = j - 1;//从对应行开始点亮
							else i = G->vexnum;
							break;
						}
					}
					if (jcount != qLink)
					{
						lightmatrix[icount][jcount] = MAXVALUE;//路径错误，熄灭
						while (!path.empty())path.pop();//清空栈
						icount = jcount = 0;//还原

					}
					else if (jcount == qLink)
					{
						findpath++;
						path.push(jcount);
						//value.push(lightmatrix[icount][jcount]);
						for (int i = 0; i < G->vexnum; i++)//全部熄灭
							for (int j = 0; j < G->vexnum; j++)
								if (lightmatrix[i][j] != MAXVALUE)b = true;
						stack<int>temp;
						while (!path.empty())
						{
							record[recordicount][recordjcount] = path.top();
							path.pop();
							recordjcount++;
						}
						if (path.empty())recordicount++;
						while (!value.empty())
						{
							recordvalue[recordivaluecount][recordjvaluecount] = value.top();
							value.pop();
							recordjvaluecount++;
						}
						if (value.empty())(recordivaluecount++);
						printf("\n");
						lightmatrix[icount][jcount] = MAXVALUE;//路径正确，熄灭，找下一条正确的路径
						icount = jcount = 0;//还原
					}
				}
			} while (!b);
			if (findpath)
			{
				int compare[MAX_VERTEX_NUM] = { 0 };
				int comparevalue = 0;
				int comparevalueicount = 0;
				for (int i = 0; i < findpath; i++)
				{
					for (int j = 0; j < G->vexnum; j++)
					{
						if (recordvalue[i][j] != MAXVALUE)compare[i] += recordvalue[i][j];
					}
					if (compare[i] > comparevalue)
					{
						comparevalueicount = i;
						comparevalue = compare[i];
					}
				}
				int pathjcount = 0;//已经确定了是第comparevalueicount条是最短的
				stack<int>s;
				for (int j = 0; j < G->vexnum; j++)
					if (record[comparevalueicount][j] != MAXVALUE)
						s.push(record[comparevalueicount][j]);
				if (!s.empty())printf("--------------------------------------------------\n");
				printf("path is:");
				while (!s.empty())
				{
					printf("%d", s.top());
					s.pop();
					if (!s.empty())printf("->");
				}
				if (s.empty())printf("\n");
				printf("value is %d\n", comparevalue);
				if (s.empty())printf("--------------------------------------------------\n");
				if (s.empty())printf("\n");
			}
		}
		//-----判断源点连接的点的详细信息，并且还原数据，用于下一次源点连接点处理-----
	}
}


*/


