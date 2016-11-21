#include <iostream>
#include <string>
#include <queue>
using namespace std;

#define MAX_VERTEX_NUM	10
#define INFINITY	0XFFFFFFFF
#define SUCCESS		1
#define UNSUCCESS	0

typedef int Status;
bool visited[MAX_VERTEX_NUM];		//全局数组记录节点是否已被访问

typedef int EdgeWeight;
typedef struct EdgeNode
{
	int adjvex;				//邻接点
	EdgeWeight	edge_weight;		//权值
	struct EdgeNode* next;	//指向下一条边
} EdgeNode;

typedef string VertexType;		//顶点类型
typedef int VertexWeight;	//顶点权值
typedef struct
{
	VertexType data;
	VertexWeight vertex_weight;	//顶点权值
	EdgeNode* FirstEdge;	//指向第一条边
} VertexNode;

typedef VertexNode AdjList[MAX_VERTEX_NUM];	//邻接表

typedef struct
{
	AdjList adjList;	//邻接表
	int VertexNum;		//顶点个数
	int EdgeNum;		//边数
} AdjListGraph;

//Prim算法
/*
	假设N={V, {E}}是连通图,TE是N上最小生成树中边的集合
	算法从U={u}, TE={}开始，重复一下操作:在所有的U和V中相连接的边中寻找一掉权值最小的边(u,v)加入TE中
	同时将v加入到U中直到U=V为止

	1、使用辅助数组closedge记录从U中到V-U中代价最小的边。(即V-U中的结点到U中哪个结点的代价最小
	2、V表示图的全部结点的集合，当有结点已经用于生成最小生成树后把结点加入U中，cloaedge的lowcost为0表示结点在U中
	3、图用邻接表存储时，要注意在每一次将节点加入U过程后对closedge中lowcost的更新。要设置一个标志，表示在当前过程该节点的lowcost是否已经被更新过，
	如果已经被更新过，则不再被更新。
*/

//此结构存放当前过程中V中各节点到U中各节点的最小权值信息
typedef struct Minimum
{
	VertexType data;		//保存U中与V中该结点相连接的结点值，使V中该结点到U中各节点间权值最小
	VertexWeight lowcost;	//两节点间的最小权值	
	int flag;				//V中该节点在某一过程中是否被更新;flag=0尚未更新,flag=1已更新
}Minimum, close_edge[MAX_VERTEX_NUM];



//由顶点的值得到顶点索引
int GetIndexByVertexVal(const AdjListGraph& G, VertexType val)
{
	for (int i = 0; i < G.VertexNum; i++)
	{
		if (val == G.adjList[i].data)
			return i;
	}
	return -1;
}

//创建有向图
Status CreateAdjListGraph(AdjListGraph& G)
{
	cout << "输入顶点个数和边数:" << endl;
	cin >> G.VertexNum >> G.EdgeNum;
	cout << "请输入" << G.VertexNum << "个顶点";
	for(int i=0; i < G.VertexNum; ++i)
	{
		cin >> G.adjList[i].data;
		G.adjList[i].FirstEdge = nullptr;
	}

	cout << "请输入图中连接弧的两个结点的值以及弧的权值： "<< endl;
	for (int i=0; i < G.EdgeNum; i++)
	{
		VertexType first;
		VertexType second;
		EdgeWeight edge_weight;
		cin >> first >> second >> edge_weight;
		int m = GetIndexByVertexVal(G, first);
		int n = GetIndexByVertexVal(G, second);
		if (m == -1 || n == -1)
			return UNSUCCESS;

		EdgeNode* edge_node = new EdgeNode;
		edge_node->adjvex = n;
		edge_node->edge_weight = edge_weight;

		//表头插入
		edge_node->next = G.adjList[m].FirstEdge;
		G.adjList[m].FirstEdge = edge_node;
	}
}

//寻找V中各节点到U中各节点间最小的权值，返回结点的编号
int minimum(AdjListGraph G, close_edge MinEdge)
{
	int i, j, first, min;
	for(i=0; i < G.VertexNum; i++)
	{
		//MinEdge[i].lowcost==0说明编号为i的结点在U中
		if(MinEdge[i].lowcost != 0)
		{
			min = MinEdge[i].lowcost;
			first = i;
			break;
		}
	}
	j = i;
	for(i = first; i < G.VertexNum; i++)
	{
		if (min > MinEdge[i].lowcost && MinEdge[i].lowcost != 0)
		{
			min = MinEdge[i].lowcost;
			j = i;
		}
	}
	return j;
}


//从图中结点u开始生成最小生成树的过程
struct MST
{
	int total_cost;
	vector<VertexNode> mst_list[MAX_VERTEX_NUM];
};

