/*
无重复字符的最长字串
给定一个字符串 s ，请你找出其中不含有重复字符的 最长
子串 的长度。

示例 1:

输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
*/

/*
思路
动态规划
dp[i][j] 表示从s[i]到s[j]的最大无重复字串
初始化dp[i][i]=1
判断s[j+1]是否在s[i]-s[j]中，如果没有，则+1
dp[i][j+1]=dp[i][j]+1 (if s[j] not in s[j-(dp[i][j])+1]-s[j])
*/
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        if (s.size() == 0) {
            return 0;
        }
        int result = 1;
        int size_s = s.size();
        vector<int> dp(size_s);
        // 初始化
        for (int i = 0; i < size_s; ++i)
        {
            dp[i] = 1;
        }
        for (int i = 0; i < size_s; ++i)
        {
            for (int j = i + 1; j < size_s; ++j)
            {
                bool flag = true;
                for (int t = j - dp[j - 1]; t < j; ++t)
                {
                    if (s[j] == s[t])
                    {
                        dp[j] = j - t;
                        flag = false;
                        continue;
                    }
                }

                if (flag == true)
                {
                    dp[j] = dp[j - 1] + 1;
                    if (result < dp[j])
                    {
                        result = dp[j];
                    }
                }
            }
        }
        return result;
    }
};

int main()
{
    string s = "pwwkew";
    Solution solution = Solution();
    cout << solution.lengthOfLongestSubstring(s) << endl;
    return 0;
}