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
	//t��������io.h�� 
	extern hashtable *t;
	 
	// node �ṹ����� point_name ��index ��x �� y
	// route �ṹ����� src �� dst �� weight 
	 
	 

	Graph g;
	PGraph pgraph = &g;
	
	//����nodes routes t 
	loadFromFile(pgraph,nodes,routes);
	
	//���˵�ɾ���˹��� �������д���ͼ
	//�޸������� ʹ�ò��� PGraph pgraph
	 
	Menu(pgraph);
} 
