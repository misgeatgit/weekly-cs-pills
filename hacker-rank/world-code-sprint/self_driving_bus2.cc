#include <vector>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <map>
#include <algorithm>

using namespace std;

std::map<int, std::vector<int>> connected;

void count(std::vector<int>, int&);

int main() {
    int n;
    std::cin >> n;
    if (n <= 1) {
        std::cout << n << std::endl;
        return 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int c1, c2;
        std::cin >> c1 >> c2;
        connected[c1].push_back(c2);
        connected[c2] = {};
    }

    int connected_subsets = 0;  // Each city is a subset

    // Look for subsets
    for (const auto& p : connected) {
        ++connected_subsets;
        count(p.second, connected_subsets);
    }

    std::cout << connected_subsets << std::endl;

    return 0;
}

void count(std::vector<int> s, int& cnt) {
    for (const int& city : s) {
        ++cnt;
        count(connected[city], cnt);
    }
}
