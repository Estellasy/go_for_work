/*
295. 数据流的中位数
中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。

例如 arr = [2,3,4] 的中位数是 3 。
例如 arr = [2,3] 的中位数是 (2 + 3) / 2 = 2.5 。
实现 MedianFinder 类:

MedianFinder() 初始化 MedianFinder 对象。

void addNum(int num) 将数据流中的整数 num 添加到数据结构中。

double findMedian() 返回到目前为止所有元素的中位数。与实际答案相差 10-5 以内的答案将被接受。

示例 1：

输入
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
输出
[null, null, null, 1.5, null, 2.0]

解释
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // 返回 1.5 ((1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
*/

/*
思路
维护两个优先队列（底层用堆实现）
一个是最大堆，一个是最小堆
每次调整堆

大顶堆存储较小一半的数据
小顶堆存储较大一半的数据
*/
#include <queue>
#include <iostream>
using namespace std;

class MedianFinder {
public:
    priority_queue<int, vector<int>, less<int>> maxHeap; // 大顶堆 存储较小一半的数据
    priority_queue<int, vector<int>, greater<int>> minHeap; // 小顶堆 存储较大一半的数据
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        // 加入堆
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        // 调整堆的大小 确保平衡
        while (maxHeap.size() > minHeap.size()+1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        while (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (minHeap.size() == maxHeap.size()) {
            return double(maxHeap.top() + minHeap.top()) / 2;
        } else {
            return maxHeap.top();
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */