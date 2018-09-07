#include <stdio.h>
#include <malloc.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmpty(Stack S);
Stack CreateStack(Stack S);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(int x, Stack S);
int Top(Stack S);
void Pop(Stack S);

struct Node {
	int x;
	PtrToNode Next;
};

int IsEmpty(Stack S) {
	return S->Next == NULL;
}

Stack CreateStack(void) {
	Stack S;
	S = (Stack)malloc(sizeof(struct Node));
	S->Next = NULL;
	MakeEmpty(S);
	return S;
}

void MakeEmpty(Stack S) {
	if (S == NULL)
		printf("Must use CreateStack first");
	else
		while (!IsEmpty(S))
			Pop(S);
}

void Push(int x, Stack S) {
	PtrToNode TmpCell;
	TmpCell = (PtrToNode)malloc(sizeof(struct Node));
	TmpCell->x = x;
	TmpCell->Next = S->Next;
	S->Next = TmpCell;
}

int Top(Stack S) {
	if (!IsEmpty(S))
		return S->Next->x;
	printf("Error : Empty Stack\n");
	return 0;
}

void Pop(Stack S) {
	PtrToNode FirstCell;
	if (IsEmpty(S))
		printf("Error : Empty Stack\n");
	else {
		FirstCell = S->Next;
		S->Next = S->Next->Next;
		free(FirstCell);
	}
}

void PrintStack(Stack S) {
	S = S->Next;
	while (S->Next != NULL) {
		printf("%d ", S->x);
		S = S->Next;
	}
	printf("%d\n", S->x);
}

int main(void)
{
	Stack S;
	int x;
	S = CreateStack();
	printf("Create the Stack : ");
	while (1) {
		scanf("%d", &x);
		if (x == -1)
			break;
		Push(x, S);
	}
	printf("The Stack is : ");
	PrintStack(S);
	printf("The top of the stack is : %d\n", Top(S));
	printf("Push : ");
	scanf("%d", &x);
	Push(x, S);
	PrintStack(S);
	printf("Pop : ");
	Pop(S);
	PrintStack(S);
	printf("MakeEmpty...\n");
	MakeEmpty(S);
	free(S);
	printf("The stack is empty now\n");
	getchar();
	getchar();
	return 0;
}
