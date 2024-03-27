/*
实现 LFUCache 类：

LFUCache(int capacity) - 用数据结构的容量 capacity 初始化对象
int get(int key) - 如果键 key 存在于缓存中，则获取键的值，否则返回 -1 。
void put(int key, int value) - 如果键 key 已存在，则变更其值；如果键不存在，请插入键值对。当缓存达到其容量 capacity 时，则应该在插入新项之前，移除最不经常使用的项。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除 最久未使用 的键。
为了确定最不常使用的键，可以为缓存中的每个键维护一个 使用计数器 。使用计数最小的键是最久未使用的键。

当一个键首次插入到缓存中时，它的使用计数器被设置为 1 (由于 put 操作)。对缓存中的键执行 get 或 put 操作，使用计数器的值将会递增。

函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
*/

/*
使用堆来实现？建最小堆？排序？
最久未使用的key
1. key
2. 最后一次使用时间
3. 使用计数器
使用双端队列

如何按照使用次数最少排序？如何记录？
*/
#include <iostream>
#include <deque>
#include <unordered_map>

class LFUCache {
public:
    struct Node
    {
        int key, value, count;
        Node *left, *right;
        Node(int _key, int _value) : key(_key), value(_value), count(1), left(nullptr), right(nullptr){};
    } *L, *R;

    int n;
    std::unordered_map<int, Node *> mp;
    LFUCache(int capacity) {
        n = capacity;
        L = new Node(-1, -1);
        R = new Node(-1, -1);
        L->right = R;
        R->left = L;
    }
    
    int get(int key) {
        // 存在key
        if (mp.find(key) != mp.end()) {
            // 更新count
            mp[key]->count++;
            // 插至最前面
            moveToHead(mp[key]);
            return mp[key]->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            // 如果存在key
            // 更新value
            mp[key]->value = value;
            // 更新count
            mp[key]->count++;
            // 插至最前面
            moveToHead(mp[key]);
        } else {
            // 不存在key
            // 判断当前是否已满
            if (mp.size() == n) {
                // 最久未使用移除
                remove();
            }
            // 插入
            Node *p = new Node(key, value);
            L->right->left = p;
            p->right = L->right;
            p->left = L;
            L->right = p;
            mp[key] = p;
        }
    }

    void moveToHead(Node *p) {
        p->left->right = p->right;
        p->right->left = p->left;

        L->right->left = p;
        p->right = L->right;
        p->left = L;
        L->right = p;
    }

    void remove() {
        // 获得最久未使用
        Node *p = R->left;
        mp.erase(p->value);
        R->left = p->left;
        p->left->right = R;
        delete p;
    }
};


int main() {
    // ["LFUCache","put","put","get","put","get","get","put","get","get","get"]
    // [[2],[1,1],[2,2],[1],[3,3],[2],[3],[4,4],[1],[3],[4]]

    // ["LFUCache","put","put","get","get","get","put","put","get","get","get","get"]
    // [[3],[2,2],[1,1],[2],[1],[2],[3,3],[4,4],[3],[2],[1],[4]]

    LFUCache cache(3);

    cache.put(2, 2); // [2]
    cache.put(1, 1); // [1, 2]
    std::cout << cache.get(2) << std::endl; // [2, 1]
    std::cout << cache.get(1) << std::endl; // [1, 2]
    std::cout << cache.get(2) << std::endl; // [2, 1]
    cache.put(3, 3); // [3, 2, 1]
    cache.put(4, 4); // [4, 3, 2]
    std::cout << cache.get(3) << std::endl; // [3, 4, 2]
    std::cout << cache.get(2) << std::endl; // [2, 3, 4]
    std::cout << cache.get(1) << std::endl; // 
    std::cout << cache.get(4) << std::endl;
}

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */