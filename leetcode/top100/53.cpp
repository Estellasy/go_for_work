#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre=nums[0];
        int ans=pre;
        for (int i=1; i<nums.size(); ++i) {
            int cur=max(nums[i], pre+nums[i]);
            if (cur>ans) {
                ans=cur;
            }
            pre=ans;
        }
        return ans;   
    }
};