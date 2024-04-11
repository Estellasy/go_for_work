/*
114. 二叉树展开为链表
给你二叉树的根结点 root ，请你将它展开为一个单链表：

展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
展开后的单链表应该与二叉树 先序遍历 顺序相同。
*/

#include "treenode.h"
#include <vector>
#include <stack>

class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) {
            return ;
        }
        // 创建虚拟节点作为链表头部
        TreeNode *dummy = new TreeNode(0);
        TreeNode *pre = dummy;
        // 二叉树先序遍历 中左右
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            // 出栈
            TreeNode* curr = st.top();
            st.pop();
            // 右节点入栈
            if (curr->right != nullptr) {
                st.push(curr->right);
            }
            // 左节点入栈
            if (curr->left != nullptr) {
                st.push(curr->left);
            }
            pre->right = curr;
            pre->left = nullptr;
            pre = pre->right; // 跟踪链表尾部
        }
        root = dummy->right;
        delete dummy;
    }
};