/*
226. 翻转二叉树
*/

#include "treenode.h"
#include <vector>
#include <stack>
#include <queue>

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        invert(root);
        return root;
    }

    void invert(TreeNode* root) {
        if (root==nullptr) {
            return;
        }
        // invert
        TreeNode* left=root->left;
        TreeNode* right=root->right;
        root->left = right;
        root->right = left;
        if (root->left!=nullptr) {
            invert(root->left);
        }
        if (root->right!=nullptr) {
            invert(root->right);
        }
    }
};