/*
98. 验证二叉搜索树
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

有效 二叉搜索树定义如下：

节点的左子树只包含 小于 当前节点的数。
节点的右子树只包含 大于 当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include "treenode.h"

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        // 验证中序遍历是否为递增数组
        vector<int> order;
        inorder(root, order);
        if (order.size()==0 || order.size()==1) {
            return true;
        }
        for (int i=1; i<order.size(); ++i) {
            if (order[i]<=order[i-1]) {
                return false;
            }
        }
        return true;
    }

    void inorder(TreeNode* root, vector<int>& order) {
        if (root==nullptr) {
            return ;
        }
        inorder(root->left, order);
        order.push_back(root->val);
        inorder(root->right, order);
    }
};