/*
101. 对称二叉树
给你一个二叉树的根节点 root ， 检查它是否轴对称。
*/

/*
思路
1. 层序遍历，验证每一层是否对称
2. 递归
*/

#include "treenode.h"
#include <queue>

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root==nullptr) {
            return true;
        }
        // 调用递归函数
        return dfs(root->left, root->right);
    }


    bool dfs(TreeNode* left, TreeNode* right) {
        if (left==nullptr && right==nullptr) {
            return true;
        }
        // 左右两子树只有一个为nullptr
        if (left==nullptr || right==nullptr) {
            return false;
        }
        // 验证left.val==right.val? 比较根节点
        if (left->val!=right->val) {
            return false;
        }
        // 递归比较左节点的左孩子和右节点的右孩子
        // 和左节点的右孩子和右节点的左孩子
        return dfs(left->left, right->right) && dfs(left->right, right->left);
    }

    bool isSymmetric_queue(TreeNode* root) {
        if (root==nullptr || root->left==nullptr&&root->right==nullptr) {
            return true;
        }
        // 用队列保存节点
        queue<TreeNode*> q;
        // 将根节点的左右孩子放入队列中
        q.push(root->left);
        q.push(root->right);
        while(q.size()>0) {
            // 从队列中取出节点
            TreeNode* left=q.front();
            q.pop();
            TreeNode* right=q.front();
            q.pop();
            // 如果都为空则继续循环
            if (left==nullptr&&right==nullptr) {
                continue;
            }
            if (left==nullptr || right==nullptr) {
                return false;
            }
            if(left->val!=right->val) {
				return false;
			}
            // 将左节点左孩子，右节点右孩子放入队列
            q.push(left->left);
            q.push(right->right);
            // 将左节点右孩子，右节点左孩子放入队列
            q.push(left->right);
            q.push(right->left);
        }
        return true;
    }
};

