#include <cmath>
#include <cstdio>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT
    */
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int> > orders;

    try {
        orders.reserve(n);
    } catch (const std::length_error& le) {
        std::cerr << "Lenght error: " << le.what() << std::endl;
    }

    for (int i = 1; i <= n; i++) {
        int ti, di;
        std::cin >> ti >> di;
        orders.push_back(std::make_pair(i, ti + di));
    }

    std::sort(orders.begin(), orders.end(),
            [](const std::pair<int, int>& order1,
                const std::pair<int, int>& order2) {
            return (order1.second == order2.second
                    ? order1.first < order2.first
                    : order1.second < order2.second);
            });

    for (const auto& p : orders) std::cout << p.first << " ";

    std::cout << "\n";

    return 0;
}
