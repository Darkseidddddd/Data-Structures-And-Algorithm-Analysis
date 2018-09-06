int judge(char *s, int i, int j) {
	int k;
	for (; i < j; i++) {
		for (k = i+1; k <= j; k++) {
			if (s[i] == s[k])
				return 0;
		}
	}
	return 1;
}
int lengthOfLongestSubstring(char* s) {
    int length = strlen(s);
	int i, j = 0, max = 0;
	for (i = 0; i < length; i++) {
		for (; j < length; j++) {
			max = (max > (j-i+1)) ? max : (j-i+1);
			if (!judge(s,i,j+1)) {
				j++;
				break;
			}
		}
		if (j == length)
			break;
	}
	return max;

}