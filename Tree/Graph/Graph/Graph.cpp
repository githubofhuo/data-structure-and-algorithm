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
	EdgeWeight	weight;		//Ȩֵ
	struct EdgeNode* next;	//ָ����һ����
} EdgeNode;

typedef string VertexType;	//��������
typedef struct
{
	VertexType data;
	EdgeNode* FirstEdge;	//ָ���һ����
} VertexNode;

typedef VertexNode AdjList[MAX_VERTEX_NUM];	//�ڽӱ�

typedef struct
{
	AdjList adjList;	//�ڽӱ�
	int VertexNum;		//�������
	int EdgeNum;		//����
} AdjListGraph;

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

	cout << "�����������㹹�ɵı�(" << G.EdgeNum << "��)" << endl;
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

		//��ͷ����
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
