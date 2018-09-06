#include <stdio.h>
#include <malloc.h>
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
    //for (i = 0; i < size; i++)
    //	printf("%d\n", nums[i]);
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int *nums;
    int size = nums1Size + nums2Size;
    nums = (int*)malloc(sizeof(int)*size);
    int i;
    for (i = 0; i < nums1Size; i++) {
        *(nums+i) = nums1[i];
        printf("%d\n", nums[i]);
    }
    printf("=%d=\n", i);
    for (; i < size; i++) {
        *(nums+i) = nums2[i-nums1Size];
        printf("%d-%d\n", nums[i],nums2[i-nums1Size]);
    }
    //for (i = 0; i < size; i++)
    //	printf("%d-",  nums[i]);
    bubble(nums, size);
    double Median;
    if (size%2 == 0)
        return (double)(nums[size/2]+nums[size/2-1])/2;
    else
        return (double)nums[size/2];
}

int main(void)
{
	int *nums1, *nums2;
	nums1 = (int*)malloc(sizeof(int)*3);
	nums2 = (int*)malloc(sizeof(int)*2);
	nums1[0] = 1;
	nums1[1] = 2;
	nums1[2] = 4;
	nums2[0] = 3;
	nums2[1] = 6;
	printf("%lf\n", findMedianSortedArrays(nums1,3,nums2,2));
	return 0;
}