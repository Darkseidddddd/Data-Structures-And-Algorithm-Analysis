#include <stdio.h>
#include <malloc.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;

struct Node {
	int Element[2];
	Position next;
};

List CreatList() {
	List L;
	L = (List)malloc(sizeof(struct Node));
	L->next = NULL;
	L->Element[0] = 0;
	return L;
}

List MakeList() {
	List Head = CreatList();
	List L = Head;
	int coefficient, index;
	while (1) {
		scanf("%d", &coefficient);
		if (coefficient == 0)
			break;
		scanf("%d", &index);
		PtrToNode Ptr;
		Ptr = (PtrToNode)malloc(sizeof(struct Node));
		Ptr->Element[0] = coefficient;
		Ptr->Element[1] = index;
		Ptr->next = NULL;
		L->next = Ptr;
		L = L->next;
	}
	return Head;
}


Position Find(int x, List L) {
	Position P = L;
	while (P->next != NULL) {
		if (P->next->Element[1] > x)
			break;
		P = P->next;
	}
	return P;
}

void insert(Position P, int Element[]) {
	if (P->Element[0] != 0 && P->Element[1] == Element[1])
			P->Element[0] += Element[0];
	else {
		PtrToNode temp;
		temp = (PtrToNode)malloc(sizeof(struct Node));
		temp->Element[0] = Element[0];
		temp->Element[1] = Element[1];
		temp->next = P->next;
		P->next = temp;
	}
}
List Multiplication(List A, List B) {
	PtrToNode listA = A->next, listB = B->next;
	List C = CreatList();
	int result[2];
	while (listB != NULL) {
		while (listA != NULL) {
			result[0] = listA->Element[0] * listB->Element[0];
			result[1] = listA->Element[1] + listB->Element[1];
			Position temp = Find(result[1], C);
			insert(temp, result);
			listA = listA->next;
		}
		listA = A->next;
		listB = listB->next;
	}
	return C;
}

void print(List L) {
	PtrToNode P = L->next;
	while (P != NULL) {
		if (P->Element[1] == 0)
			printf("%d", P->Element[0]);
		else 
			printf("%dx^%d", P->Element[0], P->Element[1]);
		if (P->next != NULL)
			printf("+");
		P = P->next;
	}
	printf("\n");
}
int main(void)
{
	List A, B, C;
	A = MakeList();
	B = MakeList();
	C = Multiplication(A, B);
	print(C);
	return 0;
}

