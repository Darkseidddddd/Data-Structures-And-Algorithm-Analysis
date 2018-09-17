#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty(List L);
int IsEmpty(List L);
Position Find(int x, List L);
void Delete(int x, List L);
Position FindPrevious(int x, List L);
void Insert(int x, List L, Position P);
void DeleteList(List L);
List MakeList(void);
void PrintList(List L);


struct Node {
	int x;
	Position Next;
};

int IsEmpty(List L) {
	return L->Next == NULL;
}

int IsLast(Position P, List L) {
	return P->Next == NULL;
}

Position Find(int x, List L) {
	Position P;
	P = L->Next;
	while (P != NULL && P->x != x)
		P = P->Next;
	return P;
}

void Delete(int x, List L) {
	Position P, TmpCell;
	P = FindPrevious(x, L);
	if (!IsLast(P, L)) {
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	} else {
		TmpCell = P->Next;
		P->Next = NULL;
		free(TmpCell);
	}
}

Position FindPrevious(int x, List L) {
	Position P;
	P = L;
	while (P->Next != NULL && P->Next->x != x)
		P = P->Next;
	return P;
}

void Insert(int x, List L, Position P) {
	Position TmpCell;
	TmpCell = (Position)malloc(sizeof(struct Node));
	TmpCell->x = x;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}

void DeleteList(List L) {
	Position P, Tmp;
	P = L->Next;
	L->Next = NULL;
	free(L);
	while (P != NULL) {
		Tmp = P;
		P = P->Next;
		free(Tmp);
	}
}

List MakeList(void) {
	List L, head;
	L = (List)malloc(sizeof(struct Node));
	head = L;
	int x;
	while (1) {
		scanf("%d", &x);
		if (x == -1)
			break;
		List Tmp;
		Tmp = (List)malloc(sizeof(struct Node));
		Tmp->x = x;
		Tmp->Next = NULL;
		L->Next = Tmp;
		L = L->Next;
	}
	return head;
}

void PrintList(List L) {
	L = L->Next;
	while (L->Next != NULL) {
		printf("%d ", L->x);
		L = L->Next;
	}
	printf("%d\n", L->x);
}

int main(void)
{
	List L;
	Position P;
	int x, y;
	printf("Input the chain table(end with -1):");
	L = MakeList();
	printf("The chain table is :");
	PrintList(L);
	printf("What number do you want to find ? ");
	scanf("%d", &x);
	P = Find(x, L);
	printf("Successfully Found : %d\n", P->x);
	printf("Insert one number : ");
	scanf("%d", &x);
	printf("Where do want to insert ? ");
	scanf("%d", &y);
	P = Find(y, L);
	Insert(x, L, P);
	printf("The new chain table is : ");
	PrintList(L);
	printf("Delete one number : ");
	scanf("%d", &x);
	Delete(x, L);
	printf("The new chain table is : ");
	PrintList(L);
	printf("Delete the list...\n");
	DeleteList(L);
	printf("Successfully Deleted");
	return 0;

}