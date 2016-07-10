#include <vector>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <map>
#include <algorithm>
using namespace std;

// Adjecency matrix style. This feature is called alias template in C++11.
template <class VertexD>
using AdjMGraph = std::map<VertexD, std::vector<VertexD>>;

// Breadth First algorithms
// Do breadth first search and apply Operator o on Each vertex reachable from
// vertex s.
template <class VertexD>
int bf_count(AdjMGraph<VertexD>& adj) {
    int subsets = 0;
    std::cout << "WORKING ON ADJ_MATRIX SIZE OF: " << adj.size() << "\n";
    for (const auto& p : adj) {
        std::vector<VertexD> frontier = {p.first};

        while (not frontier.empty()) {
            std::vector<VertexD> next = {};
            for (const auto& u : frontier) {
                for (const auto& v : adj[u]) {
                    subsets++;
                    //stdd::cout << "\t VIA " << v << " INCREASED TO " << subsets <<"\n";
                    next.push_back(v);
                }
            }
            frontier = next;
        }
    }

    return subsets;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT
    */
    AdjMGraph<int> connected;
    std::unordered_set<int> cities;
    int n;
    std::cin >> n;
    if (n <= 1) {
        std::cout << n << std::endl;
        return 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int c1, c2;
        std::cin >> c1 >> c2;
        auto mapped = [&](const int& key, const int& value) {
            if (std::find(connected[c1].begin(),
                        connected[c1].end(),
                        c2) == connected[c1].end())
                return false;
            return true;
        };
        // Lets make sure there is no remapping. i.e a->{b,..} and
        // b->{a,..}.
        if (not mapped(c1, c2) and not mapped(c2, c1))
            connected[c1].push_back(c2);
        // This will help set the minimum subset.
        cities.insert(c1);
        cities.insert(c2);
    }

    auto dbg_print = [&connected]() {
        for (const auto& p : connected) {
            std::cout << p.first << "->{";
            for (const auto& c : p.second) {
                std::cout << c << ",";
            }
            std::cout << "}" << std::endl;
        }
    };

    // dbg_print();

    // Look for subsets
    int subsets = cities.size() + bf_count(connected);

    std::cout << subsets << std::endl;

    return 0;
}
