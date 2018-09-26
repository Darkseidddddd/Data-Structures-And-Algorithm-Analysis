char* intToRoman(int num) {
    char *str;
    str = (char*)malloc(sizeof(char)*20);
    int i = 0;
    if (num/1000) {
        int j = num/1000;
        while (j-- > 0)
            str[i++] = 'M';
    }
    num %= 1000;
    if (num/100) {
        int j = num/100;
        if (j == 4) {
            str[i++] = 'C';
            str[i++] = 'D';
        } else if (j == 9) {
            str[i++] = 'C';
            str[i++] = 'M';
        } else {
            if (j >= 5) {
                str[i++] = 'D';
                j -= 5;
            }
            while (j-- > 0)
                str[i++] = 'C';
        }
    }
    num %= 100;
    if (num/10) {
        int j = num/10;
        if (j == 4) {
            str[i++] = 'X';
            str[i++] = 'L';
        } else if (j == 9) {
            str[i++] = 'X';
            str[i++] = 'C';
        } else {
            if (j >= 5) {
                str[i++] = 'L';
                j -= 5;
            }
            while (j-- > 0)
                str[i++] = 'X';
        }
    }
    num %= 10;
    if (num == 4) {
        str[i++] = 'I';
        str[i++] = 'V';
    } else if (num == 9) {
        str[i++] = 'I';
        str[i++] = 'X';
    } else {
        if (num >= 5) {
            str[i++] = 'V';
            num -= 5;
        }
        while (num-- > 0)
            str[i++] = 'I';
    }
    str[i] = '\0';
    return str;
}