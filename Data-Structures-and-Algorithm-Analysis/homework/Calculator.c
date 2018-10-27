#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct Node;
typedef struct Node *Stack;
typedef struct Node *List;
typedef struct Node *PtrToNode, *Position;

struct Node {
	char s;
	double n;
	PtrToNode next;
};

Stack Creat_List_Stack(void) {
	Stack S;
	S = (Stack)malloc(sizeof(struct Node));
	S->next = NULL;
	return S;
}

void Insert_List(char x, double n, Position P) {
	PtrToNode temp;
	temp = (PtrToNode)malloc(sizeof(struct Node));
	temp->s = x;
	if (x == '#') {
		temp->n = n;
	}
	temp->next = NULL;
	P->next = temp;
}

void Push_Stack(Stack S, char s, double n) {
	PtrToNode Temp;
	Temp = (PtrToNode)malloc(sizeof(struct Node));
	if (s != '#')
		Temp->s = s;
	else
		Temp->n = n;
	Temp->next = S->next;
	S->next = Temp;
}

void Pop_Stack(Stack S) {
	if (S->next != NULL) {
		PtrToNode Temp;
		Temp = S->next;
		S->next = S->next->next;
		free(Temp);
	}
}

int GetPriority(char s) {
	switch (s)
	{
	case 's':
	case 'c':
	case 'n':
	case 'o': return 0;
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	case '(': return 4;
	default: return -1;
	}
}

int Index(double x, int y) {
	double sum = 1.0;
	while (y-- > 0) {
		sum *= x;
	}
	return sum;
}

List Input(void) {
	char ch;
	int flag = 0, i = 0;
	double n = 0.0;
	Stack S = Creat_List_Stack();
	List L = Creat_List_Stack();
	List tail = L;
	while ((ch = getchar()) != '=') {
		if (ch == '.') {
			flag = 1;
			continue;
		}
		if (ch == 'l')
			continue;
		if (ch <= '9' && ch >= '0') {
			n = n * 10.0 + (double)(ch - '0');
			i += flag;
			continue;
		}
		if (n != 0) {
			if (i != 0)
				n /= Index(10.0,i);
			Insert_List('#', n, tail);
			tail = tail->next;
			i = flag = 0;
			n = 0.0;
		}
		if (ch == '(')
			Push_Stack(S, ch, 0);
		else if (ch == ')') {
			while (S->next != NULL) {
				if (S->next->s == '(') {
					Pop_Stack(S);
					break;
				}
				Insert_List(S->next->s, 0, tail);
				tail = tail->next;
				Pop_Stack(S);
			}
		}
		else if (ch == 's' || ch == 'c' || ch == 'n' || ch == 'o') {
			Push_Stack(S, '(', 0);
			Push_Stack(S, ch, 0);
			while (1) {
				if ((ch = getchar()) == '(')
					break;
			}
		}
		else {
			if (S->next == NULL)
				Push_Stack(S, ch, 0);
			else if (GetPriority(ch) <= GetPriority(S->next->s) && S->next->s != '(') {
				Insert_List(S->next->s, 0, tail);
				tail = tail->next;
				Pop_Stack(S);
				Push_Stack(S, ch, 0);
			}
			else {
				Push_Stack(S, ch, 0);
			}
		}
	}
	if (n != 0) {
		if (i != 0)
			n /= Index(10.0, i);
		Insert_List('#', n, tail);
		tail = tail->next;
	}
	while (S->next != NULL) {
		Insert_List(S->next->s, 0, tail);
		tail = tail->next;
		Pop_Stack(S);
	}
	return L;
}

double Calculate(char s, Stack S) {
	double a = S->next->n , b;
	if (S->next->next != NULL)
		b = S->next->next->n;
	Pop_Stack(S);
	switch (s)
	{
	case '+': Pop_Stack(S); return a + b;
	case '-': Pop_Stack(S); return b - a;
	case '*': Pop_Stack(S); return b * a;
	case '/': Pop_Stack(S); return b / a;
	case 'c': return cos(a);
	case 's': return sin(a);
	case 'n': return log(a);
	case 'o': return log10(a);
	case '^': Pop_Stack(S); return Index(b, (int)a);
	}
	return 0;
}

double Calculate_Result(List L) {
	Stack S = Creat_List_Stack();
	while (L->next != NULL) {
		if (L->next->s == '#')
			Push_Stack(S, '#', L->next->n);
		else
			Push_Stack(S, '#', Calculate(L->next->s, S));
		L = L->next;
	}
	return S->next->n;
}

int main(void)
{
	List L = Input();
	double result = Calculate_Result(L);
	printf("%lf\n", result);
	return 0;
}