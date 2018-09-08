#include <stdio.h>
#include <malloc.h>

struct QueueRecord;
typedef struct QueueRecord *Queue;
int IsEmpty(Queue Q);
int IsFull(Queue Q);
Queue CreateQueue(Queue Q);
void DisposeQueue(Queue Q);
void MakeQueue(Queue Q);
void Enqueue(int x, Queue Q);
int Front(Queue Q);
void Dequeue(Queue Q);
int FrontAndDequeue(Queue Q);

struct QueueRecord {
	int Capacity;
	int Front;
	int Rear;
	int Size;
	int *Array;
};


int IsEmpty(Queue Q) {
	return Q->Size == 0;
}

int IsFull(Queue Q) {
	return Q->Size == Q->Capacity;
}

void MakeEmpty(Queue Q) {
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}

static int Succ(int Value, Queue Q) {
	if (++Value == Q->Capacity)
		Value = 0;
	return Value;
}

void Enqueue(int x, Queue Q) {
	if (IsFull(Q))
		printf("Error : Full queue\n");
	else {
		Q->Size++;
		Q->Rear = Succ(Q->Rear, Q);
		Q->Array[Q->Rear] = x;
	}
}

Queue MakeQueue(int Capacity) {
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QueueRecord));
	Q->Capacity = Capacity;
	Q->Array = (int*)malloc(sizeof(int)*Capacity);
	return Q;
}

void PrintQueue(Queue Q) {
	int i, j = Q->Front;
	for (i = 1; i <= Q->Size; i++,j++) {
		printf("%d-%d ", j, Q->Array[j]);
		if (j+1 == Q->Capacity)
			j = -1;
	}
	printf("\n");
}

void DisposeQueue(Queue Q)
{
	if (Q != NULL) {
		free(Q->Array);
		free(Q);
	}
}

int main(void)
{
	Queue Q;
	int Capacity, x, i;
	printf("Create a Queue(Input the capacity) : ");
	scanf("%d", &Capacity);
	Q = MakeQueue(Capacity);
	MakeEmpty(Q);
	printf("Enqueue(end with -1) : ");
	for (i = 1; i <= Capacity; i++) {
		scanf("%d", &x);
		if (x == -1)
			break;
		Enqueue(x, Q);
	}
	printf("The Queue is : ");
	PrintQueue(Q);
	printf("Enqueue : ");
	scanf("%d", &x);
	Enqueue(x, Q);
	printf("The new queue is : ");
	PrintQueue(Q);
	printf("DisposeQueue...\n");
	DisposeQueue(Q);
	printf("Down");
	return 0;
}


