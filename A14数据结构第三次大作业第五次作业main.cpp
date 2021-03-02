#include <ostream>
#include <string>
#include <iostream>
#include <stack>
#include <iostream>
#include <cstdio>
#pragma warning(disable:4996)
#define MAX_VERTEX_NUM 10
#define MAXVALUE 200//相当于无穷
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
				p->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
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
void FormLightMap(ALGraph *G, int lightmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
	ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
	for (int i = 0; i < G->vexnum; i++)
	{
		p = G->vertices[i].firstarc;
		for (int j = 0; j < G->vexnum; j++)
		{
			lightmatrix[i][j] = MAXVALUE;
			if (p != NULL && p->adjvex == j)
			{
				lightmatrix[i][j] = p->info;
				p = p->nextarc;
			}

		}
	}
	for (int i = 0; i < G->vexnum; i++)
		for (int j = 0; j < G->vexnum; j++)
		{
			if (lightmatrix[i][j] == MAXVALUE)printf("∞\t");
			else printf("%d\t", lightmatrix[i][j]);
			if (j == G->vexnum - 1)printf("\n");
		}
}

//-----Dijkstra算法-----
//----主要用了贪心想法去实现，有点像强化学习里面的action与value的关系-----
//-----一层层向下走，往路径最短（权值最小）走-----
//------因为可能存在多个路径，先找最短的，这里利用已经找到的最短点为中转站-----
//-----更近就更新，否则不更新----- 
//-----仍旧用路灯比喻-----
//-----这个作业中Dijkstra由书中ShortestPath函数拓展而来，输出了路径-----
void ShortestPath(ALGraph *G,int lightmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM],int point)
{
	printf("\npoint is %d\n",point);
	int dist[MAX_VERTEX_NUM];//保存最小权值大小
	int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//路径
	int set[MAX_VERTEX_NUM];//若final[i] = 1则说明 顶点vi已在集合S中
	int n = G->vexnum;//顶点个数
	int v, w;
	for (v = 0; v < n; v++) //循环 初始化
	{
		set[v] = 0; 
		dist[v] = lightmatrix[point][v];
		for (w = 0; w < n; w++) 
			path[v][w] = 0;//设空路径
		if (dist[v] < MAX_VERTEX_NUM) 
		{ 
			path[v][point] = 1; 
			path[v][v] = 1; 
		}
	}
	dist[point] = 0; set[point] = 1; //初始化 v0顶点属于集合S
		//开始主循环 每次求得point到某个顶点v的最短路径 并加v到集合S中
	for (int i = 1; i < n; i++)
	{
		int min = MAXVALUE;
		for (w = 0; w < n; w++)
		{
			if (!set[w]) //如果w顶点在V-S中
			{
				//这个过程最终选出的点 应该是选出当前V-S中与S有关联边
				//且权值最小的顶点 书上描述为 当前离V0最近的点
				if (dist[w] < min) { v = w; min = dist[w]; }
			}
		}
		set[v] = 1; //选出该点后加入到合集S中
		for (w = 0; w < n; w++)//更新当前最短路径和距离
		{
			if (!set[w] && (min + lightmatrix[v][w] < dist[w]))
			{
				dist[w] = min + lightmatrix[v][w];
				path[w][w] = 1; 
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		
		if(dist[i]>0)printf("Value[%d] = %d\n", i, dist[i]);
		else printf("dist[%d] no path\n", i);
	}
		
}
void Dijkstra(ALGraph *G, int point,int lightmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
	int path[MAX_VERTEX_NUM];//路径数组 -1表不连通
	int dist[MAX_VERTEX_NUM];//权值记录
	int set[MAX_VERTEX_NUM] = {0};//标记顶点
	int min = 0;
	int v = 0;
	int k=0;
	int temp[MAX_VERTEX_NUM];
	for (int i = 0; i < G->vexnum; i++)
	{
		dist[i] = lightmatrix[point][i];
		if (lightmatrix[point][i] < MAXVALUE)
			path[i] = point;
		else path[i] = -1;
	}
	set[point] = 1;
	path[point] = -1;

	for (int i = 0; i < G->vexnum; i++)
	{
		min = MAXVALUE;
		//-----找到最短路径，点亮顶点成黄色-----
		for (int j = 0; j < G->vexnum; j++)
		{
			if (!set[j] && dist[j] < min)
			{
				v = j;
				min = dist[j];
			}
		}
		//-----将顶点点成绿色-----
		set[v] = 1;
		for (int j = 0; j < G->vexnum; j++)
		{
			//-----判断是否为最短路径-----
			if (!set[j] && min < MAXVALUE
				&&lightmatrix[v][j] < MAXVALUE
				&& (min + (lightmatrix[v][j]) < dist[j]))
			{
				dist[j] = min + lightmatrix[v][j];
				path[j] = v;
			}
		}
	}
	//-----输出路径-----
	for (int i = 0; i < G->vexnum; i++)
	{
		if (point != i)
		{
			printf("path:%d->%d:",G->vertices[point].data,G->vertices[i].data);
			if (path[i] == -1)
				printf("no path\n");
			
			else
			{
				int constcount = 0;
				int count = 1;
				temp[0] = 0;
				k = i;
				do 
				{
					temp[constcount]++;
					temp[count] = k;
					k = path[k];
					count++;
				} while (path[k] != -1);
				
				printf("%d ",G->vertices[point].data);

				if (temp[0])
				{
					for (int j = temp[constcount]; j > 0; j--)
						printf("%d ",G->vertices[temp[j]].data);
				}

				printf(",权值为:");
				if (dist[i] == MAXVALUE)
					printf("∞\n");
				else
					printf("%2d\n",dist[i]);
			}
		}
	}
}

int main()
{
	ALGraph G;
	Creat_Graph(&G);
	int lightmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	FormLightMap(&G, lightmatrix);
	int point=0;
	for (point; point < G.vexnum; point++)
	{
		ShortestPath(&G, lightmatrix, point);
		Dijkstra(&G, point, lightmatrix);
	}	
	system("pause");
	return 0;
}
