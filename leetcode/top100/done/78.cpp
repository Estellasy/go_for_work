/*
78. 子集
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的
子集
（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

 

示例 1：

输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
示例 2：

输入：nums = [0]
输出：[[],[0]]
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        vector<bool> used(nums.size(), false);
        dfs(0, nums, result, path, used);
        return result;
    }

    void dfs(int idx, vector<int>& nums, vector<vector<int>>& result, vector<int>& path, vector<bool>& used) {
        // 不需要终止条件
        result.push_back(path);
        
        // 回溯
        for (int i = idx; i < nums.size(); ++i) {
            if (!used[i]) {
                used[i] = true;
                path.push_back(nums[i]);
                dfs(i+1, nums, result, path, used);
                path.pop_back();
                used[i] = false;
            }
        }
    }
};


int main() {
    Solution s;
    vector<int> nums{1,2,3};
    cout << s.subsets(nums).size() << endl;
}