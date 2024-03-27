/*
给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

示例 1：

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
示例 2：

输入：nums = [0,1]
输出：[[0,1],[1,0]]
示例 3：

输入：nums = [1]
输出：[[1]]
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> ans;
        vector<bool> used(nums.size(), false);
        dfs(nums, used, ans, result);
        return result;
    }

    void dfs(vector<int>& nums, vector<bool>& used, vector<int>& ans, vector<vector<int>>& result) {
        // 生成解
        if (ans.size() == nums.size()) {
            result.push_back(ans);
            return;
        }

        // 回溯
        for (int i = 0; i < nums.size(); ++i) {
            if (!used[i]) {
                used[i] = true;
                ans.push_back(nums[i]);
                dfs(nums, used, ans, result);
                ans.pop_back();
                used[i] = false;
            }
        }
    }
};

int main() {
    Solution s;
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> permutations = s.permute(nums);
    for (const auto& permutation : permutations) {
        for (int num : permutation) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}
