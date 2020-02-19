#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include "types.h"
#include "graphics.h"


#ifndef _GRAPH_H_
#define _GRAPH_H_
#define SUCCESS    1
#define FAILURE    0
#define MAX_EDGE_NUM 100 	//����ͼ��������
#define MAX_VERTEX_NUM 20	//����ͼ����󶥵��� 
#define INF 32767			//���������
typedef char VerTexType;	// ���嶥����������
typedef int ArcType;		//����ߣ����ڽӾ�����������

extern node nodes[MAX_VERTEX_NUM];
extern	route routes[MAX_EDGE_NUM];

typedef struct Graph
{
	VerTexType Vexs[MAX_VERTEX_NUM][MAX_NAME_NUM];	//ͼ�Ķ��㣨���ƣ�����֪ʶ��char[][]:�ַ�������,MAXUM�����㣬������ַ���������10
	ArcType Arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 	//ͼ���ڽӾ���
	int VexNum;			//ͼ�ĵ�ǰ������ 
	int ArcNum; 		//ͼ�ĵ�ǰ���� 
}*PGraph;				//ͼ��ָ��


//1��������������ֲ�ͼ���ڽӾ���
int CreateGraph(PGraph pgraph);
//2�������������ֲ�ͼ
int PrintGraph(PGraph pgraph);
//2'
int PrintfGraph(PGraph pgraph);


void DFS(PGraph pgraph,int V);


int TraverseGraph(PGraph pgraph);

//Ϊ��������׼����ջ 
typedef struct 
{
	int *base;//ջ�� 
	int *top;//ջ�� 
	int stacksize;//���ռ� 
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
