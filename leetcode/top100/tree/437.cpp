/*
437. 路径总和 III
给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
*/

/*
思路
dfs 从root节点开始向下搜索 如果当前sum==targetSum 则ans++
*/
#include "treenode.h"

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
    }
};