#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    struct word {
        string w;
        size_t index;
    };

    vector<string> ws = {"cat", "tac", "dog", "act"};

    vector<word> aw;
    for(size_t i = 0; i < ws.size(); i++)
        aw.push_back({ws[i], i});

    for(auto& s : aw)
        sort((s.w).begin(), (s.w).end());

    sort(aw.begin(), aw.end(), [](word & w1, word & w2) {
        return w1.w < w2.w;
    });

    for(auto& a : aw)
        std::cout << ws[a.index] << " ";
    std::cout << "\n";

}
