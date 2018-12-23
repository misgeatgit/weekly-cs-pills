#include <algorithm>
#include <vector>
#include <iostream>

int majorityElement(std::vector<int> vec)
{
    std::sort(vec.begin(), vec.end());

    int e = vec[0];
    int prev_cnt = 1;
    int cur_cnt = 1;
    for(int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";
    for(int i = 0; i < vec.size() - 1; i++) {
        if( vec[i] == vec[i + 1] ) {
            cur_cnt++;
        } else {
            if(cur_cnt > prev_cnt) {
                prev_cnt = cur_cnt;
                e = vec[i];
            }
            cur_cnt = 1;
        }
    }

    if(cur_cnt > prev_cnt)
        e = vec[vec.size() - 1];

    return e;
}


int main( int argc, char** argv)
{
    int sz;
    std::cin >> sz;
    std::vector<int> vec(sz);

    for(int i = 0; i < sz; i++) {
        std::cin >> vec[i];
    }

    for(int i = 0; i < sz; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\nMajaority is:\n";
    std::cout << majorityElement(vec) << "\n";

}
