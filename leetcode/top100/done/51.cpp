/*
51. N皇后
按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。

n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。

每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<int> path; // queen的下标
        vector<vector<string>> result; // result
        dfs(0, n, path, result);
        return result;
    }

    void dfs(int row, int n, vector<int> &path, vector<vector<string>> &result) {
        // 返回条件
        if (row == n) {
            // 生成解
            vector<string> ans;
            for (int i = 0; i < n; ++i) {
                string str(n, '.');
                str[path[i]] = '*';
                ans.push_back(str);
            }
            result.push_back(ans);
        }

        // 回溯
        for (int col = 0; col < n; ++col) {
            if (isValid(row, col, path)) {
                path.push_back(col);
                dfs(row+1, n, path, result);
                path.pop_back();
            }
        }
    }

    bool isValid(int row, int col, vector<int> &path) {
        for (int i = 0; i < row; ++i) {
            // 检查列和对角线
            if (path[i] == col || abs(i-row) == abs(path[i]-col)) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution solution;
    int n = 4;
    vector<vector<string>> result = solution.solveNQueens(n);
    for (auto &solution : result) {
        for (auto &row : solution) {
            cout << row << endl;
        }
        cout << endl;
    }
    return 0;
}