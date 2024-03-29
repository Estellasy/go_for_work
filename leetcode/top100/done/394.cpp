/*
394. 字符串解码
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

 

示例 1：

输入：s = "3[a]2[bc]"
输出："aaabcbc"
示例 2：

输入：s = "3[a2[c]]"
输出："accaccacc"
示例 3：

输入：s = "2[abc]3[cd]ef"
输出："abcabccdcdcdef"
示例 4：

输入：s = "abc3[cd]xyz"
输出："abccdcdcdxyz"
*/
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string decodeString(string s) {
        string result = "";
        int curr = 0;
        while (curr < s.size()) {
            // 如果是字母，则直接添加到结果中
            if (isalpha(s[curr])) {
                result.push_back(s[curr]);
                curr++;
            }
            // 如果是数字，解析数字并进入循环处理方括号中的子字符串
            else if (isdigit(s[curr])) {
                int left = curr;
                while (isdigit(s[curr])) {
                    curr++;
                }
                int times = stoi(s.substr(left, curr - left));
                if (s[curr] == '[') {
                    int bracket_count = 1;
                    left = ++curr;
                    while (bracket_count != 0) {
                        if (s[curr] == '[') bracket_count++;
                        else if (s[curr] == ']') bracket_count--;
                        curr++;
                    }
                    string sub = decodeString(s.substr(left, curr - left - 1));
                    for (int i = 0; i < times; ++i) {
                        result.append(sub);
                    }
                }
            }
            // 其他情况直接跳过
            else {
                curr++;
            }
        }
        return result;
    }
};

int main() {
    Solution solution;
    string s="3[a2[c]]";
    cout << solution.decodeString(s) << endl;
    return 0;
}