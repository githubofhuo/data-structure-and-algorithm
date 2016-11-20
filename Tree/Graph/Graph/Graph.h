#ifndef GRAPH_H
#define GRAPH_H

#define MaxVertexNum 100

typedef struct Node
{
	int dest;
	int weight;
	struct Node *next;
} Edge;
#endif
