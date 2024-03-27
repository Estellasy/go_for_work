/*
239. 滑动窗口的最大值
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
返回 滑动窗口中的最大值 。

示例 1：

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
示例 2：

输入：nums = [1], k = 1
输出：[1]

思路：
建立大顶堆
如何判断大顶堆top是否在当前滑动窗口？
*/

#include <iostream>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> maxHeap; // 优先队列默认大顶堆
        for (int i = 0; i < k; ++i) {
            maxHeap.emplace(nums[i], i);
        }
        vector<int> ans = {maxHeap.top().first};
        for (int i = k; i < nums.size(); ++i) {
            maxHeap.emplace(nums[i], i);
            while (maxHeap.top().second <= i-k) {
                maxHeap.pop();
            }
            ans.push_back(maxHeap.top().first);
        }
        return ans;
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {9,10,9,-7,-4,-8,2,-6};
    int k1 = 5;
    vector<int> result1 = solution.maxSlidingWindow(nums1, k1);
    cout << "Test Case 1: [1, 3, -1, -3, 5, 3, 6, 7] with k = 5\n";
    cout << "Expected Output: [3, 3, 5, 5, 6, 7]\n";
    cout << "Actual Output: ";
    for (int num : result1) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> nums2 = {1};
    int k2 = 1;
    vector<int> result2 = solution.maxSlidingWindow(nums2, k2);
    cout << "\nTest Case 2: [1] with k = 1\n";
    cout << "Expected Output: [1]\n";
    cout << "Actual Output: ";
    for (int num : result2) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}