#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MVNum 100

typedef struct ArcNode *Arc;
typedef struct VNode *VerTex, AdjList[MVNum];
typedef struct Graph *ALGraph;

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

struct Graph{
	AdjList vertices;
	int vexnum, arcnum;
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

int main(void) 
{
	ALGraph G = CreateUDG();
	return 0;
}