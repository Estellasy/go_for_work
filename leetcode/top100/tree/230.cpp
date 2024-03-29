/*
230. 二叉搜索树中第k小的元素
给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 个最小元素（从 1 开始计数）。
*/
#include "treenode.h"

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        vector<int> order;
        inorder(root, order, k);
        return order[k-1];
    }

    void inorder(TreeNode* root, vector<int>& order, int k) {
        if (order.size()==k) {
            return ;
        }
        if (root==nullptr) {
            return ;
        }
        inorder(root->left, order, k);
        order.push_back(root->val);
        inorder(root->right, order, k);
    }
};