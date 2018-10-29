#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct Node *Stack;
typedef struct Node *List;
typedef Stack PtrToNode;

struct Node {
	int n;
	PtrToNode next;
};

Stack CreatStack_List(void) {
	Stack S;
	S = (Stack)malloc(sizeof(struct Node));
	S->next = NULL;
	return S;
}

void Push_Stack(Stack S, int n) {
	PtrToNode temp = CreatStack_List();
	temp->n = n;
	temp->next = S->next;
	S->next = temp;
}

void Push_List(List L, int n) {
	PtrToNode temp = CreatStack_List();
	temp->n = n;
	while (L->next != NULL)
		L = L->next;
	L->next = temp;
	temp->next = NULL;
}

void Pop(Stack S) {
	PtrToNode temp = S->next;
	S->next = S->next->next;
	free(temp);
}

void Print_List(List L) {
	while (L->next->next != NULL) {
		printf("%d ", L->next->n);
		L = L->next;
	}
	printf("%d\n", L->next->n);
}

void Creat_temp_stack(Stack S1, Stack S2) {
	if (S1->next->next != NULL)
		Creat_temp_stack(S1->next, S2);
	Push_Stack(S2, S1->next->n);
}

void Creat_temp_list(List L1, List L2) {
	while (L1->next != NULL) {
		Push_List(L2, L1->next->n);
		L1 = L1->next;
	}
}

void Pop_List(List L) {
	PtrToNode temp = L->next;
	L->next = L->next->next;
	free(temp);
}

void Print(Stack S, List L_in, List L_out) {
	if (L_in->next == NULL) {
		if (S->next == NULL)
			Print_List(L_out);
		else {
			Push_List(L_out, S->next->n);
			Pop(S);
			Print(S, L_in, L_out);
		}
	}
	else {
		if (S->next != NULL) {
			Stack S_temp = CreatStack_List();
			List L1_temp = CreatStack_List();
			List L2_temp = CreatStack_List();
			Creat_temp_stack(S, S_temp);
			Creat_temp_list(L_in, L1_temp);
			Creat_temp_list(L_out, L2_temp);
			Push_List(L2_temp, S_temp->next->n);
			Pop(S_temp);
			Print(S_temp, L1_temp, L2_temp);
		}
		Push_Stack(S, L_in->next->n);
		Pop_List(L_in);
		Print(S, L_in, L_out);
	}
}

void Creat_List_in(List L) {
	int n, i = 1;
	scanf("%d", &n);
	for (; i <= n; i++)
		Push_List(L, i);
	
}

int main()
{
	List L_in = CreatStack_List();
	List L_out = CreatStack_List();
	Stack S = CreatStack_List();
	Creat_List_in(L_in);
	Print(S, L_in, L_out);
	return 0;
}