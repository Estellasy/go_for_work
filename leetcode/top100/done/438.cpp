/*
给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。

示例 1:

输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
 示例 2:

输入: s = "abab", p = "ab"
输出: [0,1,2]
解释:
起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。
*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.length() < p.length()) {
            return vector<int>(0);
        }
        
        vector<int> cnts(26, 0);
        vector<int> ans;
        // 初始化计数器
        for (char c:p) {
            cnts[c-'a']++;
        }
        int left = 0;
        int count = p.length(); // 记录当前窗口中匹配字符的数量
        for (int right=0; right<s.size(); ++right) {
            // 右边界字符进入窗口
            if (--cnts[s[right]-'a']>=0) {
                count--;
            }
            if (right-left+1 == p.length()) {
                if (count == 0) {
                    ans.push_back(left);
                }
                // 左边界字符出窗口
                if (++cnts[s[left]-'a'] > 0) {
                    count++;
                }
                left++;
            } else if (right-left+1 > p.length()) {
                // 左边界字符出窗口
                if (++cnts[s[left] - 'a'] > 0) {
                    count++;
                }
                left++; // 更新左边界
            }
        }
        return ans;
    }
};


int main() {
    string s = "abab";
    string p = "ab";
    Solution solution;
    cout << solution.findAnagrams(s, p).size() << endl;
}