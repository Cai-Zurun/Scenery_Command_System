#define MAX_NAME_NUM 100
#ifndef _TYPES_H_
#define _TYPES_H_
struct route {
    int src;
    int dst;
    int weight;
};

struct node {
	int x;
	int y;
	int index;
	char point_name[MAX_NAME_NUM]; 
};

typedef node node;
typedef route route;
#endif
