#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include "types.h"
#include "graphics.h"


#ifndef _GRAPH_H_
#define _GRAPH_H_
#define SUCCESS    1
#define FAILURE    0
#define MAX_EDGE_NUM 100 	//定义图的最大边数
#define MAX_VERTEX_NUM 20	//定义图的最大顶点数 
#define INF 32767			//定义无穷大
typedef char VerTexType;	// 定义顶点数据类型
typedef int ArcType;		//定义边（即邻接矩阵）数据类型

extern node nodes[MAX_VERTEX_NUM];
extern	route routes[MAX_EDGE_NUM];

typedef struct Graph
{
	VerTexType Vexs[MAX_VERTEX_NUM][MAX_NAME_NUM];	//图的顶点（名称）。新知识，char[][]:字符串数组,MAXUM个顶点，顶点的字符数不超过10
	ArcType Arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 	//图的邻接矩阵
	int VexNum;			//图的当前顶点数 
	int ArcNum; 		//图的当前边数 
}*PGraph;				//图的指针


//1、创建景区景点分布图（邻接矩阵）
int CreateGraph(PGraph pgraph);
//2、输出景区景点分布图
int PrintGraph(PGraph pgraph);
//2'
int PrintfGraph(PGraph pgraph);


void DFS(PGraph pgraph,int V);


int TraverseGraph(PGraph pgraph);

//为拓扑排序准备的栈 
typedef struct 
{
	int *base;//栈底 
	int *top;//栈顶 
	int stacksize;//最大空间 
}STACK;

int InitStack(STACK*PStack,int num);
int  PushStack(STACK*PStack,int j);
int StackLen(STACK*PStack);
int PopStack(STACK*PStack,int*Pk);

int MinShortPath(PGraph pgraph);

int MiniSpanTree_Prim(PGraph pgraph);

void Frame();

int Menu(PGraph pgraph);


#endif
