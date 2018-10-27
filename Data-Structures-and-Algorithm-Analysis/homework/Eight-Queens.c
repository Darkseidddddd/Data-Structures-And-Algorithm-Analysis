#include <stdio.h>
#include <malloc.h>
#define Max 8
int total = 1;

int Is_ok(int *col, int row, int i) {
	int j = 0;
	for (; j < row; j++) {
		if (col[j] == i || col[j] + j == i + row || col[j] - j == i - row)
			return 0;
	}
	return 1;
}

void Print(int *col) {
	int i = 0;
	printf("%d: ", total++);
	for (; i < Max - 1; i++) {
		printf("%d ", col[i]);
	}
	printf("%d\n", col[i]);
}

void Queen(int *col, int row) {
	int i = 0;
	if (row == Max)
		Print(col);
	for (; i < Max; i++) {
		col[row] = i;
		if (!Is_ok(col, row, i))
			continue;
		Queen(col, row + 1);
	}
}

int main()
{
	int *col;
	col = (int*)malloc(sizeof(int)*Max);
	Queen(col, 0);
	return 0;
}