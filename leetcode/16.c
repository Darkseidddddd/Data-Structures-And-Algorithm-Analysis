void sort(int *nums, int numsSize) {
    int i, j;
    for (i = numsSize-1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (nums[j] > nums[j+1]) {
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
            }
        }
    }
}
int threeSumClosest(int* nums, int numsSize, int target) {
    sort(nums, numsSize);
    int i = 0, j = numsSize-1, k;
    int sum = nums[0]+nums[1]+nums[2];
    int sum_diff = sum-target;
    for (k = 1; k < j; k++) {
        while (i != k && j != k) {
            int diff = nums[i] + nums[j] + nums[k] - target;
            if (abs(diff) < abs(sum_diff)) {
                sum = diff + target;
                sum_diff = diff;
            }
            if (diff == 0)
                return sum;
            else if (diff > 0) {
                j--;
            } else {
                i++;
            }
        }
        i = 0;
        j = numsSize-1;
    }
    return sum;
}