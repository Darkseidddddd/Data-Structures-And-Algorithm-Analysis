#include <stdio.h>
#include <malloc.h>
int n = 0;
int mark = 0;
void BackBag(int *weights, int i, int T, int length, int *bag) {
	if (T == 0) {
		mark = 1;
		int j = 0;
		while (j < n - 1) { 
			printf("%d ", bag[j++]);
		}
		printf("%d\n", weights[i - 1]);
		return;
	}
	else if (T < 0) { return; }
	while (i < length && T >= 0) {
		bag[n++] = weights[i];
		BackBag(weights, i + 1, T - weights[i], length, bag);
		n--;
		i++;                                                                 
	}
}
int main()
{
	int n, weight;
	scanf("%d%d", &n, &weight);
	int *weights, *bag;
	weights = (int*)malloc(sizeof(int)*n);
	bag = (int*)malloc(sizeof(int)*n);
	int i = -1;
	while (++i < n)
		scanf("%d", &weights[i]);
	BackBag(weights, 0, weight, n, bag);
	if (!mark)
		printf("No solution");
	return 0;
}
