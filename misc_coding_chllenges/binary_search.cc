#include <cassert>
#include <cstdio>
#include <vector>

using namespace std;


int binary_search(vector<int> arr, int val, int begin, int end)
{
    if(begin == end) return -1;
    printf("%d %d\n", begin, end);
    int sz = (end - begin) / 2;
    if (arr[begin + sz] == val) return begin + sz;

    if(arr[sz] > val) return binary_search(arr, val, begin, sz);
    if(arr[sz] < val) return binary_search(arr, val, sz, end);

}


int main()
{
    auto print = [](const vector<int>& x) {
        for(const auto& e : x) {
            printf("%d ", e);
        } printf("\n");
    };
    vector<int> x = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    print(x);

    // assert( 6  == binary_search(x,7,0,x.size()));
    assert( 7  == binary_search(x, 8, 0, x.size()));
    // printf("%d is found at index %d\n", 7, binary_search(x,7,0,x.size()));

}
