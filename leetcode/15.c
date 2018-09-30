/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
void quickSort(int* nums, int first, int end) {  
    int temp, l, r;  
    if (first >= end)
        return;  
    temp = nums[first];  
    l = first;
    r = end;  
    while(l < r) {  
        while(l < r && nums[r] >= temp)
            r--;  
        if(l < r)
            nums[l]=nums[r];  
        while(l < r && nums[l] <= temp)
            l++;  
        if(l < r)
            nums[r]=nums[l];  
    }  
    nums[l] = temp;  
    quickSort(nums, first, l-1);  
    quickSort(nums, l+1, end);  
} //快排代码,思路：每次挖一个坑，然后看坑里应该放谁，当从两头挖的坑汇聚到一起，坑里的萝卜就是有序的了;
int** threeSum(int* nums, int numsSize, int* returnSize) {  
    int i, sum, top=-1, begin, end;  
    int **res=(int**)malloc(sizeof(int*)*(numsSize*(numsSize-1)*(numsSize-2))/6);//这里的内存分配最大值为c n 3,即排列组合知识;  
    if(numsSize < 3) {  
        *returnSize = 0;  
        return res;  
    }  //组内元素小于三时直接返回;
    quickSort(nums, 0, numsSize-1);//快排;  
    for(i = 0; i < numsSize; i++) {  
        if(nums[i] > 0)
            break;//首元素大于0，跳出for，已经查找到所有符合条件的三元组;  
        if(i > 0 && nums[i] == nums[i-1])
            continue; //与上次判定一致，直接跳过，执行i++; 
        begin = i+1;
        end = numsSize-1; //固定i后在i+1/尾两处放入指针，开始循环; 
        while(begin < end) {  
            sum = nums[i] + nums[begin] + nums[end];  
            if(sum == 0){  
                top++;  
                res[top] = (int*)malloc(sizeof(int)*3);  
                res[top][0] = nums[i];
                res[top][1] = nums[begin];
                res[top][2] = nums[end];  
                begin++;
                end--;  
                while(begin < end && nums[begin] == nums[begin-1])
                    begin++;  
                while(begin < end && nums[end] == nums[end+1])
                    end--;  
            } else if (sum > 0)
                end--;  
            else 
                begin++;  
        } //while 
    } //for 
    *returnSize = top+1; //top作为计数器，即为需要返回的长度; 
    return res;  
}  