void MinSpanTree(AdjListGraph G, VertexType u)
{
	int i, k;
	EdgeNode *pnode;
	close_edge MinEdge;

	k = GetIndexByVertexVal(G, u);
	for (int i=0; i < G.VertexNum; i++)
	{
		MinEdge[i].flag = 0;	//访问标志初始化为0
	}
	for (i=0; i < G.VertexNum; i++)
	{
		if (i != k)
		{
			MinEdge[i].data = u;
			for (pnode = G.adjList[i].FirstEdge; pnode != nullptr; pnode = pnode->next)
			{
				//p->adjvex==k说明编号为i的结点与编号为k的结点间连接，需要把MinEdge的lowcost修改为边上的权值
				if (pnode->adjvex == k)
				{
					MinEdge[i].lowcost = pnode->edge_weight;
					MinEdge[i].flag = 1;
				}
				else if (MinEdge[i].flag == 0)
					MinEdge[i].lowcost = INFINITY;
			}
		}
		MinEdge[k].data = G.adjList[k].data;
		MinEdge[k].lowcost = 0;
	}
	for(i=1; i<G.VertexNum;i++)
	{
		k = minimum(G, MinEdge);
		cout << G.adjList[k].data << " " << MinEdge[k].data << " " << MinEdge[k].lowcost << endl;
		//将节点加入到U中
		MinEdge[k].lowcost = 0;
		for (pnode = G.adjList[k].FirstEdge; pnode != nullptr; pnode = pnode->next)
		{
			if (MinEdge[pnode->adjvex].lowcost > pnode->edge_weight)
			{
				MinEdge[pnode->adjvex].lowcost = pnode->edge_weight;
				MinEdge[pnode->adjvex].data = G.adjList[k].data;
			}
		}
	}
}
void DestoryGraph(AdjListGraph& G)
{
	for (int i=0; i < G.VertexNum; i++)
	{
		EdgeNode* edge_node = G.adjList[i].FirstEdge;
		while (edge_node)
		{
			EdgeNode* q = edge_node;
			edge_node = edge_node->next;
			delete q;
		}
		G.adjList[i].FirstEdge = nullptr;
	}
	G.VertexNum = 0;
	G.EdgeNum = 0;
}

//得到顶点的度
int GetVertexDegree(const AdjListGraph& G, VertexType val)
{
	//顶点下标
	int m = GetIndexByVertexVal(G, val);
	int count = 0;

	for(int i=0; i < G.VertexNum; i++)
	{
		//出度
		if (i == m)
		{
			EdgeNode* edge_out_node = G.adjList[i].FirstEdge;
			while(edge_out_node)
			{
				++count;			//出度
				edge_out_node = edge_out_node->next;
			}
		}
		else
		{
			EdgeNode* edge_in_node = G.adjList[i].FirstEdge;
			while(edge_in_node)
			{
				if (edge_in_node->adjvex == m)
					++count;		//入度
				edge_in_node = edge_in_node->next;
			}
		}
	}
	return count;
}

void DFS(const AdjListGraph& G, int i)
{
	cout << G.adjList[i].data << " ";
	visited[i] = true;

	EdgeNode* edge_node = G.adjList[i].FirstEdge;
	while (edge_node)
	{
		int j = edge_node->adjvex;
		if (!visited[j])
		{
			DFS(G, j);
		}
		edge_node = edge_node->next;
	}
}

void DFSTraverse(const AdjListGraph& G)
{
	for(int i=0; i < G.VertexNum; ++i)
	{
		visited[i] = false;
	}

	for (int i=0; i < G.VertexNum; i++)
	{
		if (!visited[i])
			DFS(G, i);
	}
}

//广度优先遍历
//从点V0出发遍历其指向的切未访问的点,以这些点为V0继续直至遍历全部点
void BFSTraverse(const AdjListGraph& G)
{
	for (int i = 0; i < G.VertexNum; i++)
		visited[i] = false;

	queue<int> Q;
	for (int i=0; i < G.VertexNum; i++)
	{
		if (!visited[i])
		{
			cout << G.adjList[i].data << " ";
			visited[i] = true;
			Q.push(i);

			while (!Q.empty())
			{
				int vex = Q.front();
				Q.pop();

				EdgeNode* edge_node = G.adjList[vex].FirstEdge;
				while (edge_node)
				{
					if (!visited[edge_node->adjvex])
					{
						cout << G.adjList[edge_node->adjvex].data << " ";
						visited[edge_node->adjvex] = true;
						Q.push(edge_node->adjvex);
					}
					edge_node = edge_node->next;
				}
			}
		}
	}
}


// Finding closed tours rooted at r with each having the bounded total cost
int find_closed_tours_and_calculate_cost(AdjListGraph G, VertexNode root, double delta)
{
	int total_cost;
}

int main()
{
	//创建有向图
	AdjListGraph G;
	CreateAdjListGraph(G);

	//深度优先搜索
	DFSTraverse(G);
	cout << endl;

	//广度优先搜索
	BFSTraverse(G);
	cout << endl;

	//节点的度
	cout << "输入求节点的度:";
	VertexType v;
	cin >> v;
	cout << "度为:" << GetVertexDegree(G, v) << endl;
	
	//销毁有向图
	DestoryGraph(G);

	return 0;
}


