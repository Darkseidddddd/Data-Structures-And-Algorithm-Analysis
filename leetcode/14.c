char* longestCommonPrefix(char** strs, int strsSize) {
    char *str;
    str = (char*)malloc(sizeof(char)*100);
    str[0] = '\0';
    int i, j, count = 0;
    int len = strlen(strs[0]);
    for (j = 0; j < len; j++) {
        for (i = 1; i < strsSize; i++) {
            if (strs[0][j] != strs[i][j]) {
                j = len;
                break;
            }
        }
        if (j == len)
            break;
        str[j] = strs[0][j];
    }
    return str;
}