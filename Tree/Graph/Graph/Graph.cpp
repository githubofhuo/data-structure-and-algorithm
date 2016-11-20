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
	EdgeWeight	weight;		//权值
	struct EdgeNode* next;	//指向下一条边
} EdgeNode;

typedef string VertexType;	//顶点类型
typedef struct
{
	VertexType data;
	EdgeNode* FirstEdge;	//指向第一条边
} VertexNode;

typedef VertexNode AdjList[MAX_VERTEX_NUM];	//邻接表

typedef struct
{
	AdjList adjList;	//邻接表
	int VertexNum;		//顶点个数
	int EdgeNum;		//边数
} AdjListGraph;

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

	cout << "请输入由两点构成的边(" << G.EdgeNum << "条)" << endl;
	for (int i=0; i < G.EdgeNum; i++)
	{
		VertexType first;
		VertexType second;
		cin >> first >> second;
		int m = GetIndexByVertexVal(G, first);
		int n = GetIndexByVertexVal(G, second);
		if (m == -1 || n == -1)
			return UNSUCCESS;

		EdgeNode* edge_node = new EdgeNode;
		edge_node->adjvex = n;
		edge_node->weight = 0;

		//表头插入
		edge_node->next = G.adjList[m].FirstEdge;
		G.adjList[m].FirstEdge = edge_node;
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
