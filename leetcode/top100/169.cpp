#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[int(nums.size()/2)];
    }
};