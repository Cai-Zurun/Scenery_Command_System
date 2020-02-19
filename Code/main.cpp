#include "hashtable.h"
#include "graph.h"
#include "io.h"

//#include "Menu.h"
#define log(x) printf("%s",(x));printf("\n");
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct debug {
	int x;
};
node nodes[MAX_VERTEX_NUM];
route routes[MAX_EDGE_NUM];


int main()
{
	//t的声明在io.h中 
	extern hashtable *t;
	 
	// node 结构体包含 point_name 、index 、x 、 y
	// route 结构体包含 src 、 dst 、 weight 
	 
	 

	Graph g;
	PGraph pgraph = &g;
	
	//加载nodes routes t 
	loadFromFile(pgraph,nodes,routes);
	
	//主菜单删除了功能 从命令行创建图
	//修改了声明 使用参数 PGraph pgraph
	 
	Menu(pgraph);
} 
