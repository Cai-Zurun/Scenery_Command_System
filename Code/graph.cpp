
#include "graph.h"
#include "io.h"
 

//ΪDFS׼���ĸ������� 
int Visited[MAX_VERTEX_NUM]; 

//�ѱ����ʹ��Ķ���,��visited��ͬ���������ظ��������ģ���vexnum�Ƚ� 
int np;

//1��������������ֲ�ͼ���ڽӾ���
int CreateGraph(PGraph pgraph){
	int i,j;
	printf("������������ֲ�ͼ\n");
	//��ʼ��ͼ�Ķ�����
	printf("������ͼ�Ķ�������������<=20��\n");
	scanf("%d",&pgraph->VexNum);
	//����Ƿ񳬳� 
	if(pgraph->VexNum>MAX_VERTEX_NUM){
		
		printf("������������\n");
		
		return FAILURE; 
	}
	//��ʼ��ͼ�Ļ���
	printf("������ͼ�Ļ���������<=100��\n");
	scanf("%d",&pgraph->ArcNum) ;
	//��� 
	if(pgraph->ArcNum>MAX_EDGE_NUM){
		printf("������������\n");
		return FAILURE;
	}
	//��ʼ��ͼ��������ƣ�������������
	printf("��ʼ�����������\n");
	for(i=0;i<pgraph->VexNum;i++){
		printf("�������%d�����������\n",i+1);
		scanf("%s",pgraph->Vexs[i]);			 
	}
	//��ʼ������Ȩֵ���Խ���Ϊ0������Ϊ�����
	for(i=0;i<MAX_VERTEX_NUM;i++)
		for(int j=0;j<MAX_VERTEX_NUM;j++)
			pgraph->Arcs[i][j]=INF;
	for(i=0;i<MAX_VERTEX_NUM;i++)
		pgraph->Arcs[i][i]=0;
	//���뻡��Ȩֵ
	printf("�����뻡������֮�䣩��Ȩ�أ����룩��ע����˳���1��ʼ��\n");
	for(i=0;i<pgraph->ArcNum;i++){
		int Stav,Endv,Weight;
		printf("�������%d������Ȩ��(��ʽ�磺1 2 Weight)\n",i+1);
		scanf("%d %d %d",&Stav,&Endv,&Weight);
		pgraph->Arcs[Stav-1][Endv-1]=Weight;
		pgraph->Arcs[Endv-1][Stav-1]=Weight;
	}
	printf("������������ֲ�ͼ�ɹ�\n\n");
	printf("��������������˵�\n");
	system("pause");
	return SUCCESS;
}



//2�������������ֲ�ͼ
int PrintGraph(PGraph pgraph)
{
	int i,j;
	printf("��ʾ��������ֲ�ͼ��\n");
	printf("�����������ƣ�\n");
	for(i=0;i<pgraph->VexNum;i++){
		printf("%s	",pgraph->Vexs[i]);
	}
	printf("\n\n������ڽӾ���\n");
	for(i=0;i<pgraph->VexNum;i++){
		printf("\n");
		for(j=0;j<pgraph->VexNum;j++){
			if(pgraph->Arcs[i][j]==INF){
				printf("��	");
			}
			else if(pgraph->Arcs[i][j]==0){
				printf("0	");
			}
			else	printf("%d	",pgraph->Arcs[i][j]);
		}
		printf("\n");
	}
	printf("��������������˵�\n");
	printf("\n");
	system("pause");
	return SUCCESS;	
}

//2' ���ͼ�λ�����ֲ�
int PrintfGraph(PGraph pgraph){
	initgraph(1000,600); //��ʼ������ʾһ������
	for(int i=0;i<sizeof(nodes)/sizeof(node);i++){
		outtextxy(nodes[i].x,nodes[i].y,nodes[i].point_name); //����������� 
	}
	for(int i=0;i<sizeof(routes)/sizeof(route);i++){
		line(nodes[routes[i].src].x,nodes[routes[i].src].y,nodes[routes[i].dst].x,nodes[routes[i].dst].y);
	}
	getch(); // ��ͣһ�µȴ��û�����
    closegraph(); // �ر�ͼ�ν���
    printf("��������������˵�\n");
	printf("\n");
	system("pause");
	return SUCCESS;	
}


//3�������������·��(�������)
int TraverseGraph(PGraph pgraph){
	int V,i,j;
	char scen_name[MAX_NAME_NUM];
	np=0;
	for(i=0;i<pgraph->VexNum;i++)
			Visited[i]=0;
	printf("�������������·ͼ��\n");
	printf("�����뾰�����λ�����ƣ�\n");
	//��������ת�ɱ�� 
	scanf("%s",&scen_name);
	V=name2index(scen_name); 
	printf("���㵼��·��Ϊ��\n");
	DFS(pgraph,V);
	printf("\n\n"); 
	printf("��������������˵�\n");
	system("pause");
	return SUCCESS;
}
//������Ⱥ��� 
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




