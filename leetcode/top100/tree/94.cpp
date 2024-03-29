/*
94. 二叉树的中序遍历
中序遍历：左中右
*/

#include "treenode.h"
#include <vector>
#include <stack>

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        dfs(root, ans);
        return ans;
    }

    void dfs(TreeNode* root, vector<int>& ans) {
        if (root==nullptr) {
            return;
        }
        dfs(root->left, ans);
        ans.push_back(root->val);
        dfs(root->right, ans);
    }

    vector<int> inorderTraversal_stack(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> st;
        TreeNode* curr=root;
        
        while (curr!=nullptr || !st.empty()) {
            while (curr!=nullptr) {
                // 根节点和左子树入栈，直至为空
                st.push(root);
                curr=curr->left;
            }
            // 出栈
            curr = st.top();
            st.pop();
            ans.push_back(curr->val);
            // 移动至右子树
            curr=curr->right;
        }
        return ans;
    }
};