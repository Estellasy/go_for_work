/*
108. 将有序数组转换为平衡二叉搜索树
思路
二叉搜索树的中序遍历是升序序列
给定二叉搜索树的中序遍历，不能唯一确定二叉搜索树
每次选择中间的元素为根节点，构建BST，其余的数字分别位于平衡二叉搜索树的左子树和右子树中
左子树和右子树也是平衡二叉搜索树，可以通过递归的方式创建。
*/

#include "treenode.h"
#include <vector>

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // 中序遍历，选择中间位置左边的数字为根节点
        return build(nums, 0, nums.size()-1);
    }

    TreeNode* build(vector<int>& nums, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        // 选择中间位置左边的数字为根节点
        int mid=(left+right)/2;
        TreeNode* root=new TreeNode(nums[mid]);
        root->left=build(nums, left, mid-1);
        root->right=build(nums, mid+1, right);
        return root;
    }
};