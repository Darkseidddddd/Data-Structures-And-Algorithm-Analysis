int min(int a, int b) {
    return a < b ? a : b;
}
int maxArea(int* height, int heightSize) {
    int i = 0, max = 0;
    while (i < heightSize) {
        int s = (heightSize-1-i)*min(height[heightSize-1],height[i]);
        max = max > s ? max : s;
        if (height[heightSize-1] > height[i])
            i++;
        else
            heightSize--;
    }
    return max;
}