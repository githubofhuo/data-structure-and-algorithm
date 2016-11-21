#include <iostream>
#include <cstdlib>
#define ERROR 1;  
typedef char VertexType;
typedef int InfoType;
typedef int VRType;
using namespace std;

typedef struct ArcNode {
	int adjvex;    //ͼ�еĻ��������Ķ���ı��  
	InfoType weight;   //����������Ȩֵ  
	struct ArcNode *nextarc;  //ָ����һ������ָ��  
}ArcNode;

typedef struct VNode {
	VertexType data;  //���н���ֵ  
	ArcNode *firstarc; //ָ�������ڸö���ĵ�һ������ָ��  
}VNode, AdjVex[20];  //�����Ŷ�����Ϣ������  

typedef struct {
	int vexnum, arcnum;  //���Ľ�����ͻ���  
	AdjVex vertices;    //���ͼ�н����Ϣ������  
}ALGraph;

typedef struct Minimum { //�˽ṹ��ŵ�ǰ������V�и��ڵ㵽U�и��ڵ����СȨֵ��Ϣ  
	VertexType data;    //����U����V�иý�������ӵĽ��ֵ��ʹV�иý�㵽U�и��ڵ��Ȩֵ��С  
	VRType lowcost;     //������������С��Ȩֵ(����)  
	int flag;           //��ʾV�иý����ĳһ�������Ƿ񱻸��µı�־��flag=0��ʾ��δ���£�flag=1��ʾ�Ѿ����£������ٸ����ˣ�ͼʹ���ڽӱ�洢ʱҪע�����ô˱�־������ĳһ����minimum�ṹ�����¶�Σ��ò�����ȷ����СȨֵ  
}Minimum, closedge[20];

int LocateVex(ALGraph G, VertexType u) {  //ȷ�����u��ͼ�еı��  
	int i;
	for (i = 0; i<G.vexnum; i++) {
		if (G.vertices[i].data == u)
			return i;
	}
	return ERROR;
}

void CreateGraph(ALGraph &G) {
	VertexType v1, v2;
	InfoType w;
	ArcNode *p, *q;
	int i, j, k;
	cout << "������ͼ�Ľ������ͻ��ĸ�����";
	cin >> G.vexnum;
	cin >> G.arcnum;
	cout << "������ͼ�ĸ�������ֵ��";
	for (i = 0; i<G.vexnum; i++) {
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	for (k = 0; k<G.arcnum; k++) {
		cout << "������ͼ�����ӻ�����������ֵ�Լ�����Ȩֵ��";
		p = (ArcNode *)malloc(sizeof(ArcNode));
		q = (ArcNode *)malloc(sizeof(ArcNode));
		if (!p || !q)
			exit(0);
		cin >> v1;
		cin >> v2;
		cin >> w;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		p->nextarc = G.vertices[i].firstarc;
		q->nextarc = G.vertices[j].firstarc;
		G.vertices[i].firstarc = p;
		p->weight = w;
		p->adjvex = j;
		G.vertices[j].firstarc = q;
		q->weight = w;
		q->adjvex = i;
	}
}

int minimum(ALGraph G, closedge MinEdge) {  //Ѱ��V�и��ڵ㵽U�и��ڵ����С��Ȩֵ�����ؽ��ı��  
	int i, j, first, min;
	for (i = 0; i<G.vexnum; i++) {
		if (MinEdge[i].lowcost != 0) {  //MinEdge[i].lowcost==0˵�����Ϊi�Ľ����U��  
			min = MinEdge[i].lowcost;
			first = i;
			break;
		}
	}
	j = i;
	for (i = first; i<G.vexnum; i++) {
		if (min>MinEdge[i].lowcost&&MinEdge[i].lowcost != 0) {
			min = MinEdge[i].lowcost;
			j = i;
		}
	}
	return j;
}

void MinSpanTree(ALGraph G, VertexType u) {  //��ͼ�н��u��ʼ������С�������Ĺ���  
	int i, k;
	ArcNode *p;
	closedge MinEdge;
	k = LocateVex(G, u);
	for (i = 0; i<G.vexnum; i++)
		MinEdge[i].flag = 0;  //���ʱ�־��ʼ��Ϊ0  
	for (i = 0; i<G.vexnum; i++) {
		if (i != k) {
			MinEdge[i].data = u;
			for (p = G.vertices[i].firstarc; p != NULL; p = p->nextarc) {
				if (p->adjvex == k) {   //p->adjvex==k˵�����Ϊi�Ľ������Ϊk�Ľ����л����ӣ���Ҫ��MinEdge��lowcost�޸�Ϊ���ϵ�Ȩֵ  
					MinEdge[i].lowcost = p->weight;
					MinEdge[i].flag = 1;    //���ñ�־����ʾ���Ϊi�Ľ������һ�������Ѹ��¹�Ȩֵ  
				}
				else if (MinEdge[i].flag == 0)
					MinEdge[i].lowcost = 100;
			}
		}
		MinEdge[k].data = G.vertices[k].data;
		MinEdge[k].lowcost = 0;
	}
	for (i = 1; i<G.vexnum; i++) {
		k = minimum(G, MinEdge);
		cout << G.vertices[k].data << "  " << MinEdge[k].data << "  " << MinEdge[k].lowcost << endl;
		MinEdge[k].lowcost = 0;   //��������U��  
		for (p = G.vertices[k].firstarc; p != NULL; p = p->nextarc) {
			if (MinEdge[p->adjvex].lowcost>p->weight) {
				MinEdge[p->adjvex].lowcost = p->weight;
				MinEdge[p->adjvex].data = G.vertices[k].data;
			}
		}
	}
}
/*
int main() {
	ALGraph G;
	CreateGraph(G);
	cout << "ͼ����С�������ı�Ϊ��" << endl;
	MinSpanTree(G, G.vertices[0].data);
	return 0;
}
*/