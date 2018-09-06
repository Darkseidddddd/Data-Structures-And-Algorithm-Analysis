void bubble(int* nums, int size) {
    int i, j;
    for (i = size-1; i >= 1; i--) {
        for (j = 0; j < i; j++) {
            if (nums[j] > nums[j+1]) {
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
            }
        }
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int *nums;
    int size = nums1Size + nums2Size;
    nums = (int*)malloc(sizeof(int)*size);
    int i;
    for (i = 0; i < nums1Size; i++)
        nums[i] = nums1[i];
    for (; i < size; i++)
        nums[i] = nums2[i-nums1Size];
    bubble(nums, size);
    double Median;
    if (size%2 == 0)
        return (double)(nums[size/2]+nums[size/2-1])/2;
    else
        return (double)nums[size/2];
}