#define POINTFILE "points.txt"
#define ROUTEFILE "routes.txt"
#ifndef _IO_H_
#define _IO_H_ 
#include "graph.h"
#include "string.h"
#include "types.h"

void loadFromFile(PGraph  pgraph);
void readPoints(char  pointNames[][MAX_NAME_NUM]);
int getPointNum();
int getArcsNum();




int  parseNode(node *);
// ֱ���޸ľ�̬�����Ĺ�ϣ��
// ע���ȼ�����û�б�ע��


// 
int  parseRoute(route *); 

// util for parseRoute Ϊ�����parseRoute�Ĺ��ߺ��� 
int route_split(char *buffer,route * record);

// util for parseNode
int node_split(char * buffer,node * record,char *point_name);

// util for convert string to int
int str2int(char *str); 

// load data from file and create a graph
int loadFromFile(PGraph pgraph,node * nodes , route * routes); 

//��������ת��Ϊ���
int name2index(char*scen_name); 

#endif
