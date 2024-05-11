#include <iostream>
#include <vector>
using namespace std;

int main() {

}

class Solution {
private:
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; //  四个方向
    void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
        for (int i=0; i<4; ++i) {
            int xx = x+dir[i][0];
            int yy = y+dir[i][1];
            if (xx<0 || xx>=grid.size() || yy<0 || yy>=grid.size()) {
                continue;   // 越界 直接跳过
            }
            if (!visited[xx][yy] && grid[xx][yy]==1) {
                visited[xx][yy] = true;
                dfs(grid, visited, xx, yy);
            }
        }
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false));

        int result = 0;
        for (int i=0; i<n; ++i) {
            for (int j=0; j<m; ++j) {
                if (!visited[i][j] && grid[i][j]=='1') {
                    visited[i][j] = true;
                    result++;
                    dfs(grid, visited, i, j);   // 找到所有与其连接的陆地
                }
            }
        }

        return result;
    }
}