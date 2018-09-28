int number(char str) {
    int i = 0;
    char list[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    int num[7] = {1,5,10,50,100,500,1000};
    while (i < 7) {
        if (list[i] == str)
            return num[i];
        i++;
    }
    return 0;
}

int romanToInt(char* s) {
    int i = 1, result = 0;
    int len = strlen(s);
    result += number(s[0]);
    while (i < len) {
        int a = number(s[i-1]), b = number(s[i]);
        result += b;
        if (a < b)
            result -= 2*a;
        i++;
    }
    return result;
}