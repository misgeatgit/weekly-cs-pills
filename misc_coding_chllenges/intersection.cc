// Definition for singly-linked list.
#include <cassert>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        auto tmpA = headA;
        auto tmpB = headB;
        int lengthA = 0; int lengthB = 0;

        while(tmpA) {
            tmpA = tmpA->next;
            lengthA++;
        }

        while(tmpB) {
            tmpB = tmpB->next;
            lengthB++;
        }

        printf("Length A:%d Length B:%d \n", lengthA, lengthB);
        tmpA = headA; tmpB = headB;

        while( not(lengthA == lengthB)) {
            if(lengthA > lengthB) {
                tmpA = tmpA->next;
                --lengthA;
            }
            if( lengthB > lengthA) {
                tmpB = tmpB->next;
                --lengthB;
            }
        }

        while(tmpA and tmpB) {
            if(tmpA == tmpB) return tmpA;
            tmpA = tmpA->next;
            tmpB = tmpB->next;
        }

        return nullptr;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        string lh, rh;
        while(l1) {
            lh += to_string(l1->val);
            l1 = l1->next;
        }
        while(l2) {
            rh += to_string(l2->val);
            l2 = l2->next;
        }

        reverse(lh.begin(), lh.end());
        reverse(rh.begin(), rh.end());

        unsigned long long r = stoull(lh) + stoull(rh);
        string st = to_string(r);

        st.erase(st.begin() + st.find('.'), st.end());
        std::cout << st << std::endl;

        ListNode * l = nullptr; ListNode* head;
        for(int i = st.length() - 1; i >= 0; i--) {
            ListNode * n = new ListNode((int)(st[i] - 48)) ;
            n->next = nullptr;
            if( i == st.size() - 1) {
                l = head = n;
                continue;
            }
            l->next = n;
            l = n;
        }

        return head;
    }


};

int main(int argc, char** argv)
{
    ListNode headA(2);
    ListNode a1(4);
    ListNode a2(3);
    headA.next = &a1;
    a1.next = &a2;
    a2.next = nullptr;

    ListNode headB(5);
    ListNode b1(6);
    ListNode b2(4);
    headB.next = &b1;
    b1.next = &b2;
    b2.next = nullptr;

    Solution sln;

    ListNode * r = sln.addTwoNumbers(&headA, &headB);

    printf("%s\n", "result");
    while(r) {
        printf("%d", r->val);
        r = r->next;
    }

    // assert(r == headB);
}

// 10 2 3 4 5 6 7.....X
// 18 2 3 4 5 6 7....X
//
