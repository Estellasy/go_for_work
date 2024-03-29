/*
543. 二叉树的直径
给你一棵二叉树的根节点，返回该树的 直径 。

二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点 root 。

两节点之间路径的 长度 由它们之间边数表示。
*/

/*
即为求根节点左右节点的高度和
*/

#include "treenode.h"
#include <vector>
#include <stack>
#include <queue>

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (root==nullptr) {
            return 0;
        }

        int maxDiameter=0;  // 跟踪最长路径长度
        getDepth(root, maxDiameter);
        return maxDiameter;
    }

    int getDepth(TreeNode* root, int& depth) {
        if (root == nullptr) {
            return 0;
        }

        int leftDepth=getDepth(root->left, depth);
        int rightDepth=getDepth(root->right, depth);

        depth = max(depth, leftDepth + rightDepth);
        return 1+max(leftDepth, rightDepth);
    }
};