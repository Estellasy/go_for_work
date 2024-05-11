#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 二分查找
// [left, right]
// while (left <= right)
// if (nums[middle] > target) 
// right 要赋值为 middle - 1

int search(vector<int>&nums, int target) {
    int left=0;
    int right=nums.size()-1;
    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (nums[middle] > target) {
            right = middle - 1;
        } else if (nums[middle] < target) {
            left = middle + 1;
        } else {
            return middle;
        }
    }
    return -1;
}