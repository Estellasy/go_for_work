#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void backtracking() {
    if (终止条件) {
        存放结果;
        return;
    }
    for (选择：本层集合) {
        处理节点;
        backtracking(路径，选择列表); // 递归
        回溯，撤销处理结果
    }
}

int main() {
    backtracking(); // 调用
    return 0;
}

class Solution {
private:
    vector<string> result;  // 记录结果
    void backtracking(string& s, int startIndex, int pointNum) {
        if (pointNum == 3) {
            // 判断第四段子字符串是否合法
            if (isValid(s, startIndex, s.size() - 1)) {
                result.push_back(s.substr(startIndex, s.size() - startIndex));
            }
            return;
        }
        for (int i=startIndex; i<s.size(); i++) {
            if (isValid(s, startIndex, i)) {
                s.insert(s.begin() + i + 1, '.');
                pointNum++;
                backtracking(s, i + 2, pointNum);
                pointNum--;
                s.erase(s.begin() + i + 1);
            } else {
                break;
            }
        }
    }
    bool isValid(const string& s, int start, int end) {
        if (start > end) {
            return false;
        }
        if (s[start] == '0' && start!=end) {
            return false;
        }

    }
}