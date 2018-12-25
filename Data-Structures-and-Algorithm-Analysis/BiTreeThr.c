//1 2 4 -1 -1 5 6 -1 -1 7 -1 -1 3 8 -1 -1 9 -1 10 11 -1 -1 -1
#include <stdio.h>
#include <malloc.h>

typedef struct TreeNode *BiThrTree;
typedef struct TreeNode *BiThrNode;
typedef struct TreeNode *Position;

BiThrNode Pre;

struct TreeNode {
	int x;
	BiThrNode Left;
	BiThrNode Right;
	int LTag, RTag;
};

BiThrTree CreateBiTree_PreOrder(void) {
	int x;
	scanf("%d", &x);
	BiThrTree T;
	if (x != -1) {
		T = (BiThrTree)malloc(sizeof(struct TreeNode));
		T->x = x;
		T->Left = CreateBiTree_PreOrder();
		T->Right = CreateBiTree_PreOrder();
	}
	else
		T = NULL;
	return T;
}


void InThreading(BiThrTree P) {
	if (P) {
		InThreading(P->Left);
		if (!P->Left) {
			P->LTag = 1;
			P->Left = Pre;
		}
		else
			P->LTag = 0;
		if (!Pre->Right) {
			Pre->RTag = 1;
			Pre->Right = P;
		}
		else
			Pre->RTag = 0;
		Pre = P;
		InThreading(P->Right);
	}
}

BiThrTree InOrderThreading(BiThrTree T) {
	BiThrTree Head;
	Head = (BiThrTree)malloc(sizeof(struct TreeNode));
	Head->Right = Head;
	Head->RTag = 1;
	Head->LTag = 0;
	if (!T) Head->Left = Head;
	else {
		Head->Left = T;
		Pre = Head;
		InThreading(T);
		Pre->Right = Head;
		Pre->RTag = 1;
		Head->Right = Pre;
	}
	return Head;
}

void InOrderTraverse_Thr(BiThrTree T) {
	BiThrNode P = T->Left;
	while (P != T) {
		while (P->LTag == 0) P = P->Left;
		printf("%d ", P->x);
		while (P->RTag == 1 && P->Right != T) {
			P = P->Right;
			printf("%d ", P->x);
		}
		P = P->Right;
	}
}

int main(void) {
	BiThrTree T = CreateBiTree_PreOrder();
	BiThrTree Thrt = InOrderThreading(T);
	InOrderTraverse_Thr(Thrt);
	return 0;
}
