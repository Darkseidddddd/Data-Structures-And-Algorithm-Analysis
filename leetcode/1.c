int* twoSum(int* nums, int numsSize, int target) {
    int i,j;
    int *Nums;
    Nums = (int*)malloc(sizeof(int)*2);
    for (i = 0; i < numsSize; i++) {
        for (j = i+1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                Nums[0] = i;
                Nums[1] = j;
                return Nums;
            }
        }
    }
    return NULL;
}