#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    void left_print(map<int, std::vector<std::pair<vector<int>, TreeNode*>>>& print, int l, int depth, TreeNode* begin)
    {
        if(nullptr == begin->left) return;
        std::stack<TreeNode*> parent;
        TreeNode * left = begin->left;
        ++l;

        while(left) {
            vector<int> order_info = {depth, 0};
            if(print.find(l) != print.end()) {
                print[l].push_back(std::make_pair(order_info, left));
            } else {
                print[l] = {std::make_pair(order_info, left)};
            }

            parent.push(left);
            left = left->left;
            l++;
            ++depth;
        }

        while(not parent.empty()) {
            TreeNode* p = parent.top();
            parent.pop();
            right_print(print, --l, depth, p); // parent is at l-1 where refers to the vertical position
            depth--;
        }

    }

    void right_print(map<int, std::vector<std::pair<vector<int>, TreeNode*>>>& print, int l, int depth, TreeNode* begin)
    {
        if(nullptr == begin->right) return;
        std::stack<TreeNode*> parent;
        TreeNode * right = begin->right;
        l--;

        while(right) {
            vector<int> order_info = {depth, 1};
            if(print.find(l) != print.end()) {
                print[l].push_back(std::make_pair(order_info, right));
            } else {
                print[l] = {std::make_pair(order_info, right)};
            }

            parent.push(right);
            right = right->right;
            l--;
            ++depth;
        }


        while(not parent.empty()) {
            TreeNode* p = parent.top();
            parent.pop();

            left_print(print, ++l, depth, p); // Parent is at l+1 where refers to the vertical position
            depth--;
        }

    }


    vector<vector<int>> verticalOrder(TreeNode* root)
    {
        if(nullptr == root) return {};
        map<int, std::vector<std::pair< vector<int>, TreeNode*>>> print;
        vector<int> order_info = {0, -1};
        print[0] = {std::make_pair(order_info, root)};

        left_print(print, 0 , 0 , root);
        right_print(print, 0 ,  0 , root);

        vector<vector<int>> print_val;

        for(auto it = print.rbegin(); it != print.rend(); ++it) {
            std::vector<int> val;
            std::vector< std::pair<vector<int>, TreeNode*>> nodes = it->second;
            std::sort(nodes.begin(), nodes.end(), [](std::pair<vector<int>, TreeNode*> p1, std::pair<vector<int>, TreeNode*> p2) {
                if(p1.first[0] == p2.first[0]) {
                    return p1.first[1] < p2.first[1];
                } else {
                    return p1.first[0] < p2.first[0];
                }
            });

            for(auto node : nodes) {
                val.push_back((node.second)->val);
                std::cout << (node.second)->val << "@depth " << node.first[0] << "\n";
            }

            print_val.push_back(val);
        }

        return print_val;
    }

};

