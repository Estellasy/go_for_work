/*
请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：
LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
*/
#include <iostream>
#include <unordered_map>

class LRUCache
{
public:
    struct Node
    {
        int key, value;
        Node *left, *right;
        Node(int _key, int _value) : key(_key), value(_value), left(nullptr), right(nullptr){};
    } *L, *R;
    int n;
    std::unordered_map<int, Node *> map;

    LRUCache(int capacity)
    {
        n = capacity;
        L = new Node(-1, -1);
        R = new Node(-1, -1);
        L->right = R;
        R->left = L;
    }

    int get(int key)
    {
        if (isExist(key))
        {
            // 移动node至最前端
            Node *p = map[key];
            p->right->left = p->left;
            p->left->right = p->right;
            // 修改p节点指针
            p->right = L->right;
            p->left = L;
            // 修改目前L->right指针
            L->right->left = p;
            // 修改L指针
            L->right = p;

            return map[key]->value;
        }
        else
        {
            return -1;
        }
    }

    void put(int key, int value)
    {
        // 如果当前存在key
        if (isExist(key))
        {
            // 更新value
            map[key]->value = value;
            // 移动node至最前端
            Node *p = map[key];
            p->right->left = p->left;
            p->left->right = p->right;
            // 修改p节点指针
            p->right = L->right;
            p->left = L;
            // 修改目前L->right指针
            L->right->left = p;
            // 修改L指针
            L->right = p;
        }
        // 如果不存在当前key
        else
        {
            if (map.size() == n)
            {
                // 删除最后一个节点
                Node *p = R->left;
                p->left->right = R;
                R->left = p->left;
                // 从map中删除
                map.erase(p->key);
                // std::cout << "remove tail " << p->value << std::endl;
                delete p;
            }
            Node *p = new Node(key, value);
            p->left = L;
            p->right = L->right;
            L->right->left = p;
            L->right = p;
            map[key] = p;
        }
        // std::cout << "put " << key << " to left, first is " << L->right->key << std::endl;
    }

    bool isExist(int key)
    {
        if (map.find(key) != map.end())
        {
            return true;
        }
        return false;
    }
};

void testLRUCache()
{
    // 创建LRUCache对象，容量为2
    LRUCache cache(2);

    // ["LRUCache","put","put","get","put","get","put","get","get","get"]
    // [[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]

    // ["LRUCache","put","put","get","put","get","put","get","get","get"]
    // [[2],[1,0],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]

    cache.put(1, 0);
    cache.put(2, 2);
    std::cout << cache.get(1) << std::endl;
    cache.put(3, 3);
    std::cout << cache.get(2) << std::endl;
    cache.put(4, 4);
    std::cout << cache.get(1) << std::endl;
    std::cout << cache.get(3) << std::endl;
    std::cout << cache.get(4) << std::endl;
}

int main()
{
    testLRUCache();
    return 0;
}
