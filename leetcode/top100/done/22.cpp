/*
22. 括号生成
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例 1：

输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
示例 2：

输入：n = 1
输出：["()"]
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string path="";

        dfs(0, 0, n, result, path);
        return result;
    }

    void dfs(int left, int right, int n, vector<string>& result, string& path) {
        // 终止条件
        if (left == n && right == n) {
            result.push_back(path);
            return;
        }

        // 回溯构造path
        if (left < n) {
            path.push_back('(');
            dfs(left + 1, right, n, result, path);
            path.pop_back();
        }
        if (right < left) {
            path.push_back(')');
            dfs(left, right + 1, n, result, path);
            path.pop_back();
        }
    }
};

int main() {
    Solution s;
    vector<string> result = s.generateParenthesis(3);
    for (auto str:result) {
        cout << str << endl;
    }
    return 0; 
}