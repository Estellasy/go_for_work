/*
79. 单词搜索
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<int>> walk = {{1,0}, {-1,0}, {0,1}, {0,-1}};  // 四个方向
    bool exist(vector<vector<char>>& board, string word) {
        int sizex = board.size();
        int sizey = board[0].size();
        vector<vector<bool>> used(sizex, vector<bool>(sizey, false));
        
        for (int i = 0; i < sizex; ++i) {
            for (int j = 0; j < sizey; ++j) {
                if (dfs(board, used, i, j, sizex, sizey, 0, word)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isValid(const vector<vector<bool>>& used, int sizex, int sizey, int xx, int yy) {
        return xx >= 0 && xx < sizex && yy >= 0 && yy < sizey && !used[xx][yy];
    }

    bool dfs(const vector<vector<char>>& board, vector<vector<bool>>& used, int x, int y, int sizex, int sizey, int startIdx, const string& word) {
        if (startIdx == word.length()) {
            return true;
        }
        
        if (!isValid(used, sizex, sizey, x, y) || board[x][y] != word[startIdx]) {
            return false;
        }
        
        used[x][y] = true;
        for (const auto& dir : walk) {
            int xx = x + dir[0];
            int yy = y + dir[1];
            
            if (dfs(board, used, xx, yy, sizex, sizey, startIdx + 1, word)) {
                return true;
            }
        }
        used[x][y] = false;
        
        return false;
    }
};

int main() {
    vector<vector<char>> board = {{'A','B','C','E'},
                                  {'S','F','C','S'},
                                  {'A','D','E','E'}};
    string word="ABCCED";
    Solution solution;
    solution.exist(board, word);
}