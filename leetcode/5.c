char* longestPalindrome(char* s) {
    int length = strlen(s);
    int start = 0, end = 0;
    int i, j, k, max = 1;
    
    for (i = 1; i < length; i++) {
        j = i-1;
        k = i+1;
        while (j >= 0 && k < length) {
            if (s[j] == s[k]) {
                if (k-j+1 > max) {
                    max = k-j+1;
                    start = j;
                    end = k;
                }    
                j--;
                k++;
            } else {
                break;
            }
        }
    }
    
    for (i = 0; i < length; i++) {
        j = i;
        k = i+1;
        while (j >= 0 && k < length) {
            if (s[j] == s[k]) {
                if (k-j+1 > max) {
                    max = k-j+1;
                    start = j;
                    end = k;
                }
                j--;
                k++;
            } else {
                break;
            }
        }
    }
    char* str;
    str = (char*)malloc(sizeof(char)*(end-start+2));
    for (i = start; i <= end; i++)
        str[i-start] = s[i];
    str[max] = '\0';
    return str;
}