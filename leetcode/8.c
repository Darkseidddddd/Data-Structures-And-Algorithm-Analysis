int myAtoi(char* str) {
    int i = 0, n = 0;
    int length = strlen(str);
    while (str[i++] == ' ');
    i--;
    if (str[i] <= '9' && str[i] >= '0')
        n = 1;
    if (str[i] != '-' && str[i] != '+' && !n)
        return 0;
    else if (((str[i] == '-' || str[i] == '+') && str[i+1] <= '9' && str[i+1] >= 0) || n) {
        int j = 0, sum = 0, k = i+1;
        i -= n;
        while (j+1 <= length && str[++i] <= '9' && str[i] >= '0') {
            sum *= 10;
            sum += str[i]-'0';
            if (str[i]-'0' == 0 && sum == 0)
                j--;
            if (++j >= 10) {
                if (str[k]-'0' > 2 || j == 11 || sum < 0) {
                    if (str[k-1] == '-')
                        return -2147483648;
                    return 2147483647;
                }
            }
        }
        if (str[k-1] == '-') 
            sum = 0-sum;
        return sum;
    }
    return 0;
}