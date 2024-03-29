/*
104. 二叉树的最大深度

1. 层序遍历
2. dfs深度优先搜索
*/

#include "treenode.h"
#include <vector>
#include <stack>
#include <queue>

class Solution {
public:
    int maxDepth_dfs(TreeNode* root) {
        return getDepth(root, 0);
    }

    int getDepth(TreeNode* root, int depth) {
        if (root==nullptr) {
            return depth;
        }
        return max(getDepth(root->left, depth+1), getDepth(root->right, depth+1));
    }

    int maxDepth(TreeNode* root) {
        // 层序遍历 队列
        queue<TreeNode*> q;
        // 记录层数
        int ans = 0;
        if (root==nullptr) {
            return ans;
        }
        q.push(root);
        while (!q.empty()) {
            int size=q.size();
            for(int i=0; i<size; ++i) {
                TreeNode* t = q.front();
                q.pop();
                if (t->left!=nullptr) {
                    q.push(t->left);
                }
                if (t->right!=nullptr) {
                    q.push(t->right);
                }
            }
            ans++;
        }
        return ans;
    }
};
