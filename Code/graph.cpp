
#include "graph.h"
#include "io.h"
 

//为DFS准备的辅助数组 
int Visited[MAX_VERTEX_NUM]; 

//已被访问过的顶点,与visited不同，是用来重复输出顶点的，与vexnum比较 
int np;

//1、创建景区景点分布图（邻接矩阵）
int CreateGraph(PGraph pgraph){
	int i,j;
	printf("创建景区景点分布图\n");
	//初始化图的顶点数
	printf("请输入图的顶点数（顶点数<=20）\n");
	scanf("%d",&pgraph->VexNum);
	//检查是否超出 
	if(pgraph->VexNum>MAX_VERTEX_NUM){
		
		printf("输入数据有误\n");
		
		return FAILURE; 
	}
	//初始化图的弧数
	printf("请输入图的弧数（弧数<=100）\n");
	scanf("%d",&pgraph->ArcNum) ;
	//检查 
	if(pgraph->ArcNum>MAX_EDGE_NUM){
		printf("输入数据有误\n");
		return FAILURE;
	}
	//初始化图顶点的名称，即各景点名称
	printf("初始化顶点的名称\n");
	for(i=0;i<pgraph->VexNum;i++){
		printf("请输入第%d个顶点的名称\n",i+1);
		scanf("%s",pgraph->Vexs[i]);			 
	}
	//初始化弧的权值，对角线为0，其余为无穷大
	for(i=0;i<MAX_VERTEX_NUM;i++)
		for(int j=0;j<MAX_VERTEX_NUM;j++)
			pgraph->Arcs[i][j]=INF;
	for(i=0;i<MAX_VERTEX_NUM;i++)
		pgraph->Arcs[i][i]=0;
	//输入弧的权值
	printf("请输入弧（景点之间）的权重（距离）（注：按顺序从1开始）\n");
	for(i=0;i<pgraph->ArcNum;i++){
		int Stav,Endv,Weight;
		printf("请输入第%d条弧的权重(格式如：1 2 Weight)\n",i+1);
		scanf("%d %d %d",&Stav,&Endv,&Weight);
		pgraph->Arcs[Stav-1][Endv-1]=Weight;
		pgraph->Arcs[Endv-1][Stav-1]=Weight;
	}
	printf("创建景区景点分布图成功\n\n");
	printf("按任意键返回主菜单\n");
	system("pause");
	return SUCCESS;
}



//2、输出景区景点分布图
int PrintGraph(PGraph pgraph)
{
	int i,j;
	printf("显示景区景点分布图：\n");
	printf("景区景点名称：\n");
	for(i=0;i<pgraph->VexNum;i++){
		printf("%s	",pgraph->Vexs[i]);
	}
	printf("\n\n景点的邻接矩阵：\n");
	for(i=0;i<pgraph->VexNum;i++){
		printf("\n");
		for(j=0;j<pgraph->VexNum;j++){
			if(pgraph->Arcs[i][j]==INF){
				printf("∞	");
			}
			else if(pgraph->Arcs[i][j]==0){
				printf("0	");
			}
			else	printf("%d	",pgraph->Arcs[i][j]);
		}
		printf("\n");
	}
	printf("按任意键返回主菜单\n");
	printf("\n");
	system("pause");
	return SUCCESS;	
}

//2' 输出图形化景点分布
int PrintfGraph(PGraph pgraph){
	initgraph(1000,600); //初始化，显示一个窗口
	for(int i=0;i<sizeof(nodes)/sizeof(node);i++){
		outtextxy(nodes[i].x,nodes[i].y,nodes[i].point_name); //输出景点名称 
	}
	for(int i=0;i<sizeof(routes)/sizeof(route);i++){
		line(nodes[routes[i].src].x,nodes[routes[i].src].y,nodes[routes[i].dst].x,nodes[routes[i].dst].y);
	}
	getch(); // 暂停一下等待用户按键
    closegraph(); // 关闭图形界面
    printf("按任意键返回主菜单\n");
	printf("\n");
	system("pause");
	return SUCCESS;	
}


