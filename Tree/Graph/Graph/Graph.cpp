#include <iostream>
#include <string>
#include <queue>
using namespace std;

#define MAX_VERTEX_NUM	10
#define INFINITY	0XFFFFFFFF
#define SUCCESS		1
#define UNSUCCESS	0

typedef int Status;
bool visited[MAX_VERTEX_NUM];		//ȫ�������¼�ڵ��Ƿ��ѱ�����

typedef int EdgeWeight;
typedef struct EdgeNode
{
	int adjvex;				//�ڽӵ�
	EdgeWeight	edge_weight;		//Ȩֵ
	struct EdgeNode* next;	//ָ����һ����
} EdgeNode;

typedef string VertexType;		//��������
typedef int VertexWeight;	//����Ȩֵ
typedef struct
{
	VertexType data;
	VertexWeight vertex_weight;	//����Ȩֵ
	EdgeNode* FirstEdge;	//ָ���һ����
} VertexNode;

typedef VertexNode AdjList[MAX_VERTEX_NUM];	//�ڽӱ�

typedef struct
{
	AdjList adjList;	//�ڽӱ�
	int VertexNum;		//�������
	int EdgeNum;		//����
} AdjListGraph;

//Prim�㷨
/*
	����N={V, {E}}����ͨͼ,TE��N����С�������бߵļ���
	�㷨��U={u}, TE={}��ʼ���ظ�һ�²���:�����е�U��V�������ӵı���Ѱ��һ��Ȩֵ��С�ı�(u,v)����TE��
	ͬʱ��v���뵽U��ֱ��U=VΪֹ

	1��ʹ�ø�������closedge��¼��U�е�V-U�д�����С�ıߡ�(��V-U�еĽ�㵽U���ĸ����Ĵ�����С
	2��V��ʾͼ��ȫ�����ļ��ϣ����н���Ѿ�����������С��������ѽ�����U�У�cloaedge��lowcostΪ0��ʾ�����U��
	3��ͼ���ڽӱ�洢ʱ��Ҫע����ÿһ�ν��ڵ����U���̺��closedge��lowcost�ĸ��¡�Ҫ����һ����־����ʾ�ڵ�ǰ���̸ýڵ��lowcost�Ƿ��Ѿ������¹���
	����Ѿ������¹������ٱ����¡�
*/

//�˽ṹ��ŵ�ǰ������V�и��ڵ㵽U�и��ڵ����СȨֵ��Ϣ
typedef struct Minimum
{
	VertexType data;		//����U����V�иý�������ӵĽ��ֵ��ʹV�иý�㵽U�и��ڵ��Ȩֵ��С
	VertexWeight lowcost;	//���ڵ�����СȨֵ	
	int flag;				//V�иýڵ���ĳһ�������Ƿ񱻸���;flag=0��δ����,flag=1�Ѹ���
}Minimum, close_edge[MAX_VERTEX_NUM];



//�ɶ����ֵ�õ���������
int GetIndexByVertexVal(const AdjListGraph& G, VertexType val)
{
	for (int i = 0; i < G.VertexNum; i++)
	{
		if (val == G.adjList[i].data)
			return i;
	}
	return -1;
}

//��������ͼ
Status CreateAdjListGraph(AdjListGraph& G)
{
	cout << "���붥������ͱ���:" << endl;
	cin >> G.VertexNum >> G.EdgeNum;
	cout << "������" << G.VertexNum << "������";
	for(int i=0; i < G.VertexNum; ++i)
	{
		cin >> G.adjList[i].data;
		G.adjList[i].FirstEdge = nullptr;
	}

	cout << "������ͼ�����ӻ�����������ֵ�Լ�����Ȩֵ�� "<< endl;
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

		//��ͷ����
		edge_node->next = G.adjList[m].FirstEdge;
		G.adjList[m].FirstEdge = edge_node;
	}
}

//Ѱ��V�и��ڵ㵽U�и��ڵ����С��Ȩֵ�����ؽ��ı��
int minimum(AdjListGraph G, close_edge MinEdge)
{
	int i, j, first, min;
	for(i=0; i < G.VertexNum; i++)
	{
		//MinEdge[i].lowcost==0˵�����Ϊi�Ľ����U��
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


//��ͼ�н��u��ʼ������С�������Ĺ���
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
		MinEdge[i].flag = 0;	//���ʱ�־��ʼ��Ϊ0
	}
	for (i=0; i < G.VertexNum; i++)
	{
		if (i != k)
		{
			MinEdge[i].data = u;
			for (pnode = G.adjList[i].FirstEdge; pnode != nullptr; pnode = pnode->next)
			{
				//p->adjvex==k˵�����Ϊi�Ľ������Ϊk�Ľ������ӣ���Ҫ��MinEdge��lowcost�޸�Ϊ���ϵ�Ȩֵ
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
		//���ڵ���뵽U��
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

//�õ�����Ķ�
int GetVertexDegree(const AdjListGraph& G, VertexType val)
{
	//�����±�
	int m = GetIndexByVertexVal(G, val);
	int count = 0;

	for(int i=0; i < G.VertexNum; i++)
	{
		//����
		if (i == m)
		{
			EdgeNode* edge_out_node = G.adjList[i].FirstEdge;
			while(edge_out_node)
			{
				++count;			//����
				edge_out_node = edge_out_node->next;
			}
		}
		else
		{
			EdgeNode* edge_in_node = G.adjList[i].FirstEdge;
			while(edge_in_node)
			{
				if (edge_in_node->adjvex == m)
					++count;		//���
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

//������ȱ���
//�ӵ�V0����������ָ�����δ���ʵĵ�,����Щ��ΪV0����ֱ������ȫ����
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
	//��������ͼ
	AdjListGraph G;
	CreateAdjListGraph(G);

	//�����������
	DFSTraverse(G);
	cout << endl;

	//�����������
	BFSTraverse(G);
	cout << endl;

	//�ڵ�Ķ�
	cout << "������ڵ�Ķ�:";
	VertexType v;
	cin >> v;
	cout << "��Ϊ:" << GetVertexDegree(G, v) << endl;
	
	//��������ͼ
	DestoryGraph(G);

	return 0;
}


