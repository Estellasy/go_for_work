/*
199. 二叉树的右视图
给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
*/

#include "treenode.h"
#include <queue>
#include <vector>

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<vector<int>> levelRes = levelOrder(root);
        vector<int> res;
        for (auto i:levelRes) {
            res.push_back(i.back());
        }
        return res;
    }

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