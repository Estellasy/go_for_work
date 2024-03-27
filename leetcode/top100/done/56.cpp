/*
56. 合并区间

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

示例 1：

输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2：

输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
*/


/*
思路
判断区间[l1, r1] 和 [l2, r2] 是否能合并
[1,2] [5,6]
[5,6] [1,2]
不能合并的情况: r1<l2 || l1>r2
否则可合并为min(l1,l2),max(r1,r2)
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        sort(intervals.begin(), intervals.end());
        // 加入第一个
        result.push_back(intervals[0]);
        int size = intervals.size();
        for (int i=1; i<size; ++i) {
            bool flag=false;
            for (int j=0; j<result.size(); ++j) {
                // 可合并
                if (canMerge(intervals[i], result[j])) {
                    // 合并
                    result[j][0] = min(intervals[i][0], result[j][0]);
                    result[j][1] = max(intervals[i][1], result[j][1]);
                    flag=true;
                    break;
                }
            }
            // 不能合并
            if (!flag) {
                result.push_back(intervals[i]);
            }
        }

        return result;
    }

    bool canMerge(vector<int> a, vector<int> b) {
        if ((a[0]>b[1] && a[1]>b[0]) || (a[0]<b[1] && a[1]<b[0])) {
            return false;
        }
        return true;
    }
};

int main() {
    Solution s;
    vector<vector<int>> intervals{{1,4}, {0,0}};
    s.merge(intervals);
    return 0;
}
