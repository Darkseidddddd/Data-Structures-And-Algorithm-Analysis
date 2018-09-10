int Count(int x) {
    int i = 0;
    while (x != 0) {
        x /= 10;
        i++;
    }
    return i;
}

int rev(int x) {
    int result = 0;
    while (x != 0) {
        result = result*10 + x%10;
        x /= 10;
    }
    return result;
}

int reverse(int x) {
    int length = Count(x);
    int z = rev(x);
    if (length == 10) {
        if (x % 10 > 2 || x % 10 < -2)
            return 0;
        else {
            int y = rev(abs(x)); 
            return y < 0 ? 0 : z;
        }
    } else {
        return z;
    }
}