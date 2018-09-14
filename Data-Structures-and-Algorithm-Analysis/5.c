#include <stdio.h>
#include <malloc.h>


struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

AvlTree MakeEmpty(AvlTree T);
Position Find(int x, AvlTree T);
Position FIndMin(AvlTree T);
Position FimdMax(AvlTree T);
AvlTree Insert(int x, AvlTree T);
AvlTree Delete(int x, AvlTree T);

struct AvlNode {
	int x;
	AvlTree Left;
	AvlTree Right;
	int Height;
};

int Max(int a, int b) {
	return a > b ? a : b;
}

int Height(Position P) {
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

Position SingleRotateWithLeft(Position K2) {
	Position K1;
	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Left), K2->Height) + 1;
	return K1;
}

Position SingleRotateWithRight(Position K2) {
	Position K1;
	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;
	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Right), K2->Height) + 1;
	return K1;
}

Position DoubleRotateWithLeft(Position K3) {
	K3->Left = SingleRotateWithRight(K3->Left);
	return SingleRotateWithLeft(K3);
}

Position DoubleRotateWithRight(Position K3) {
	K3->Right = SingleRotateWithLeft(K3->Right);
	return SingleRotateWithRight(K3);

}

AvlTree Insert(int x, AvlTree T) {
	if (T == NULL) {
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		T->x = x;
		T->Height = 0;
		T->Left = T->Right = NULL;
	} else if (x < T->x) {
		T->Left = Insert(x, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2)
			if (x < T->Left->x)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
	} else if (x > T->x) {
		T->Right = Insert(x, T->Right);
		if (Height(T->Right) - Height(T->Left) == 2)
			if (x > T->Right->x)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
	}

	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

void print(AvlTree T) {
	if (T != NULL) {
		print(T->Left);
		print(T->Right);
		printf("%d ", T->x);
	}
}

Position Find(int x, AvlTree T) {
	Position P = T;
	if (x < T->x)
		P = Find(x, T->Left);
	else if (x > T->x)
		P = Find(x, T->Right);
	return P;
}

Position FindMin(AvlTree T) {
	if (T == NULL)
		return NULL;
	while (T->Left != NULL)
		T = T->Left;
	return T;
}

Position FindMax(AvlTree T) {
	if (T == NULL)
		return NULL;
	while (T->Right != NULL)
		T = T->Right;
	return T;
}


AvlTree MakeEmpty(AvlTree T) {
	if (T->Left != NULL)
		T->Left = MakeEmpty(T->Left);
	else if (T->Right != NULL)
		T->Right = MakeEmpty(T->Right);
	free(T);
	return NULL;
}

int main(void)
{
	int x;
	AvlTree T = NULL;
	printf("Input the AvlTree(end with -1) : ");
	while (1) {
		scanf("%d", &x);
		if (x == -1)
			break;
		T = Insert(x, T);
	}
	printf("The AvlTree is : ");
	print(T);
	printf("\nInsert one element : ");
	scanf("%d", &x);
	T = Insert(x, T);
	printf("The new AvlTree is : ");
	print(T);
	printf("\nThe new AvlTree is : ");
	print(T);
	printf("\nWhat number do you want to find ? ");
	scanf("%d", &x);
	printf("number %d is found.\n", Find(x, T)->x);
	printf("The max is : %d\nThe min is : %d\n", FindMax(T)->x, FindMin(T)->x);
	printf("MakeEmpty...");
	if (MakeEmpty(T) == NULL)
		printf("Successfully\n");
	else
		printf("Failed\n");
	return 0;
}
