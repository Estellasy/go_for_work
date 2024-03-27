/*
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。
*/

/*
思路：
建立大小为k的大顶堆
*/

#include <iostream>
#include <vector>
using namespace std;

class Heap {
private:
    // Heap
    std::vector<int> heap;
    void init(int size) {
        
    }

    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size()-1);
    }

    void heapifyUp(int index) {
        // 计算插入数据父节点位置
        int parent = (index - 1) / 2;
        while (index > 0 && heap[parent] < heap[index]) {
            std::swap(heap[parent], heap[index]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }
public:
};