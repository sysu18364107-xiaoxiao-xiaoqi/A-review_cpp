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
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("请输入第%d个顶点的信息\n", i);
		scanf(" %d", &(G->vertices[i].data));
		
		printf("请输入第%d个顶点第一个连接的点的信息,如果没有第一个连接的点,请输入'0'\n", i);
		G->vertices[i].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
		scanf(" %d", &temp);
		if (temp)
		{
			printf("请输入第%d个顶点到第一个孩子的权值\n", i);
			scanf(" %d", &(G->vertices[i].firstarc->info));
			G->vertices[i].firstarc->adjvex = temp;
			G->vertices[i].firstarc->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
			p = G->vertices[i].firstarc->nextarc;
		}
		else G->vertices[i].firstarc = NULL;
		while (temp)
		{
			printf("请输入第%d个顶点后续连接的点的信息,如果没有后续连接的点,请输入'0'\n", i);
			scanf("%d", &temp);
			if (temp)
			{
				int infotemp;
				printf("请输入第%d个顶点到后续孩子的权值\n", i);
				scanf("%d", &(infotemp));
				p->adjvex = temp;
				p->info = infotemp;
				p->nextarc= (ArcNode*)malloc(sizeof(ArcNode));
				p = p->nextarc;
			}
			else
			{
				p->info = NULL;
				p = NULL;
				
			}
				
		}

	}
	return(G);
}
//------------------

//-----同样将经过的点看成路径上的路灯，不过亮度有区分-----
//-----先形成路灯存在的表格，点亮成黄色-----
void FormLightMap(ALGraph *G,int lightmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
	ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
	for (int i = 0; i < G->vexnum; i++)
	{
		p = G->vertices[i].firstarc;
		for (int j = 0; j < G->vexnum; j++)
		{
			lightmatrix[i][j] = MAXVALUE;			
			if (p!=NULL&&p->adjvex==j)
			{
				lightmatrix[i][j] = p->info;
				p = p->nextarc;
			}	
			
		}
	}
	for (int i = 0; i < G->vexnum; i++)
		for (int j = 0; j < G->vexnum; j++)
		{
			printf(" %d ",lightmatrix[i][j]);
			if (j == G->vexnum - 1)printf("\n");
		}
}

//-----找到最短路径的办法------
//-----对于错误路径上的灯，每次都熄灭一盏灯-----
//-----因为在这里可能存在多个路径，因此在每找到一条正确路径时-----
//-----也要熄灭正确路径上的一盏灯，直至所有灯都被熄灭-----
//-----比较记录的路径权值大小，输出最短路径-----
void FindTheShortestPath(ALGraph *G, int lightmatrixorigin[MAX_VERTEX_NUM][MAX_VERTEX_NUM]) 
{
	for (int q = 0; q < G->vexnum; q++)//把图中每一个点都当作源点来寻找一遍路径
	{							
		for (int qLink = q + 1; qLink < G->vexnum; qLink++)//源点连接的点
		{
			int lightmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
			for (int i = 0; i < MAX_VERTEX_NUM; i++)
				for (int j = 0; j < MAX_VERTEX_NUM;j++)
					lightmatrix[i][j]=lightmatrixorigin[i][j];
			stack<int>path;
			stack<int>value;
			int icount = 0;
			int jcount = 0;
			int idelaycount = 0;
			int jdelaycount = 0;
			int count = 0;
			bool b = false;
			int record[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//用来存储最短路径的信息
			int recordvalue[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//用来存储最短路径的权值
			for (int i = 0; i < MAX_VERTEX_NUM; i++)
			{
				for (int j = 0; j < MAX_VERTEX_NUM; j++)
				{
					record[i][j] = MAXVALUE;
					recordvalue[i][j] = MAXVALUE;
				}
			}
			int recordicount = 0;
			int recordjcount = 0;
			int recordivaluecount = 0;
			int recordjvaluecount = 0;
			int findpath = 0;
			do
			{
			for(int i = q; i < G->vexnum; i++)//处理这个源点的信息
			{
				for (int j = i; j < G->vexnum; j++)
				{
					if (lightmatrix[i][j] != MAXVALUE)
					{
						idelaycount = icount;
						jdelaycount = jcount;
						icount = i;
						jcount = j;
						path.push(i);
						value.push(lightmatrix[i][j]);
						if (i != G->vexnum - 1)
							i = j - 1;//从对应行开始点亮						
						else if (i == G->vexnum - 1)
						{
							i = G->vexnum;
							break;
						}
							
							
					}
				}
				if (jcount != qLink)
				{
					lightmatrix[icount][jcount] = MAXVALUE;//路径错误，熄灭
					while (!path.empty())path.pop();//清空栈
					while (!value.empty())value.pop();
					icount = jcount = 0;//还原
					idelaycount = jdelaycount = 0;

				}
				else if (jcount == qLink)
				{
					findpath++;
					path.push(jcount);

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
					//if (idelaycount == q) b = true;
					//else lightmatrix[idelaycount][jdelaycount] = MAXVALUE;//路径的上一盏灯正确，熄灭，找下一条正确的路径
					lightmatrix[icount][jcount] = MAXVALUE;
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
			printf("value is %d\n",comparevalue);
			if (s.empty())printf("--------------------------------------------------\n");
			if (s.empty())printf("\n");
		}
		}
		//-----判断源点连接的点的详细信息，并且还原数据，用于下一次源点连接点处理-----	
	}
}

#include <iostream>
#include <cstdio>
#define MAX 1000000
using namespace std;
int arcs[10][10];//邻接矩阵
int D[10];//保存最短路径长度
int p[10][10];//路径
int final[10];//若final[i] = 1则说明 顶点vi已在集合S中
int n = 0;//顶点个数
int v0 = 0;//源点
int v, w;
void ShortestPath_DIJ()
{
	for (v = 0; v < n; v++) //循环 初始化
	{
		final[v] = 0; D[v] = arcs[v0][v];
		for (w = 0; w < n; w++) p[v][w] = 0;//设空路径
		if (D[v] < MAX) { p[v][v0] = 1; p[v][v] = 1; }
	}
	D[v0] = 0; final[v0] = 1; //初始化 v0顶点属于集合S
	//开始主循环 每次求得v0到某个顶点v的最短路径 并加v到集合S中
	for (int i = 1; i < n; i++)
	{
		int min = MAX;
		for (w = 0; w < n; w++)
		{
			//我认为的核心过程--选点
			if (!final[w]) //如果w顶点在V-S中
			{
				//这个过程最终选出的点 应该是选出当前V-S中与S有关联边
				//且权值最小的顶点 书上描述为 当前离V0最近的点
				if (D[w] < min) { v = w; min = D[w]; }
			}
		}
		final[v] = 1; //选出该点后加入到合集S中
		for (w = 0; w < n; w++)//更新当前最短路径和距离
		{
			/*在此循环中 v为当前刚选入集合S中的点
			则以点V为中间点 考察 d0v+dvw 是否小于 D[w] 如果小于 则更新
			比如加进点 3 则若要考察 D[5] 是否要更新 就 判断 d(v0-v3) + d(v3-v5) 的和是否小于D[5]
			*/
			if (!final[w] && (min + arcs[v][w] < D[w]))
			{
				D[w] = min + arcs[v][w];
				// p[w] = p[v];
				p[w][w] = 1; //p[w] = p[v] +　[w]
			}
		}
	}
}


int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arcs[i][j];
		}
	}
	ShortestPath_DIJ();
	for (int i = 0; i < n; i++) printf("D[%d] = %d\n", i, D[i]);
	return 0;
}


int main() {
	ALGraph G;
	Creat_Graph(&G);
	int lightmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	FormLightMap(&G, lightmatrix);
	FindTheShortestPath(&G, lightmatrix);
	
	system("pause");
}

void FindPath(ALGraph G,int v0,int )
