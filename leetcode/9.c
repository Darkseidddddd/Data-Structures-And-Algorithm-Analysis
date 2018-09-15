bool isPalindrome(int x) {
    int y = x;
    if (x < 0)
        return false;
    else {
        int sum = 0;
        while (x != 0) {
            sum *= 10;
            sum += x % 10;
            x /= 10;
        }
        if (sum == y)
            return true;
    }
    return false;
}