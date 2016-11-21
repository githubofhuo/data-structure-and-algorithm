#include <iostream>
#include <cstdlib>
#define ERROR 1;  
typedef char VertexType;
typedef int InfoType;
typedef int VRType;
using namespace std;

typedef struct ArcNode {
	int adjvex;    //图中的弧所依附的顶点的编号  
	InfoType weight;   //弧上所带的权值  
	struct ArcNode *nextarc;  //指向下一条弧的指针  
}ArcNode;

typedef struct VNode {
	VertexType data;  //弧中结点的值  
	ArcNode *firstarc; //指向依附于该顶点的第一条弧的指针  
}VNode, AdjVex[20];  //定义存放顶点信息的数组  

typedef struct {
	int vexnum, arcnum;  //弧的结点数和弧数  
	AdjVex vertices;    //存放图中结点信息的数组  
}ALGraph;

typedef struct Minimum { //此结构存放当前过程中V中各节点到U中各节点的最小权值信息  
	VertexType data;    //保存U中与V中该结点相连接的结点值，使V中该结点到U中各节点间权值最小  
	VRType lowcost;     //保存两结点间最小的权值(代价)  
	int flag;           //表示V中该结点在某一过程中是否被更新的标志，flag=0表示尚未更新，flag=1表示已经更新，不用再更新了，图使用邻接表存储时要注意设置此标志，以免某一结点的minimum结构被更新多次，得不到正确的最小权值  
}Minimum, closedge[20];

int LocateVex(ALGraph G, VertexType u) {  //确定结点u在图中的编号  
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
	cout << "请输入图的结点个数和弧的个数：";
	cin >> G.vexnum;
	cin >> G.arcnum;
	cout << "请输入图的各个结点的值：";
	for (i = 0; i<G.vexnum; i++) {
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	for (k = 0; k<G.arcnum; k++) {
		cout << "请输入图中连接弧的两个结点的值以及弧的权值：";
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

int minimum(ALGraph G, closedge MinEdge) {  //寻找V中各节点到U中各节点间最小的权值，返回结点的编号  
	int i, j, first, min;
	for (i = 0; i<G.vexnum; i++) {
		if (MinEdge[i].lowcost != 0) {  //MinEdge[i].lowcost==0说明编号为i的结点在U中  
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

void MinSpanTree(ALGraph G, VertexType u) {  //从图中结点u开始生成最小生成树的过程  
	int i, k;
	ArcNode *p;
	closedge MinEdge;
	k = LocateVex(G, u);
	for (i = 0; i<G.vexnum; i++)
		MinEdge[i].flag = 0;  //访问标志初始化为0  
	for (i = 0; i<G.vexnum; i++) {
		if (i != k) {
			MinEdge[i].data = u;
			for (p = G.vertices[i].firstarc; p != NULL; p = p->nextarc) {
				if (p->adjvex == k) {   //p->adjvex==k说明编号为i的结点与编号为k的结点间有弧连接，需要把MinEdge的lowcost修改为弧上的权值  
					MinEdge[i].lowcost = p->weight;
					MinEdge[i].flag = 1;    //设置标志，表示编号为i的结点在这一过程中已更新过权值  
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
		MinEdge[k].lowcost = 0;   //将结点加入U中  
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
	cout << "图的最小生成树的边为：" << endl;
	MinSpanTree(G, G.vertices[0].data);
	return 0;
}
*/