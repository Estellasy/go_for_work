/*
347. 前k个高频元素
给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

示例 1:

输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
示例 2:

输入: nums = [1], k = 1
输出: [1]
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 计数
        unordered_map<int, int> mp;
        for (auto num:nums) {
            if (mp.find(num) != mp.end()) {
                mp[num]++;
            } else {
                mp[num] = 1;
            }
        }

        // 创建最小堆
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        for (auto kv : mp) {
            if (minHeap.size() < k) {
                minHeap.push(make_pair(kv.second, kv.first));
            } else {
                if (kv.second > minHeap.top().first) {
                    minHeap.pop();
                    minHeap.push(make_pair(kv.second, kv.first)); 
                }
            }
        }

        // 取出堆中的元素
        vector<int> result;
        while (!minHeap.empty())
        {
            result.push_back(minHeap.top().second); 
            minHeap.pop();
        }
        return result;
    }
};


int main() {
    vector<int> nums = {1,1,1,2,2,3};
    Solution s;
    vector<int> ans = s.topKFrequent(nums, 2);
    for (auto i:ans) {
        cout << i << endl;
    }
    return 0;
}
