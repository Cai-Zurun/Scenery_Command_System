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
// 直接修改静态变量的哈希表
// 注意先检测点有没有被注释


// 
int  parseRoute(route *); 

// util for parseRoute 为了完成parseRoute的工具函数 
int route_split(char *buffer,route * record);

// util for parseNode
int node_split(char * buffer,node * record,char *point_name);

// util for convert string to int
int str2int(char *str); 

// load data from file and create a graph
int loadFromFile(PGraph pgraph,node * nodes , route * routes); 

//景点名称转换为编号
int name2index(char*scen_name); 

#endif
