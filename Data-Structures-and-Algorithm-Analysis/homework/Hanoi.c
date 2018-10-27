#include <stdio.h>
int times = 0;

void move(char begin, char final) {
	times++;
	printf("%d step: %c-->%c\n", times, begin, final);
}

void Hanoi(int n, char a, char b, char c) {
	if (n == 1)
		move(a, c);
	else {
		Hanoi(n - 1, a, c, b);
		move(a, c);
		Hanoi(n - 1, b, a, c);
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	Hanoi(n, 'A', 'B', 'C');
	printf("%d", times);
	return 0;
}