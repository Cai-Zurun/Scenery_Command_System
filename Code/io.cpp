#include "hashtable.h"
#include "io.h"
#include "math.h"
#include "malloc.h"

// some functions use this static hashtable
hashtable * t =hashtable_create();

int route_split(char *buffer,route * record){
	char src_name[MAX_NAME_NUM];
	char dst_name[MAX_NAME_NUM];
	char weight[32];
	int sum=0;
	
	// �����ע����  ��ֱ��������������һ����ʾ���8 
	if (buffer[0]=='#') {
		printf("annotation found");
		return 0;
	}
	int i =0;
	// �ַ������� ��src_name 
	while(buffer[i]!=9 && buffer[i]!=32){
		src_name[i]=buffer[i];
		i++;
	}
	src_name[i]='\0';
	while (buffer[i]==9 || buffer[i]==32) i++;
	
	// �ַ������Ƶ� dst_name 
	int g=0;
	while(buffer[i]!=32 && buffer[i]!=9){
		dst_name[g]=buffer[i];
		i++;
		g++;
	}
	dst_name[g]='\0';
	
	//�����м�Ŀո� �� tab 
	while (buffer[i]==9 || buffer[i]==32) i++;
	// �ַ�����ʽ��ʽ������ ת�������� 
	int length=0;
	while(buffer[i]!='\n' && buffer[i]!='\0'){
		weight[length]=buffer[i];
		i++;
		length++;
	}
	sum = str2int(weight);
	 	
	record->src = (long long)hashtable_get(t,src_name);
	record->dst = (long long)hashtable_get(t,dst_name);
	record->weight = sum;
	
	return 1;
}


// ���رߵĸ��� �߶���д��ṹ������routes�� 
int parseRoute(route * routes){
	FILE * routes_file = fopen(ROUTEFILE,"r");
	char buffer[1024];
	int count=0;
	while(fgets(buffer,1024,routes_file)){
		if (route_split(buffer,routes+count)) count++;
	} 
	return count;
}


int str2int(char *str){
	int length = strlen(str); 
	int sum=0;
	for (int k=length-1;k>=0;k--){
		sum+=pow(10,length-k-1)*(str[k]-'0');
	}
	return sum;
	}


// ����ڵ㱻ע�� ���� 0 
// �������� ���� 0 
int node_split(char * buffer , node * record,char * point_name){
	if (buffer[0]=='#') return 0;
 	char pos_x[16]; 
 	char pos_y[16]; 
	int x;
 	int y;
	// ��ʼ�� pointer 
	int i=0;
	
	//���������ַ�  ֪������ �ո� ���� tab 
	while(buffer[i]!=32 && buffer[i]!=9){
		point_name[i] = buffer[i];
		i++;
	 }
	 point_name[i]='\0';
	 
	//�����м�� �ո� ���� tab 
	while(buffer[i]==32 ||buffer[i]==9) i++;
	
	//�������� 
	
	// ���� ( , )	
	while(buffer[i]=='(' ||buffer[i] == ')' || buffer[i]==',') i++;
	
	int k=0;
	while((buffer[i]<='9' &&buffer[i]>='0')) {
		pos_x[k]=buffer[i];
		k++;
		i++;
	}
	pos_x[k]='\0';
	
	while(buffer[i]=='(' ||buffer[i] == ')' || buffer[i]==',') i++;
	
	int g=0;
	while((buffer[i]<='9' &&buffer[i]>='0')) {
		pos_y[g]=buffer[i];
		g++;
		i++;
	}
	pos_y[g]='\0';
	x = str2int(pos_x);
	y = str2int(pos_y); 
	record->x= x;
	record->y= y;
	strcpy(record->point_name,point_name);
	return 1;
}



// ֱ���޸ľ�̬�����Ĺ�ϣ��
// ע���ȼ�����û�б�ע��
int  parseNode(node * nodes){
 	FILE * node_file = fopen(POINTFILE,"r");
 	// ����
	int count =0; 
 	char buffer[1024];
 	while(fgets(buffer,1024,node_file)){
 		char * point_name = (char*)malloc(MAX_NAME_NUM);
 		if (node_split(buffer , nodes+count,point_name)){
 			hashtable_set(t,point_name,(void *)count);
 			(nodes+count)->index = count;
 			count++;
		 }
		}
	return count; 
  }
  
  
// ���� ָ��ͼ��ָ�� �ṹ������nodes �ṹ������routes 
int loadFromFile(PGraph pgraph,node * nodes , route * routes){
	int node_num = parseNode(nodes);
	int route_num = parseRoute(routes);
	
	pgraph->VexNum = node_num;
	pgraph->ArcNum = route_num;
	
	// assign name
	for (int k=0;k<node_num;k++){
		strcpy((char *)((pgraph->Vexs)+k),nodes[k].point_name);
	}
	
	//��ʼ������Ȩֵ���Խ���Ϊ0������Ϊ�����
	for(int i=0;i<MAX_VERTEX_NUM;i++)
		for(int j=0;j<MAX_VERTEX_NUM;j++)
			pgraph->Arcs[i][j]=INF;
	for(int i=0;i<MAX_VERTEX_NUM;i++)
		pgraph->Arcs[i][i]=0;
		
	// ʹ��routes�ṹ������ ��ɳ�ʼ��ֵ
	// ��
	for (int i =0;i<route_num;i++){
		pgraph->Arcs[routes[i].src][routes[i].dst]=routes[i].weight;
		pgraph->Arcs[routes[i].dst][routes[i].src]=routes[i].weight; 
	} 
		
		
	return SUCCESS;
}
  
int name2index(char*scen_name){
	return (long long)hashtable_get(t,scen_name);
} 
