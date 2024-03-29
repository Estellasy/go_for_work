/*
给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。
*/
#include "treenode.h"
#include <vector>
#include <queue>

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> result;
        
        if (root==nullptr) {
            return result;
        }
        q.push(root);
        while (!q.empty()) {
            // 记录当前层节点数量
            int size=q.size();
            vector<int> path;
            for (int i=0; i<size; ++i) {
                // 从队列中取出节点
                TreeNode *t = q.front();
                q.pop();
                path.push_back(t->val);
                if (t->left != nullptr) {
                    q.push(t->left);
                }
                if (t->right != nullptr) {
                    q.push(t->right);
                }
            }
            result.push_back(path);
        }
        return result;
    }
};