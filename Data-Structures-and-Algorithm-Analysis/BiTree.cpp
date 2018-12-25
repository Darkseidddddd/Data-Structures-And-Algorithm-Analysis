//1 2 4 -1 -1 5 6 -1 -1 -1 3 -1 7 8 -1 -1 9 -1 -1
#include <stdio.h>
#include <malloc.h>

struct TreeNode;
typedef struct TreeNode *BiTree;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

typedef struct StackNode *Stack;
typedef struct QueueNode *Queue;

struct TreeNode {
	int x;
	Position Left;
	Position Right;
};

struct StackNode {
	Position P;
	int tag;
	Stack next;
};

struct QueueNode {
	Position P;
	Queue Tail;
	Queue next;
};

void MakeEmpty(BiTree T) {
	if (T != NULL) {
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
		T = NULL;
	}
}
/*
BiTree InsertTree(int x, BiTree T) {
	if (T == NULL) {
		T = (BiTree)malloc(sizeof(struct TreeNode));
		T->Left = T->Right = NULL;
		T->x = x;
	}
	else if (x < T->x) {
		T->Left = InsertTree(x, T->Left);
	}
	else {
		T->Right = InsertTree(x, T->Right);
	}
	return T;
}
*/

BiTree InsertTree(int x, BiTree T) {
	if (T == NULL) {
		T = (Position)malloc(sizeof(struct TreeNode));
		T->Right = T->Left = NULL;
		T->x = x;
	}
	else if (T->Right == NULL && T->Left != NULL)
		T->Right = InsertTree(x, T->Right);
	else
		T->Left = InsertTree(x, T->Left);
	return T;
}

void PreOrderTraverse(BiTree T) {
	if (T) {
		printf("%d ", T->x);
		PreOrderTraverse(T->Left);
		PreOrderTraverse(T->Right);
	}
}

void InOrderTraverse(BiTree T) {
	if (T) {
		InOrderTraverse(T->Left);
		printf("%d ", T->x);
		InOrderTraverse(T->Right);
	}
}

void PostOrderTraverse(BiTree T) {
	if (T) {
		PostOrderTraverse(T->Left);
		PostOrderTraverse(T->Right);
		printf("%d ", T->x);
	}
}

Stack InitStack(void) {
	Stack S;
	S = (Stack)malloc(sizeof(struct StackNode));
	S->next = NULL;
	return S;
}

void PushStack(Stack S, Position P, int tag) {
	Stack temp;
	temp = (Stack)malloc(sizeof(struct StackNode));
	temp->P = P;
	temp->tag = tag;
	temp->next = S->next;
	S->next = temp;
}

Position PopStack(Stack S, int *tag) {
	Position P = S->next->P;
	if (tag)
		*tag = S->next->tag;
	Stack temp = S->next;
	S->next = S->next->next;
	free(temp);
	return P;
}

bool StackEmpty(Stack S) {
	return S->next == NULL;
}

void PreOrderTraverse_nrec(BiTree T) {
	Stack S = InitStack();
	Position P = T;
	while (P || !StackEmpty(S)) {
		if (P) {
			printf("%d ", P->x);
			PushStack(S, P, 0);
			P = P->Left;
		}
		else {
			P = PopStack(S, NULL);
			P = P->Right;
		}
	}
}

void InOrderTraverse_nrec(BiTree T) {
	Stack S = InitStack();
	Position P = T;
	while (P || !StackEmpty(S)) {
		if (P) {
			PushStack(S, P, 0);
			P = P->Left;
		}
		else {
			P = PopStack(S, NULL);
			printf("%d ", P->x);
			P = P->Right;
		}
	}
}

void PostOrderTraverse_nrec(BiTree T) {
	Stack S = InitStack();
	Position P = T;
	int tag = 0;
	while (P || !StackEmpty(S)) {
		while (P) {
			PushStack(S, P, tag);
			P = P->Left;
		}
		tag = 1;
		while (!StackEmpty(S) && tag == 1) {
			P = PopStack(S, &tag);
			if (tag == 0) {
				PushStack(S, P, 1);
				P = P->Right;
			}
			else {
				printf("%d ", P->x);
				P = NULL;
			}
		}
	}
}

Queue InitQueue(void) {
	Queue Q;
	Q = (Queue)malloc(sizeof(struct StackNode));
	Q->next = NULL;
	Q->Tail = Q;
	return Q;
}

void EnQueue(Position P, Queue Q) {
	Queue temp;
	temp = (Queue)malloc(sizeof(struct StackNode));
	temp->P = P;
	Q->Tail->next = temp;
	Q->Tail = temp;
	temp->next = NULL;
}

Position DeQueue(Queue Q) {
	Position P = Q->next->P;
	Queue temp = Q->next;
	Q->next = Q->next->next;
	if (Q->next == NULL)
		Q->Tail = Q;
	free(temp);
	return P;
}

bool EmptyQueue(Queue Q) {
	return Q->next == NULL;
}

void LevelOrderTraverse(BiTree T) {
	Queue Q = InitQueue();
	Position P = T;
	if (P) EnQueue(P, Q);
	while (!EmptyQueue(Q)) {
		P = DeQueue(Q);
		printf("%d ", P->x);
		if (P->Left) EnQueue(P->Left, Q);
		if (P->Right) EnQueue(P->Right, Q);
	}
}

BiTree CreateBiTree_PreOrder(void) {
	int x;
	scanf("%d", &x);
	BiTree T;
	if (x != -1) {
		T = (BiTree)malloc(sizeof(struct TreeNode));
		T->x = x;
		T->Left = CreateBiTree_PreOrder();
		T->Right = CreateBiTree_PreOrder();
	}
	else
		T = NULL;
	return T;
}

BiTree Copy_Tree(BiTree T) {
	if (T) {
		BiTree NewPosition;
		NewPosition = (BiTree)malloc(sizeof(struct TreeNode));
		NewPosition->x = T->x;
		NewPosition->Left = Copy_Tree(T->Left);
		NewPosition->Right = Copy_Tree(T->Right);
	}
	return T;
}

int DepthTree(BiTree T) {
	if (T != NULL) {
		int m = DepthTree(T->Left);
		int n = DepthTree(T->Right);
		return m > n ? m + 1 : n + 1;
	}
	return 0;
}

int TreeNodeCount(BiTree T) {
	if (T) return TreeNodeCount(T->Left) + TreeNodeCount(T->Right) + 1;
	return 0;
}

void PrintTree(BiTree T) {
	PreOrderTraverse(T);
	printf("\n");
	InOrderTraverse(T);
	printf("\n");
	PostOrderTraverse(T);
	printf("\n");
	PreOrderTraverse_nrec(T);
	printf("\n");
	InOrderTraverse_nrec(T);
	printf("\n");
	PostOrderTraverse_nrec(T);
	printf("\n");
	LevelOrderTraverse(T);
	printf("\n");
}

BiTree InputTree(void) {
	BiTree T = NULL;
	printf("Insert the tree: ");
	int x;
	while (1) {
		scanf("%d", &x);
		if (x == -1)
			break;
		T = InsertTree(x, T);
	}
	return T;
}

int main(void) {
	BiTree T = CreateBiTree_PreOrder();
	BiTree NewT = Copy_Tree(T);
	PrintTree(T);
	printf("\n");
	PrintTree(NewT);
	printf("Depth: %d\nNodeCount: %d\n", DepthTree(T), TreeNodeCount(T));
	return 0;
}






