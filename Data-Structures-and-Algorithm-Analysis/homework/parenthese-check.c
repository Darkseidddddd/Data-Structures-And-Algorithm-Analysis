#include <stdio.h>
#include <malloc.h>
int Bracket(int *bracket) {
	char ch;
	while ((ch = getchar()) != '\n') {
		switch (ch)
		{
		case '(': bracket[0]++; break;
		case '[': bracket[1]++; break;
		case '{': bracket[2]++; break;
		case ')': if (--bracket[0] < 0) return 0; else break;
		case ']': if (--bracket[1] < 0) return 0; else break;
		case '}': if (--bracket[2] < 0) return 0; else break;
		}
	}
	return 1;
}
int main()
{
	int *bracket;
	bracket = (int*)malloc(sizeof(int) * 3);
	bracket[0] = bracket[1] = bracket[2] = 0;
	int falg = Bracket(bracket);
	if (falg && !(bracket[0] || bracket[1] || bracket[2]))
		printf("Successfully\n");
	else
		printf("Failed\n");
	return 0;
}