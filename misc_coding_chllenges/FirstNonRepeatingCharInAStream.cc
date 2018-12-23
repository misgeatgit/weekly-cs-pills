
#include <map>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

struct Node {
    char c;
    Node * next;
    Node * prev;
};

struct DLLQueue {
    Node * head = nullptr;
    Node * tail = nullptr;

    void append(Node * node)
    {
        if(not head) {
            head = node;
            head->next = nullptr;
            head->prev = nullptr;
            tail = head;
        } else {
            tail->next = node;
            node->prev = tail;
            node->next = nullptr;
            tail = node;
        }
        //std::cout << "Append--- head is " << head->c << " tail is " << tail->c << "\n";
    }

    void remove(Node * node)
    {
        Node * after = node->next;
        Node * before = node->prev;

        if( node != head and node != tail) {
            //std::cout << "Removing from middle\n";
            before->next = after;
            //std::cout << "Before is " << (before)->c << "\n";
            after->prev = before;
            //std::cout << "After is " << (after)->c << "\n";
        } else {

            if(node == head and after) {
                //  std::cout << "Removing from head\n";
                head = after;
                after->prev = nullptr;
            }
            if ( node == tail and before) {
                //  std::cout << "Removing from tail\n";
                tail = before;
                before->next = nullptr;
            }
        }

        delete(node);
    }
};




int main(int argc, char** argv)
{
    string test = "The quick brown fox jumped onto the lazy dog.";

    if(false) {
        bool is_seen[256] = {false}; // one way since char maps to int
        Node * DLL[256] = {nullptr};

        //std::map<char,Node*> nodes;
        DLLQueue dlq;
        int i = 0;
        for (char& s : test ) {
            printf("%s\n", test.substr(0, i).c_str());
            if(not DLL[s] and (not is_seen[s]))  {
                Node * node = new Node {s, nullptr, nullptr};
                dlq.append(node);
                DLL[s] = node;
                is_seen[s] = true;
            }  else {
                if (DLL[s]) {
                    //std::cout << "Removing " << DLL[s]->c << "\n";
                    dlq.remove(DLL[s]);
                    DLL[s] = nullptr;
                }
            }

            if(dlq.head)
                std::cout << "First non repeating char is " << (dlq.head)->c << "\n";
            else
                std::cout << "There is non repeating char so far.\n";
            i++;
        }
    }

    //STL queue based
    if(true) {
        queue<char> observations;
        size_t freq [256] = {0};
        int j = 0;
        for (char& s : test ) {
            printf("%s\n", test.substr(0, j).c_str());
            observations.push(s);
            freq[s]++;

            while(!observations.empty()) {
                if(freq[observations.front()] > 1)
                    observations.pop();
                else break;

            }

            if(not observations.empty())
                std::cout << "First non repeating char is " << observations.front() << "\n";
            else
                std::cout << "There is non repeating char so far.\n";

            j++;
        }
    }


}
