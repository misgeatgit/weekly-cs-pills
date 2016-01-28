#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int N,M;
    cin >> N; cin >> M;
    vector<int> array;
    array.resize(N);
    for(int i=0; i<N; i++) cin >> array[i];

    auto print = [&array]() {for(const auto& i: array) cout << i << " " ; cout << "\n";};

    for(int k=0; k<M; k++){
        int pos_flag;
        int i,j;
        cin >> pos_flag;
        cin >> i;
        cin >> j;
        switch(pos_flag){
            //Prepend
            case 1:             
            rotate(array.rbegin() + (N-j),array.rbegin()+(N-i+1),array.rend());            
            break;
            //Append
            case 2:            
            rotate(array.begin() + (i-1),array.begin()+j,array.end());            
            break;
            default:
            return -1;
        }
    }
    cout << abs(array[0]-array[N-1]) << "\n";    
    print();
    
    return 0;
}