//3、输出景区导游路线(深度优先)
int TraverseGraph(PGraph pgraph){
	int V,i,j;
	char scen_name[MAX_NAME_NUM];
	np=0;
	for(i=0;i<pgraph->VexNum;i++)
			Visited[i]=0;
	printf("输出景区导游线路图：\n");
	printf("请输入景点出发位置名称：\n");
	//景点名称转成编号 
	scanf("%s",&scen_name);
	V=name2index(scen_name); 
	printf("景点导游路线为：\n");
	DFS(pgraph,V);
	printf("\n\n"); 
	printf("按任意键返回主菜单\n");
	system("pause");
	return SUCCESS;
}
//深度优先函数 
void DFS(PGraph pgraph,int V){
	int j;
	np++;
	if(np==1)
		printf("%s",pgraph->Vexs[V]);
	else
		printf("-->%s",pgraph->Vexs[V]);
	Visited[V]=1;
	for(j=0;j<pgraph->VexNum;j++)
	{
		if((pgraph->Arcs[V][j]!=INF&&pgraph->Arcs[V][j]!=0)&&Visited[j]!=1)
		{
			DFS(pgraph,j);
			if(pgraph->VexNum>np)
				printf("-->%s",pgraph->Vexs[V]);
		}
	}
}




//4、判断导游线路有无回路（拓扑排序）
int TopologicalSort(PGraph pgraph) 
{
	int i,j;
	printf("判断导游线路有无回路：\n\n");
	//定义入度数组,记录每个顶点的入度，初始化为0
	int Indegree[MAX_VERTEX_NUM]={0};
	//定义桟、并初始化桟
	STACK Stack;
	if(InitStack(&Stack,pgraph->VexNum)==FAILURE)
	{
		printf("警告：创建桟失败！！！\n");
 		printf("按任意键回主菜单\n");
 		system("pause"); 
 		return FAILURE;
	} 
	//求顶点的入度
	for(j=0;j<pgraph->VexNum;j++)
	{ 
		for(i=0;i<pgraph->VexNum;i++)
			if(pgraph->Arcs[i][j]!=0&&pgraph->Arcs[i][j]!=INF)
				Indegree[j]++;
		//入度为0的点入栈
		if(Indegree[j]==0)
			PushStack(&Stack,j);		
	}
	int Count=0,k;
	while(StackLen(&Stack))
	{
		PopStack(&Stack,&k);
		Count++;
		//对出栈的顶点所指向的点的入度减一，并将新入度为0的点入栈
		for(j=0;j<pgraph->VexNum;j++)
		{
			if(pgraph->Arcs[k][j]!=0&&pgraph->Arcs[k][j]!=INF)
				if((--Indegree[j])==0)
					PushStack(&Stack,j);
		}
	}
 	//判断是否有回路
	if(Count==pgraph->VexNum)
		printf("导游线路图无回路\n");
	else
	{
		printf("导游线路图有回路\n");
	}
 	printf("\n按任意键回主菜单\n");
 	system("pause");
 	return SUCCESS;
}
//初始化栈，为拓扑排序用 
int InitStack(STACK*PStack,int num)
{
	PStack->base=(int*)malloc(num*sizeof(int));
	PStack->top=PStack->base;
	PStack->stacksize=num;
	return SUCCESS; 
}
//入栈
int  PushStack(STACK*PStack,int j)
{
	if(PStack->top-PStack->base==PStack->stacksize)
		return FAILURE;
	*(PStack->top++)=j;
	return SUCCESS; 
}
//栈的长度
int StackLen(STACK*PStack)
{
	return PStack->top-PStack->base;
} 
//出栈
int PopStack(STACK*PStack,int*Pk)
{
	if(PStack->top==PStack->base)
		return FAILURE;
	*Pk=*(--(PStack->top));
	return SUCCESS;	
} 
//5、两个景点的最短路径（弗洛伊德）
int MinShortPath(PGraph pgraph)
{
	printf("景点间的最短路径：\n\n");
	int PathMatrix[pgraph->VexNum][pgraph->VexNum];//路径矩阵 
	int DisMatrix[pgraph->VexNum][pgraph->VexNum]; //距离矩阵 
	int i,j,k;
	//初始化两矩阵
	for(i=0;i<pgraph->VexNum;i++)
	{
		for(j=0;j<pgraph->VexNum;j++)
		{
			DisMatrix[i][j]=pgraph->Arcs[i][j];
			if(DisMatrix[i][j]!=INF&&DisMatrix[i][j]!=0)
				PathMatrix[i][j]=i;
			else
				PathMatrix[i][j]=-1;
		}
	}
	//更新两矩阵
	for(k=0;k<pgraph->VexNum;k++)
		for(i=0;i<pgraph->VexNum;i++)
			for(j=0;j<pgraph->VexNum;j++) 
				if(DisMatrix[i][j]>DisMatrix[i][k]+DisMatrix[k][j])
				{
 					DisMatrix[i][j]=DisMatrix[i][k]+DisMatrix[k][j];
				 	PathMatrix[i][j]=k;
				}
	//准备输出两景点的最短路径 
	int Stav=-1,Endv=-1;
	char Stav_name[MAX_NAME_NUM];
	char Endv_name[MAX_NAME_NUM];
	printf("请输入起点和终点名称：\n");
	//景点名称转成编号 
	scanf("%s %s",&Stav_name,&Endv_name);
	Stav=name2index(Stav_name);
	Endv=name2index(Endv_name);

 	if(Stav==-1||Endv==-1)
	 	return FAILURE;
	STACK Stack;
	if(InitStack(&Stack,pgraph->VexNum)==FAILURE)
 	{
 		printf("警告：创建桟失败！！！ \n");
	 	printf("按任意键回主菜单\n");
 		system("pause");
 	}
 	printf("\n两景点最短距离为%d\n",DisMatrix[Stav][Endv]);
 	while(Endv!=-1)
 	{
	 	PushStack(&Stack,Endv);
 		Endv=PathMatrix[Stav][Endv];
 	}
 	// 将所有路径出桟、并输出
 	printf("两景点最短路线为：\n");
 	while(1)
 	{
 		PopStack(&Stack,&Stav);
 		if(StackLen(&Stack)==1)
 			printf("%s",pgraph->Vexs[Stav]);
 		else
			printf("-->%s",pgraph->Vexs[Stav]);
 		if(!StackLen(&Stack))
			break;
 	}
 	printf("\n\n按任意键返回主菜单\n");
 	system("pause");
 	return SUCCESS; 
} 


