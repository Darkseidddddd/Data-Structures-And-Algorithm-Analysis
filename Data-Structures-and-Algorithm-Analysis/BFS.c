#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MVNum 100

typedef struct ArcNode *Arc;
typedef struct VNode *VerTex, AdjList[MVNum];
typedef struct Graph *ALGraph;
typedef struct QueueNode *Queue;

int visited[MVNum];

struct ArcNode {
	int adjvex;
	Arc nextarc;
	int info;
};

struct VNode {
	int data;
	Arc firstarc;
};

struct Graph {
	AdjList vertices;
	int vexnum, arcnum;
};

struct QueueNode {
	int x;
	Queue Next;
};


int LocateVex(ALGraph G, int v) {
	int i;
	for (i = 0; i < G->vexnum; i++) {
		if (G->vertices[i].data == v)
			return i;
	}
	return -1;
}

ALGraph CreateUDG(void) {	//创建无向图
	ALGraph G;
	G = (ALGraph)malloc(sizeof(struct Graph));
	scanf("%d%d", &G->vexnum, &G->arcnum);
	int i, j, k;
	for (i = 0; i < G->vexnum; i++) {
		scanf("%d", &G->vertices[i].data);
		G->vertices[i].firstarc = NULL;
	}
	for (k = 0; k < G->arcnum; k++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		Arc p1;
		p1 = (Arc)malloc(sizeof(struct ArcNode));
		p1->adjvex = j;
		p1->nextarc = G->vertices[i].firstarc; G->vertices[i].firstarc = p1;
		Arc p2;
		p2 = (Arc)malloc(sizeof(struct ArcNode));
		p2->adjvex = i;
		p2->nextarc = G->vertices[j].firstarc; G->vertices[j].firstarc = p2;
	}
	return G;
}

Queue CreateQueue(void) {
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QueueNode));
	Q->Next = NULL;
	return Q;
}

void EnQueue(Queue Q, int x) {
	Queue temp;
	temp = (Queue)malloc(sizeof(struct QueueNode));
	temp->Next = Q->Next;
	Q->Next = temp;
}

int DeQueue(Queue Q) {
	if (Q->Next == NULL)
		return -1;
	Queue temp = Q->Next;
	Q->Next = Q->Next->Next;
	int x = temp->x;
	free(temp);
	return x;
}

bool EmptyQueue(Queue Q) {
	return Q->Next == NULL;
}

int FirstAdjVex(ALGraph G, int v) {
	if (v < G->vexnum)
		return G->vertices[v].firstarc->adjvex;
	return -1;
}

int NextAdjVex(ALGraph G, int v, int w) {
	Arc temp = G->vertices[v].firstarc;
	while (temp->adjvex != w) temp = temp->nextarc;
	if (temp->nextarc)
		return temp->nextarc->adjvex;
	return -1;
}

void BFS(ALGraph G, int v) {
	Queue Q = CreateQueue();
	EnQueue(Q, v);
	while (!EmptyQueue(Q)) {
		int u = DeQueue(Q);
		int w;
		for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)) {
			if (!visited[w]) {
				visited[w] = 1;
				EnQueue(Q, w);
			}
		}
	}
}

int main(void)
{
	ALGraph G = CreateUDG();
	int v;
	scanf("%d", &v);
	BFS(G, v); //从v结点开始广度优先遍历连通图
	return 0;
}