//4���жϵ�����·���޻�·����������
int TopologicalSort(PGraph pgraph) 
{
	int i,j;
	printf("�жϵ�����·���޻�·��\n\n");
	//�����������,��¼ÿ���������ȣ���ʼ��Ϊ0
	int Indegree[MAX_VERTEX_NUM]={0};
	//����C������ʼ���C
	STACK Stack;
	if(InitStack(&Stack,pgraph->VexNum)==FAILURE)
	{
		printf("���棺�����Cʧ�ܣ�����\n");
 		printf("������������˵�\n");
 		system("pause"); 
 		return FAILURE;
	} 
	//�󶥵�����
	for(j=0;j<pgraph->VexNum;j++)
	{ 
		for(i=0;i<pgraph->VexNum;i++)
			if(pgraph->Arcs[i][j]!=0&&pgraph->Arcs[i][j]!=INF)
				Indegree[j]++;
		//���Ϊ0�ĵ���ջ
		if(Indegree[j]==0)
			PushStack(&Stack,j);		
	}
	int Count=0,k;
	while(StackLen(&Stack))
	{
		PopStack(&Stack,&k);
		Count++;
		//�Գ�ջ�Ķ�����ָ��ĵ����ȼ�һ�����������Ϊ0�ĵ���ջ
		for(j=0;j<pgraph->VexNum;j++)
		{
			if(pgraph->Arcs[k][j]!=0&&pgraph->Arcs[k][j]!=INF)
				if((--Indegree[j])==0)
					PushStack(&Stack,j);
		}
	}
 	//�ж��Ƿ��л�·
	if(Count==pgraph->VexNum)
		printf("������·ͼ�޻�·\n");
	else
	{
		printf("������·ͼ�л�·\n");
	}
 	printf("\n������������˵�\n");
 	system("pause");
 	return SUCCESS;
}
//��ʼ��ջ��Ϊ���������� 
int InitStack(STACK*PStack,int num)
{
	PStack->base=(int*)malloc(num*sizeof(int));
	PStack->top=PStack->base;
	PStack->stacksize=num;
	return SUCCESS; 
}
//��ջ
int  PushStack(STACK*PStack,int j)
{
	if(PStack->top-PStack->base==PStack->stacksize)
		return FAILURE;
	*(PStack->top++)=j;
	return SUCCESS; 
}
//ջ�ĳ���
int StackLen(STACK*PStack)
{
	return PStack->top-PStack->base;
} 
//��ջ
int PopStack(STACK*PStack,int*Pk)
{
	if(PStack->top==PStack->base)
		return FAILURE;
	*Pk=*(--(PStack->top));
	return SUCCESS;	
} 
//5��������������·�����������£�
int MinShortPath(PGraph pgraph)
{
	printf("���������·����\n\n");
	int PathMatrix[pgraph->VexNum][pgraph->VexNum];//·������ 
	int DisMatrix[pgraph->VexNum][pgraph->VexNum]; //������� 
	int i,j,k;
	//��ʼ��������
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
	//����������
	for(k=0;k<pgraph->VexNum;k++)
		for(i=0;i<pgraph->VexNum;i++)
			for(j=0;j<pgraph->VexNum;j++) 
				if(DisMatrix[i][j]>DisMatrix[i][k]+DisMatrix[k][j])
				{
 					DisMatrix[i][j]=DisMatrix[i][k]+DisMatrix[k][j];
				 	PathMatrix[i][j]=k;
				}
	//׼���������������·�� 
	int Stav=-1,Endv=-1;
	char Stav_name[MAX_NAME_NUM];
	char Endv_name[MAX_NAME_NUM];
	printf("�����������յ����ƣ�\n");
	//��������ת�ɱ�� 
	scanf("%s %s",&Stav_name,&Endv_name);
	Stav=name2index(Stav_name);
	Endv=name2index(Endv_name);

 	if(Stav==-1||Endv==-1)
	 	return FAILURE;
	STACK Stack;
	if(InitStack(&Stack,pgraph->VexNum)==FAILURE)
 	{
 		printf("���棺�����Cʧ�ܣ����� \n");
	 	printf("������������˵�\n");
 		system("pause");
 	}
 	printf("\n��������̾���Ϊ%d\n",DisMatrix[Stav][Endv]);
 	while(Endv!=-1)
 	{
	 	PushStack(&Stack,Endv);
 		Endv=PathMatrix[Stav][Endv];
 	}
 	// ������·�����C�������
 	printf("���������·��Ϊ��\n");
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
 	printf("\n\n��������������˵�\n");
 	system("pause");
 	return SUCCESS; 
} 


//6�������·�޽��滮ͼ����С������ prim�㷨��
int MiniSpanTree_Prim(PGraph pgraph)
{
	int lowcost[MAX_VERTEX_NUM],closest[MAX_VERTEX_NUM];
	int i,j,k,min,v=0;//(v=0:�ӵ�һ�����㿪ʼ������������ 
	printf("�����·�޽��滮ͼ:\n");
	//��ʼ��lowcost�����closest����
	for(i=0;i<pgraph->VexNum;i++)
	{
		lowcost[i]=pgraph->Arcs[v][i];
		closest[i]=v;
	} 
	//��ʼ�ӵ㲢����lowcost��closest����
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
		//���������� 
		for(j=0;j<pgraph->VexNum;j++)
		{
			if(pgraph->Arcs[k][j]!=0&&pgraph->Arcs[k][j]<lowcost[j])
			{
				lowcost[j]=pgraph->Arcs[k][j];
				closest[j]=k;
			}	
		}	
	} 
	printf("\n\n��������������˵�\n");
 	system("pause");
 	return SUCCESS;
} 

//��ʾ����
void Frame(){
	printf("����������Ϣ����ϵͳ���ܣ�\n");
	printf("1�������������ͼ\n");
	printf("2�������������·��\n");
	printf("3���жϵ�����·ͼ���޻�·\n");
	printf("4������֮������·��\n");
	printf("5�������·�޽��滮ͼ\n");
	printf("��ѡ����Ӧ�Ĺ���\n");
	
} 

//���˵�
int Menu(PGraph pgraph){
	int select;
	while(1){
		system("cls");	//���� 
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


 
 
