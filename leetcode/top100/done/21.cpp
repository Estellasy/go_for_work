/*
21. 合并有序链表
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *head, *curr;
        ListNode *p1, *p2;
        head = NULL;
        curr = NULL;
        p1 = list1;
        p2 = list2;

        // 特判
        if (p1 == NULL) {
            return p2;
        }
        if (p2 == NULL) {
            return p1;
        }

        // first
        if (p1->val < p2->val) {
            head = p1;
            curr = p1;
            p1 = p1->next;
        } else {
            head = p2;
            curr = p2;
            p2 = p2->next;
        }

        while (p1 != NULL && p2 != NULL) {
            if (p1->val < p2->val) {
                curr->next = p1;
                p1 = p1->next;
            } else {
                curr->next = p2;
                p2 = p2->next;
            }
            curr = curr->next; // 更新curr位置
        }

        if (p1 != NULL) {
            curr->next = p1;
        }
        if (p2 != NULL) {
            curr->next = p2;
        }
        return head;
    }
};