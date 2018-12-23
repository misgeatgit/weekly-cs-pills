//#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

using ulint = long double;

ulint fib(unsigned int n)
{
    ulint fib [] = {0, 1};

    for(unsigned int i = 2; i <= n; i++) {
        ulint tmp = fib[0] + fib[1];
        fib[0] = fib[1];
        fib[1] = tmp;
    }

    return fib[1];
}


int main(int argc, char** argv)
{

    //printf("size of long double= %d bits.", sizeof(long double)*8);
    // cout << "fib(" << argv[1] << ") = " << fib(stoi(argv[1])) << "\n";
    printf("fib(%s) = %Lf\n", argv[1], fib(atoi(argv[1])));

}
