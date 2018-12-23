#include <map>
#include <set>
#include <iostream>
#include <vector>


using namespace std;


struct Page {
    size_t id;
    size_t hit;

};

bool operator <(const Page& p1, const Page& p2)
{
    return (p1.hit < p2.hit and p1.id != p2.id); // second one is to insure they are not duplicates.

}

struct PagePtrComp {
    bool operator()(const Page* p1, const Page* p2) const
    {
        return p1->hit < p2->hit;
    }
};

map<size_t, Page*> table;
set<Page*, PagePtrComp>  lru;

int main()
{
    vector<Page> pages = { {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}};

    for( int i = 0 ; i < 100; i++) {
        int access = rand() % 4;
        pages[access].hit++;

        if(lru.size() >= 5) {
            auto it = lru.begin();
            lru.erase(it);
            std::cout << "ERASED " << pages[access].id << "\n";
        }

        lru.insert(&pages[access]); // Olog(n) opposed to O(1) with doubly linked list.
    }

    auto printPages = [](const vector<Page>& pages) {
        for(auto& page : pages) {
            std::cout << "{" << page.id << "," << page.hit << " } ";
        }
        std::cout << "\n";
    };

    auto printLru = [] (set<Page*, PagePtrComp>& lru) {
        for(auto it = lru.begin(); it != lru.end(); ++it) {
            std::cout << "{" << (*it)->id << "," << (*it)->hit << " } ";
        }
        std::cout << "\n";
    };


    printPages(pages); PagePtrComp cmp;
    std::cout << "LRU\n";

    printLru(lru);
}

