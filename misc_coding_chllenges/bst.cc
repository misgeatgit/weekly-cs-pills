#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename DataType>
class Tree
{
private:
    struct Node;
    using NodePtr = shared_ptr<Node>;
    //using DataPtr = shared_ptr<DataType>;
    struct Node {
        NodePtr left = nullptr;
        NodePtr right = nullptr;
        DataType data;
    };

    void _inorder_traversal(vector<DataType>& vec, NodePtr nptr = nullptr) const
    {
        if( nullptr == nptr) {
            return;
        }

        _inorder_traversal(vec, nptr->left);
        vec.push_back(nptr->data);
        _inorder_traversal(vec, nptr->right);

    }

    void _postorder_print(vector<DataType>& vec, const NodePtr left) const
    {
        stack<NodePtr> prev;
        NodePtr lft = left;
        while(lft) {
            prev.push(lft);
            lft = lft->left;
        }

        while (not prev.empty()) {
            NodePtr& p = prev.top();
            prev.pop();
            _postorder_print(vec, p->right);
            vec.push_back(p->data);
        }
    }

    NodePtr _search(const NodePtr root, const DataType& d) const
    {
        if( nullptr == root)
            return nullptr;
        else if ( root->data == d)
            return root;
        else if(d < root->datat)
            _search(root->left, d);
        else
            _search(root->right, d);
    }

public:
    NodePtr root = nullptr;

    void insert(DataType data)
    {
        Node n;
        n.data = data;
        if (not root) {
            root = make_shared<Node>(n);
            return;
        }

        NodePtr* tmproot = &root;
        while (*tmproot) {
            // to the left
            if ( data < ((*tmproot)->data) )
                tmproot = &((*tmproot)->left);
            else  // to the right
                tmproot = &((*tmproot)->right);
        }

        *tmproot = make_shared<Node>(n);
    }


    NodePtr common_ancestor(const DataType data1, const DataType data2)
    {
        NodePtr tmproot = root;
        while (tmproot) {
            if ( data1 > tmproot->data and data2 > tmproot->data)
                tmproot = tmproot->right;

            else if ( data1 < tmproot->data and data2 < tmproot->data)
                tmproot = tmproot->left;

            else
                return tmproot;
        }

        return nullptr;
    }

    NodePtr search(const DataType& d) const
    {
        return  _search(root, d);
    }

    int minimum_distance(const DataType data1, const DataType data2)
    {
        return -1;
    }

    void inorder_traversal(vector<DataType>& vec) const
    {
        if(not root) return;

        _inorder_traversal(vec, root);

    }

    void postorder_traversal(vector<DataType>& vec) const
    {
        if(not root) return;

        _postorder_print(vec, root->left);
        _postorder_print(vec, root->right);
        vec.push_back(root->data);
    }

    //TODO
    bool checkBST(NodePtr root)
    {
        return false;
    }


    NodePtr lcm(DataType v1, DataType v2)
    {
        vector<NodePtr> traversed1;
        vector<NodePtr> traversed2;
        NodePtr n = root;

        while (n) {
            traversed1.push_back(n);
            if (n->data == v1)
                break;

            if (v1 < n->data)
                n = n->left;
            else
                n = n->right;
        }

        n = root;
        while (n) {
            traversed2.push_back(n);
            if (n->data == v2)
                break;

            if (v2 < n->data)
                n = n->left;
            else
                n = n->right;
        }

        if (traversed1.size() > traversed2.size()) {
            for ( int i = traversed1.size() - 1; i >= 0; i--) {
                for ( int j = traversed2.size() - 1; j >= 0; j--)
                    if ( traversed1[i] == traversed2[j] ) return traversed1[i];
            }
        } else {
            for ( int i = traversed2.size() - 1; i >= 0; i--) {
                for ( int j = traversed1.size() - 1; j >= 0; j--)
                    if ( traversed2[i] == traversed1[j] ) return traversed2[i];
            }
        }

        return nullptr;
    }
};

template <typename DataType>
ostream& operator<<(ostream& os, const Tree<DataType>& t)
{
    std::vector<DataType> vec;
    t.inorder_traversal(vec);
    ostream_iterator<DataType> it(os, " ");
    std::copy(vec.begin(), vec.end(), it);
    return os;
}

// Leetcode
//-------------------Xhrs----------------------
// balancing
// Postfix and Infix traversal
// Calculator
// printing
// Searching
// AVL and Rb tree
// linked list(doubly linked list)
// Graph
//---------------------Xhrs------------------
// algorithm analysis
// hashing
// quick sort and merge srot
// matrix
//-------------------------Xhrs----------------
//   dynamic programming
//----------8hrs------------------------------
//   sorting
//   array problem solving
//   OOP, Concurrency in C++, File, string processing, STL algorithms
//   Distributed computing
//   Scalability (the pdf books recommended by the recruiter)
//   System design (the pdf sent by the recruiter)
//   Operating systems (Threads, process, memory...etc)

int main(int argc, char** argv)
{
    Tree<int> tree;
    tree.insert(23);
    tree.insert(23);
    tree.insert(28);
    tree.insert(21);
    tree.insert(45);
    tree.insert(10);
    tree.insert(30);
    tree.insert(25);

    std::cout << "Tree is:\n" << tree << "\n";

    cout << "LCM(25,21): " << tree.lcm(25, 21)->data << "\n";

    cout << "ISBst " << tree.checkBST(tree.root) << "\n";
    cout << "common ancestor of 30 and 25   " << (tree.common_ancestor(30,
            25))->data << endl;

    vector<int> vec;
    tree.inorder_traversal(vec);
    std::cout << "Inorder traversal \n";
    for(auto e : vec)
        std::cout << e << ", ";
    std::cout << "\n";

    vec = {};
    tree.postorder_traversal(vec);
    std::cout << "Postorder traversal \n";
    for(auto e : vec)
        std::cout << e << ", ";
    std::cout << "\n";
}
