/*
76. 最小覆盖子串
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
注意：

对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
如果 s 中存在这样的子串，我们保证它是唯一的答案。
 

示例 1：

输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
*/

/*
思路
滑动窗口
*/
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> cnt(52, 0);
        for (int i = 0; i < t.length(); ++i) {
            cnt[t[i]-'A']++;
        }

        // 滑动窗口
        int left = 0;
        int right = 0;
        int len = 0;
        int minLen = INT_MAX;
        int minLeft = 0;
        while (right < s.length()) {
            if (cnt[s[right]-'A'] > 0) {
                // 满足s[right] in t
                len++;
            }
            // 匹配过的字符-1（注意这里无论是否满足都应该--）
            cnt[s[right]-'A']--;
            right++;

            while (len == t.length()) {
                if (right - left < minLen) {
                    minLen = right - left;
                    minLeft = left;
                }
                // 是否能进一步缩小left
                if (cnt[s[left]-'A'] >= 0) {
                    len--;  // 不再满足s
                }
                cnt[s[left]-'A']++; // 恢复原来匹配过的字符数量
                left++;
            }
        }

        if (minLen == INT_MAX) {
            return "";
        }
        return s.substr(minLeft, minLen);
    }
};

int main() {
    Solution solution;
    string s = "cabwefgewcwaefgcf";
    string t = "cae";
    cout << solution.minWindow(s, t) << endl; // 输出 "BANC"
    return 0;
}