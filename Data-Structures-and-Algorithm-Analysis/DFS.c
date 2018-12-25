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

ALGraph CreateUDG(void) {
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

void DFS(ALGraph G, int v) {
	visited[v] == 1;
	int w;
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
		if (!visited[w]) DFS(G, w, visited);
	}
}

int main(void)
{
	ALGraph G = CreateUDG();
	int v;
	scanf("%d", &v);
	DFS(G, v, visited); //从v结点开始深度优先搜索
	return 0;
}

