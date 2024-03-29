/*
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

实现 MinStack 类:

MinStack() 初始化堆栈对象。
void push(int val) 将元素val推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。
*/
#include <iostream>
using namespace std;

class MinStack {
public:
    vector<int> stack;
    int size;
    vector<int> minIndex;
    MinStack() {
        size = 0;
    }
    
    void push(int val) {
        stack.push_back(val);
        // 处理minIndex
        if (minIndex.size() == 0) {
            minIndex.push_back(0);
        } else if (val < stack[minIndex[size-1]]) {
            minIndex.push_back(size);
        } else {
            minIndex.push_back(minIndex[size-1]);
        }
        size++;
    }
    
    void pop() {
        stack.pop_back();
        minIndex.pop_back();
        size--;
    }
    
    int top() {
        return stack[size-1];
    }
    
    int getMin() {
        return stack[minIndex[size-1]];
    }
};

int main() {
    MinStack stack;
    stack.push(-2);
    stack.push(0);
    stack.push(-3);
    cout << stack.getMin() << endl;
    stack.pop();
    cout << stack.top() << endl;
    cout << stack.getMin() << endl;
    return 0;
}

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */