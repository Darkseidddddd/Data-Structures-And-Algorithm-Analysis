#include <stdio.h>
#include <malloc.h>

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

struct TreeNode {
	int x;
	SearchTree Left;
	SearchTree Right;
};


SearchTree MakeEmpty(SearchTree T) {
	if (T != NULL) {
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(int x, SearchTree T) {
	if (T == NULL)
		return NULL;
	if (x < T->x)
		return Find(x, T->Left);
	else if (x > T->x)
		return Find(x, T->Right);
	else
		return T;
}

Position FindMin(SearchTree T) {
	if (T == NULL)
		return NULL;
	else if (T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}

Position FindMax(SearchTree T) {
	if (T != NULL)
		while (T->Right != NULL)
			T = T->Right;
	return T;
}

SearchTree Insert(int x, SearchTree T) {
	if (T == NULL) {
		T = (SearchTree)malloc(sizeof(struct TreeNode));
		T->x = x;
		T->Right = T->Left = NULL;
	}
	else if (x < T->x)
		T->Left = Insert(x, T->Left);
	else if (x > T->x)
		T->Right = Insert(x, T->Right);
	return T;
}

SearchTree Delete(int x, SearchTree T) {
	Position TmpCell;
	if (T == NULL)
		printf("Element not found");
	else if (x < T->x)
		T->Left = Delete(x, T->Left);
	else if (x > T->x)
		T->Right = Delete(x, T->Right);
	else if (T->Left && T->Right) {
		TmpCell = FindMin(T->Right);
		T->x = TmpCell->x;
		T->Right = Delete(T->x, T->Right);
	}
	else {
		TmpCell = T;
		if (T->Left == NULL)
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(TmpCell);
	}
	return T;
}

int main(void)
{
	SearchTree T1 = NULL;
	int x;
	printf("Input the numbers(end with -1):");
	scanf("%d", &x);
	while (x != -1) {
		T1 = Insert(x, T1);
		scanf("%d", &x);
	}
	printf("Find the number:");
	scanf("%d", &x);
	SearchTree Temp;
	Temp = Find(x, T1);
	printf("-%d-\n", Temp->x);
	Temp = FindMax(T1);
	printf("max = %d\n", Temp->x);
	Temp = FindMin(T1);
	printf("Min = %d\n", Temp->x);
	printf("Delete the number:");
	scanf("%d", &x);
	T1 = Delete(x, T1);
	printf("=%d=", T1->x);
	T1 = MakeEmpty(T1);
	if (T1 == NULL)
		printf("Empty\n");
	return 0;
}