//6、输出道路修建规划图（最小生成树 prim算法）
int MiniSpanTree_Prim(PGraph pgraph)
{
	int lowcost[MAX_VERTEX_NUM],closest[MAX_VERTEX_NUM];
	int i,j,k,min,v=0;//(v=0:从第一个顶点开始构建生成树） 
	printf("输出道路修建规划图:\n");
	//初始化lowcost数组和closest数组
	for(i=0;i<pgraph->VexNum;i++)
	{
		lowcost[i]=pgraph->Arcs[v][i];
		closest[i]=v;
	} 
	//开始加点并更新lowcost和closest数组
	for(i=1;i<pgraph->VexNum;i++)
	{
		min=INF;
		for(j=0;j<pgraph->VexNum;j++)
		{
			if(lowcost[j]!=0&&lowcost[j]<min)
			{
				min=lowcost[j];
				k=j;
			}	
		}
		if(min<INF){
			printf("%s->%s\n",pgraph->Vexs[closest[k]],pgraph->Vexs[k]);
		}
		lowcost[k]=0;
		//更新两数组 
		for(j=0;j<pgraph->VexNum;j++)
		{
			if(pgraph->Arcs[k][j]!=0&&pgraph->Arcs[k][j]<lowcost[j])
			{
				lowcost[j]=pgraph->Arcs[k][j];
				closest[j]=k;
			}	
		}	
	} 
	printf("\n\n按任意键返回主菜单\n");
 	system("pause");
 	return SUCCESS;
} 

//显示功能
void Frame(){
	printf("景区旅游信息管理系统功能：\n");
	printf("1、输出景区景点图\n");
	printf("2、输出景区导游路线\n");
	printf("3、判断导游线路图有无回路\n");
	printf("4、景点之间的最短路径\n");
	printf("5、输出道路修建规划图\n");
	printf("请选择相应的功能\n");
	
} 

//主菜单
int Menu(PGraph pgraph){
	int select;
	while(1){
		system("cls");	//清屏 
		Frame(); 
		scanf("%d",&select);
		system("cls");	
		switch(select)
		{
			case 1:
				PrintfGraph(pgraph);
				break;
			case 2:
				TraverseGraph(pgraph);
				break;
			case 3:
				TopologicalSort(pgraph);
				break;
			case 4:
				MinShortPath(pgraph);
				break;
			case 5:
				MiniSpanTree_Prim(pgraph);
				break;
			default:
				break;
		}
	}
} 


 
 
